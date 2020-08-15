#-------------------------------------------------
#
# Project created by QtCreator 2019-02-16T19:37:56
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Cam2Qt
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
        mainwindow.cpp

HEADERS += \
        mainwindow.h

FORMS += \
        mainwindow.ui

INCLUDEPATH += C:\opencv\include

JG_PATH = C:\opencv\x86\mingw\bin
LIBS += $$JG_PATH\libopencv_core345.dll
LIBS += $$JG_PATH\libopencv_highgui345.dll
LIBS += $$JG_PATH\libopencv_imgcodecs345.dll
LIBS += $$JG_PATH\libopencv_imgproc345.dll
LIBS += $$JG_PATH\libopencv_features2d345.dll
LIBS += $$JG_PATH\libopencv_calib3d345.dll
LIBS += $$JG_PATH\libopencv_video345.dll
LIBS += $$JG_PATH\libopencv_videoio345.dll
LIBS += $$JG_PATH\libopencv_videostab345.dll
LIBS += $$JG_PATH\opencv_ffmpeg345.dll
LIBS += $$JG_PATH\libopencv_objdetect345.dll
