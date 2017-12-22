
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

#include <QtGui>
#include "View/BLXMainWindow.h"

int main(int argc, char *argv[])
{
   QApplication app(argc, argv);
   MainWindow* m_widget = new MainWindow();
      m_widget->show();

   return app.exec();
}
