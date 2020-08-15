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
//    le_user->setText("<user_name>");
//    le_pw->setText("<password>");
    le_user->setText("admin");
    le_pw->setText("hodrumet999");

    le_ip->setText( QString::fromStdString(getCamIP()) );
    le_port->setText("554");

    connect(pb, SIGNAL(clicked(bool)), this, SLOT(initVideoStream()));

    gl->addWidget(pb);
    gl->addWidget(le_user);
    gl->addWidget(le_pw);
    gl->addWidget(le_ip);
    gl->addWidget(le_port);

    return gl;
}

void MainWindow::videoStream(std::string url_0){
    QString program = "ffplay"; // or the path to ffmpeg
    QStringList arguments;
    url_0 += " -fast -filter_threads 4";
    arguments << "-i";
    arguments << QString::fromStdString(url_0); // rtsp://admin:hodrumet999@192.168.1.116:554";


    QProcess *ffmpegProc = new QProcess(this); // this can be replaced by a valid parent
//    ffmpegProc->start(program, arguments);
    ffmpegProc->execute(program, arguments);
    std::cout << ffmpegProc->error() << std::endl;
    ffmpegProc->waitForFinished();

}

void MainWindow::initVideoStream(){
//    std::string url_1 = "/cam/realmonitor?channel=1&subtype=1";

    url_0 = "rtsp://" + le_user->text().toStdString()
            + ":" + le_pw->text().toStdString()
            + "@" + le_ip->text().toStdString()
            + ":" + le_port->text().toStdString();

    videoStream(url_0);

    return;
}


std::string MainWindow::getCamIP(){
//    return "192.168.1.116";
    QString ret = "";
    QString keyword = "9c-8e-cd-1e-54-06";
    QString cmd = "arp -a";
    std::string word = "";
    std::string ip = "";
    std::string mac = "";

    QProcess *myProcess = new QProcess();
    myProcess->start(cmd);
    myProcess->waitForFinished();
    QByteArray ba = myProcess->readAll();

    std::stringstream ss(QString::fromLocal8Bit(ba).toStdString());

    int i = 0;
    while(ss >> word){
        std::cout << i << " " << word << std::endl;
        if(i % 2 == 0) ip = word;
        else mac = word;

        if( word == keyword.toStdString() ){
            std::cout << "Amcrest Camera found! " << mac << " : " << ip << std::endl;
            ret = QString::fromStdString(ip);
        }

        i++;
    }

    return ret.toStdString();
}


bool MainWindow::connection(std::string){
    QProcess *myProcess = new QProcess();
    QString cmd = "ping";
    QString args;

    myProcess->start(cmd);
    myProcess->waitForFinished();
    QByteArray ba = myProcess->readAll();

    std::stringstream ss(QString::fromLocal8Bit(ba).toStdString());

    int i = 0;
    std::string word;
    while(ss >> word){
        std::cout << i << " " << word << std::endl;
        if(0) return true;
        i++;
    }

    return false;
}



