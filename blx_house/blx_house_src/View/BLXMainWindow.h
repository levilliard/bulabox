
/*
------------------------------------------------------------------
||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
|||                                                                                                        |||
|||      BULABOX 1.0                                                                          |||
|||      Module HOMEBOX                                                                 |||
|||      Copyright 2014 june, levilliard@gmail.com                    |||
|||                                                                                                        |||
||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
------------------------------------------------------------------
*/
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "Core/BLXCore.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void createView();
    void switchWidget();
    void switchWidget1();

private:
 QWidget* m_widget1;
 QWidget* m_widget2;
};

#endif // MAINWINDOW_H
