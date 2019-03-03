#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    qRegisterMetaType<cv::Mat>();

    ImageViewer *view = new ImageViewer;
    Capture *capture = new Capture;
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

//    view->show();

    QObject::connect(capture, capture->started, [](){ qDebug() << "Capture started."; });
    QMetaObject::invokeMethod(capture, "start");

    setCentralWidget(view);

}

MainWindow::~MainWindow()
{
    delete ui;
}
