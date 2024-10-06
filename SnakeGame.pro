QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    food.cpp \
    main.cpp \
    gamewindow.cpp \
    node.cpp \
    returnwindow.cpp \
    snake.cpp \
    startwindow.cpp \
    wall.cpp

HEADERS += \
    food.h \
    gamewindow.h \
    node.h \
    returnwindow.h \
    snake.h \
    startwindow.h \
    wall.h

FORMS += \
    gamewindow.ui \
    returnwindow.ui \
    startwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    image/image.qrc
