#include "capture.h"

Capture::Capture()
{
    cf = new CannyFilter;
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
//        cv::imshow(WIN_RF, frameReference); // view raw image
        cv::imshow(WIN_RF,cf->useCannyFilter(frameReference,lowThreshold));
    }

    return 0;
}




double Capture::getPSNR(const cv::Mat& I1, const cv::Mat& I2)
{
    cv::Mat s1;
    absdiff(I1, I2, s1);       // |I1 - I2|
    s1.convertTo(s1, CV_32F);  // cannot make a square on 8 bits
    s1 = s1.mul(s1);           // |I1 - I2|^2

    cv::Scalar s = sum(s1);        // sum elements per channel

    double sse = s.val[0] + s.val[1] + s.val[2]; // sum channels

    if( sse <= 1e-10) // for small values return zero
        return 0;
    else
    {
        double mse  = sse / (double)(I1.channels() * I1.total());
        double psnr = 10.0 * log10((255 * 255) / mse);
        return psnr;
    }
}




cv::Scalar Capture::getMSSIM( const cv::Mat& i1, const cv::Mat& i2)
{
    const double C1 = 6.5025, C2 = 58.5225;
    /***************************** INITS **********************************/
    int d = CV_32F;

    cv::Mat I1, I2;
    i1.convertTo(I1, d);            // cannot calculate on one byte large values
    i2.convertTo(I2, d);

    cv::Mat I2_2   = I2.mul(I2);        // I2^2
    cv::Mat I1_2   = I1.mul(I1);        // I1^2
    cv::Mat I1_I2  = I1.mul(I2);        // I1 * I2

    /*************************** END INITS **********************************/

    cv::Mat mu1, mu2;                   // PRELIMINARY COMPUTING
    cv::GaussianBlur(I1, mu1, cv::Size(11, 11), 1.5);
    cv::GaussianBlur(I2, mu2, cv::Size(11, 11), 1.5);

    cv::Mat mu1_2   =   mu1.mul(mu1);
    cv::Mat mu2_2   =   mu2.mul(mu2);
    cv::Mat mu1_mu2 =   mu1.mul(mu2);

    cv::Mat sigma1_2, sigma2_2, sigma12;

    cv::GaussianBlur(I1_2, sigma1_2, cv::Size(11, 11), 1.5);
    sigma1_2 -= mu1_2;

    cv::GaussianBlur(I2_2, sigma2_2, cv::Size(11, 11), 1.5);
    sigma2_2 -= mu2_2;

    cv::GaussianBlur(I1_I2, sigma12, cv::Size(11, 11), 1.5);
    sigma12 -= mu1_mu2;

    ///////////////////////////////// FORMULA ////////////////////////////////
    cv::Mat t1, t2, t3;

    t1 = 2 * mu1_mu2 + C1;
    t2 = 2 * sigma12 + C2;
    t3 = t1.mul(t2);                 // t3 = ((2*mu1_mu2 + C1).*(2*sigma12 + C2))

    t1 = mu1_2 + mu2_2 + C1;
    t2 = sigma1_2 + sigma2_2 + C2;
    t1 = t1.mul(t2);                 // t1 =((mu1_2 + mu2_2 + C1).*(sigma1_2 + sigma2_2 + C2))

    cv::Mat ssim_map;
    cv::divide(t3, t1, ssim_map);        // ssim_map =  t3./t1;

    cv::Scalar mssim = cv::mean(ssim_map);   // mssim = average of ssim map
    return mssim;
}
