
#include "mainwindow.h"
#include "BoxApplication.h"
#include <QApplication>

int main(int argc, char *argv[])
{
  QApplication app(argc, argv);

  BoxApplication *w = new BoxApplication;
  w->show();
 
  return app.exec();
}
