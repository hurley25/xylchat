# =====================================================================================
# 
#       Filename:  chat.pro
#
#    Description:  为 Linux 环境书写的 chat 项目文件
#
#        Created:  2013年06月03日 18时05分02秒
#
# =====================================================================================

TEMPLATE = app
TARGET = 
DEPENDPATH += .
INCLUDEPATH += .

INCLUDEPATH += include

QT += network

# Input
HEADERS += include/MainWindow.h include/ChatWidget.h

SOURCES += src/main.cpp src/MainWindow.cpp src/ChatWidget.cpp

RESOURCES += resource.qrc
