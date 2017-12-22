#include "BLXMainWindow.h"
#include <QPushButton>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      m_widget1(0),
      m_widget2(0)
{
    setFixedSize(500, 400);
    createView();
}

MainWindow::~MainWindow()
{

}

void MainWindow::createView()
{
    m_widget1 = new QWidget;
    m_widget1->setFixedSize(300, 200);
    m_widget1->setStyleSheet("background-color: gray;");
    setCentralWidget(m_widget1);

    QPushButton* m_button = new QPushButton("ONE",m_widget1);
    QObject::connect(m_button, SIGNAL(clicked()), this, SLOT(switchWidget()));
}

void MainWindow::switchWidget()
{

    m_widget2 = new QWidget;
    m_widget2->setFixedSize(300, 200);
    m_widget2->setStyleSheet("background-color: blue;");
    setCentralWidget(m_widget2);

    QPushButton* m_button = new QPushButton("TWO", m_widget2);
    QObject::connect(m_button, SIGNAL(clicked()), this, SLOT(switchWidget1()));
}

void MainWindow::switchWidget1()
{

    m_widget2 = new QWidget;
    m_widget2->setFixedSize(300, 200);
    m_widget2->setStyleSheet("background-color: yellow;");
    setCentralWidget(m_widget2);

    QPushButton* m_button = new QPushButton("THREE", m_widget2);
    QObject::connect(m_button, SIGNAL(clicked()), this, SLOT(createView()));
}
