#-------------------------------------------------
#
# Project created by QtCreator 2014-05-19T19:49:51
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = TestBox
TEMPLATE = app

unix {
    # You may need to change this include directory
    INCLUDEPATH += /usr/include/OGRE
    CONFIG += link_pkgconfig
    PKGCONFIG += OGRE
}
win32 {
    LIBS *= user32.lib
    LIBS += -L$(OGRE_HOME)\\boost\\lib
    release:LIBS += -L$(OGRE_HOME)\\lib\\release
    debug:LIBS += -L$(OGRE_HOME)\\lib\\debug
    INCLUDEPATH += $(OGRE_HOME)\\include
    INCLUDEPATH += $(OGRE_HOME)\\include\\OGRE\\Overlay
    INCLUDEPATH += $(OGRE_HOME)\\include\\OGRE
    INCLUDEPATH += $(OGRE_HOME)\\boost
}
INCLUDEPATH += include

debug {
    TARGET = $$join(TARGET,,,d)
    LIBS *= -lOgreMain_d -lOIS_d
}
release:LIBS *= -lOgreMain -lOIS

SOURCES += main.cpp \
           BoxApplication.cpp \
           mainwindow.cpp \
           MovableText.cpp 

HEADERS +=  BoxApplication.h \
            mainwindow.h \
            MovableText.h 
