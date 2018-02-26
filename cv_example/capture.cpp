#include "capture.h"

Capture::Capture()
{
    cf = new CannyFilter;

    //-- 1. Load the cascades
    if( !face_cascade.load( face_cascade_name ) ){
        printf("--(!)Error loading face cascade\n");
        exit(-1);
    }
    if( !eyes_cascade.load( eyes_cascade_name ) ){
        printf("--(!)Error loading eyes cascade\n");
        exit(-1);
    }


}

int Capture::initVideo(int deviceID, const std::string ipcam){
    std::string sourceReference = ipcam;
    if( deviceID == 0 || deviceID == 1)
        captRefrnc.open(deviceID);
    else
        captRefrnc.open(sourceReference);

    if (!captRefrnc.isOpened()){
        std::cout  << "Could not open reference " << sourceReference << std::endl;
        return -1;
    }

    cv::Size refS = cv::Size((int) captRefrnc.get(cv::CAP_PROP_FRAME_WIDTH),
                             (int) captRefrnc.get(cv::CAP_PROP_FRAME_HEIGHT));
    const char* WIN_RF = "Reference";

    // Windows
    cv::namedWindow(WIN_RF, cv::WINDOW_AUTOSIZE);
    cv::moveWindow(WIN_RF, 400, 0);         //750,  2 (bernat =0)

    std::cout << "Reference frame resolution: Width=" << refS.width << "  Height=" << refS.height
              << " of nr#: " << captRefrnc.get(cv::CAP_PROP_FRAME_COUNT) << std::endl;

    cv::Mat frameReference;

    while(cv::waitKey(33) != 27) //Show the image captured in the window and repeat
    {
        // Add trackerbar for canny filter
        cv::createTrackbar( "Min Threshold:", WIN_RF, &lowThreshold, 100, change );

        captRefrnc >> frameReference;
        cv::imshow(WIN_RF, frameReference); // view raw image
        //        cv::imshow(WIN_RF,cf->useCannyFilter(frameReference,lowThreshold));
    }

    exit(0);
}



void Capture::BackgroundSubtract(int deviceID, const std::string ipcam){    
    cv::Mat frameReference, res;
    std::vector<cv::Mat> spl;
    int i=0,
            channel = 0;
    std::string sourceReference = ipcam;

    pMOG2 = cv::createBackgroundSubtractorMOG2(); //MOG2 approach

    if( deviceID == 0 || deviceID == 1)
        captRefrnc.open(deviceID);
    else
        captRefrnc.open(sourceReference);

    if (!captRefrnc.isOpened()){
        std::cout  << "Could not open reference " << sourceReference << std::endl;
        exit(1);
    }

    cv::Size refS = cv::Size((int) captRefrnc.get(cv::CAP_PROP_FRAME_WIDTH),
                             (int) captRefrnc.get(cv::CAP_PROP_FRAME_HEIGHT));
    const char* WIN_RF = "Reference";

    // Open output video for motion
//    int ex = static_cast<int>(captRefrnc.get(CV_CAP_PROP_FOURCC));
//    outputVideo.open(vidPath, ex, captRefrnc.get(CV_CAP_PROP_FPS), refS, true);

    // Windows
    cv::namedWindow(WIN_RF, cv::WINDOW_AUTOSIZE);
    cv::moveWindow(WIN_RF, 400, 0);         //750,  2 (bernat =0)

    std::cout << "Reference frame resolution: Width=" << refS.width << "  Height=" << refS.height
              << " of nr#: " << captRefrnc.get(cv::CAP_PROP_FRAME_COUNT) << std::endl;

    while(cv::waitKey(33) != 27) //Show the image captured in the window and repeat
    {        
        captRefrnc >> frameReference;

        // Add trackerbar
        cv::createTrackbar( "Min Threshold:", WIN_RF, &lowThreshold, 100, change );



        // If MOTION
        if(doBS(&frameReference, &fgMaskMOG2, refS.width * refS.height) > lowThreshold){

            /* Save Video of Motion */
            cv::split(frameReference, spl);
            for (int i =0; i < 3; ++i)
                if (i != channel)
                    spl[i] = cv::Mat::zeros(refS, spl[0].type());
            cv::merge(spl, res);
            outputVideo << res;



            /* Save Images of motion
            newPath = path + "image_" + std::to_string(i) + ".jpg";
            cv::imwrite(newPath, frameReference);
            i++;
            */

            cv::imshow(WIN_RF, frameReference); // view raw image
        } else {
//            cv::imshow(WIN_RF, fgMaskMOG2); // view mask
            detectAndDisplay( frameReference );
            cv::imshow(WIN_RF, frameReference); // view raw image
        }
    }

    exit(0);
}


// Does actual Background subtraction and calculates percentage
// of pixel motion
double Capture::doBS(cv::Mat *src, cv::Mat *mask, int totalPix){

    // Background Subtraction
    pMOG2->apply(*src, *mask);
    //get the frame number and write it on the current frame
    std::stringstream ss;
    cv::rectangle(*src, cv::Point(10, 2), cv::Point(100,20),
                  cv::Scalar(255,255,255), -1);
    ss << captRefrnc.get(cv::CAP_PROP_POS_FRAMES);
    std::string frameNumberString = ss.str();
    cv::putText(*src, frameNumberString.c_str(), cv::Point(15, 15),
                cv::FONT_HERSHEY_SIMPLEX, 0.5 , cv::Scalar(0,0,0));

    return 100.0 * (1.0-(double)(totalPix - cv::countNonZero(*mask))/totalPix);

}



/** @function detectAndDisplay */
void Capture::detectAndDisplay( cv::Mat &frame )
{
    std::vector<cv::Rect> faces;
    cv::Mat frame_gray;

    cv::cvtColor( frame, frame_gray, cv::COLOR_BGR2GRAY );
    cv::equalizeHist( frame_gray, frame_gray );

    //-- Detect faces
    face_cascade.detectMultiScale( frame_gray, faces, 1.1, 2, 0|cv::CASCADE_SCALE_IMAGE, cv::Size(30, 30) );

    for( size_t i = 0; i < faces.size(); i++ )
    {
        cv::Point center( faces[i].x + faces[i].width/2, faces[i].y + faces[i].height/2 );
        cv::ellipse( frame, center, cv::Size( faces[i].width/2, faces[i].height/2), 0, 0, 360, cv::Scalar( 255, 0, 255 ), 4, 8, 0 );

        cv::Mat faceROI = frame_gray( faces[i] );
        std::vector<cv::Rect> eyes;

        //-- In each face, detect eyes
        eyes_cascade.detectMultiScale( faceROI, eyes, 1.1, 2, 0 |cv::CASCADE_SCALE_IMAGE, cv::Size(30, 30) );

        for( size_t j = 0; j < eyes.size(); j++ )
        {
            cv::Point eye_center( faces[i].x + eyes[j].x + eyes[j].width/2, faces[i].y + eyes[j].y + eyes[j].height/2 );
            int radius = cvRound( (eyes[j].width + eyes[j].height)*0.25 );
            cv::circle( frame, eye_center, radius, cv::Scalar( 255, 0, 0 ), 4, 8, 0 );
        }
    }
    //-- Show what you got
//    cv::imshow( "Face", frame );
}
