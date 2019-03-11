QT += core gui widgets opengl

TARGET = QtOpenGL
TEMPLATE = app

DEFINES += QT_DEPRECATED_WARNINGS
CONFIG += c++11

SOURCES += main.cpp \
   FrmPrincipal.cpp \
   WidgetGL.cpp

HEADERS += \
   FrmPrincipal.h \
   WidgetGL.h

FORMS += \
   FrmPrincipal.ui

DISTFILES +=

RESOURCES += \
    images.qrc
