QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = opencvtest
TEMPLATE = app
CONFIG += -std=c++11

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += main.cpp\
        mainwindow.cpp \
    cannyfilter.cpp \
    contour.cpp \
    capture.cpp

HEADERS  += mainwindow.h \
    cannyfilter.h \
    contour.h \
    capture.h

FORMS    += mainwindow.ui

INCLUDEPATH += C:\Users\usjaghi41\Documents\OpenCV\opencv\build\include

LIBS += C:\Users\usjaghi41\Documents\OpenCV\opencv\build\bin\libopencv_core340.dll
LIBS += C:\Users\usjaghi41\Documents\OpenCV\opencv\build\bin\libopencv_highgui340.dll
LIBS += C:\Users\usjaghi41\Documents\OpenCV\opencv\build\bin\libopencv_imgcodecs340.dll
LIBS += C:\Users\usjaghi41\Documents\OpenCV\opencv\build\bin\libopencv_imgproc340.dll
LIBS += C:\Users\usjaghi41\Documents\OpenCV\opencv\build\bin\libopencv_features2d340.dll
LIBS += C:\Users\usjaghi41\Documents\OpenCV\opencv\build\bin\libopencv_calib3d340.dll
LIBS += C:\Users\usjaghi41\Documents\OpenCV\opencv\build\bin\libopencv_video340.dll
LIBS += C:\Users\usjaghi41\Documents\OpenCV\opencv\build\bin\libopencv_videoio340.dll
LIBS += C:\Users\usjaghi41\Documents\OpenCV\opencv\build\bin\libopencv_videostab340.dll
LIBS += C:\Users\usjaghi41\Documents\OpenCV\opencv\build\bin\opencv_ffmpeg340.dll


# more correct variant, how set includepath and libs for mingw
# add system variable: OPENCV_SDK_DIR=D:/opencv/build
# read http://doc.qt.io/qt-5/qmake-variable-reference.html#libs

#OPENCV_SDK_DIR=C:/Users/usjaghi41/Documents/OpenCV/opencv/build
#INCLUDEPATH += $$(OPENCV_SDK_DIR)/include

#LIBS += -L$$(OPENCV_SDK_DIR)/bin    \
#        -lopencv_core320            \
#        -lopencv_highgui320         \
#        -lopencv_imgcodecs320       \
#        -lopencv_imgproc320         \
#        -lopencv_features2d320      \
#        -lopencv_calib3d320         \
#        -libopencv_video340.dll     \
#        -libopencv_videoio340.dll   \
#        -libopencv_videostab340.dll \
#        -opencv_ffmpeg340.dll







