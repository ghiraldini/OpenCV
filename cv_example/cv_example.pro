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

# more correct variant, how set includepath and libs for mingw
# add system variable: OPENCV_SDK_DIR=D:/opencv/build
# read http://doc.qt.io/qt-5/qmake-variable-reference.html#libs

#OPENCV_SDK_DIR=C:\opencv\x64\mingw\bin
#INCLUDEPATH += $$(OPENCV_SDK_DIR)/include

#LIBS += -LC:\opencv\x64\mingw\bin  \
#        -lopencv_core400            \
#        -lopencv_highgui400         \
#        -lopencv_imgcodecs400       \
#        -lopencv_imgproc400         \
#        -lopencv_features2d400      \
#        -lopencv_calib3d400         \
#        -lopencv_video400.dll     \
#        -lopencv_videoio400.dll   \
##        -libopencv_videostab340.dll \
#        -opencv_ffmpeg400_64.dll







