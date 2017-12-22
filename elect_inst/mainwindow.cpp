
#include "mainwindow.h"
#include <QApplication>

MainWindow::MainWindow()
{
  setWindowTitle("BULABOX/FDS_INST");
  setMinimumSize(700, 400);
  create_menu();
  
  m_widget = new BoxApplication(0);
  setCentralWidget(m_widget);

}

void MainWindow::create_menu()
{
    QMenu* menu_file = menuBar()->addMenu("&File");

    QAction *add_file = new QAction("&Add file", this);
    QAction *open_file = new QAction("&Open file", this);
    QAction *exit = new QAction("&Exit", this);

    menu_file->addAction(add_file);
    menu_file->addAction(open_file);
    menu_file->addAction(exit);

    QObject::connect(exit, SIGNAL(triggered()), qApp, SLOT(quit()));
    //QObject::connect(open_box, SIGNAL(triggered()), this, SLOT(open_file()));
    //QObject::connect(add_box, SIGNAL(triggered()), this, SLOT(open_file()));

    QMenu* menu_about = menuBar()->addMenu("&About ");

    QAction *about_us = new QAction("&About us", this);
    QAction *about_pro = new QAction("&About The Pro ", this);

    menu_about->addAction(about_us);
    menu_about->addAction(about_pro);

    QObject::connect(about_us, SIGNAL(triggered()), this, SLOT(about()));
    QObject::connect(about_pro, SIGNAL(triggered()), this, SLOT(about_pro()));

    QMenu *help = menuBar()->addMenu("&?");

    QObject::connect(help, SIGNAL(triggered()), this, SLOT(help()));
}

void MainWindow::about()
{

}
 void MainWindow::about_pro()
{

}

void MainWindow::help()
{

}

