
#ifndef PRO_h
#define PRO_h

#include <QMainWindow>
#include <QMenu>
#include <QMenuBar>
#include <QAction>
#include <QWidget>

#include "BoxApplication.h"

class MainWindow: public QMainWindow
{
  Q_OBJECT
 
  private:
    BoxApplication *m_widget;
  
  public:
    MainWindow();

  public slots:
    void create_menu();
    void about();
    void about_pro();
    void help();
};
 
#endif 	//PRO_h
