#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLayout>
#include <QPushButton>
#include <QLineEdit>
#include <QProcess>

#include <iostream>

#include "opencv2/core/core.hpp"

Q_DECLARE_METATYPE(cv::Mat);

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;    
    QGridLayout * initGUI();
    std::string url_0;
    QLineEdit *le_user;
    QLineEdit *le_pw;
    QLineEdit *le_ip;
    QLineEdit *le_port;

    std::string getCamIP();
    void videoStream(std::string);

    bool connection(std::string);

signals:
    void start(int cam);

public slots:
    void initVideoStream();
};

#endif // MAINWINDOW_H
