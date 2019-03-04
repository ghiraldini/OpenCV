#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QWidget *w = new QWidget;
    w->setLayout( initGUI() );

    setCentralWidget(w);

}

MainWindow::~MainWindow()
{
    delete ui;
}


QGridLayout* MainWindow::initGUI(){
    //"rtsp://<user>:<pw>@10.0.0.234:554/cam/realmonitor?channel=1&subtype=1";
    QGridLayout *gl = new QGridLayout;
    QPushButton *pb = new QPushButton("Start");
    le_user = new QLineEdit("USER");
    le_pw = new QLineEdit();
    le_ip = new QLineEdit();
    le_port = new QLineEdit();
    le_pw->setEchoMode(QLineEdit::Password);
    le_user->setText("<user_name>");
    le_pw->setText("<password>");
    le_ip->setText("10.0.0.234");
    le_port->setText("554");

    connect(pb, SIGNAL(clicked(bool)), this, SLOT(initVideoStream()));

    gl->addWidget(pb);
    gl->addWidget(le_user);
    gl->addWidget(le_pw);
    gl->addWidget(le_ip);
    gl->addWidget(le_port);

    return gl;
}


void MainWindow::initVideoStream(){
    std::string url_1 = "/cam/realmonitor?channel=1&subtype=1";

    url_0 = "rtsp://" + le_user->text().toStdString()
            + ":" + le_pw->text().toStdString()
            + "@" + le_ip->text().toStdString()
            + ":" + le_port->text().toStdString()
            + url_1;

    qRegisterMetaType<cv::Mat>();

    ImageViewer *view = new ImageViewer;
    Capture *capture = new Capture(url_0);
    Converter *converter = new Converter;

    Thread *captureThread = new Thread;
    Thread *converterThread = new Thread;

    // Everything runs at the same priority as the gui, so it won't supply useless frames.
    converter->setProcessAll(false);

    captureThread->start();
    converterThread->start();

    capture->moveToThread(captureThread);
    converter->moveToThread(converterThread);

    QObject::connect(capture, capture->frameReady, converter, converter->processFrame);
    QObject::connect(converter, converter->imageReady, view, view->setImage);

    view->show();

    QObject::connect(capture, capture->started, [](){ qDebug() << "Capture started."; });
    QMetaObject::invokeMethod(capture, "start");

    return;
}
