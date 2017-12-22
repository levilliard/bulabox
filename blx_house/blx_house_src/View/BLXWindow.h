
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

#ifndef __BLXWINDOW_h
#define __BLXWINDOW_h

#include "Core/BLXCore.h"

class BLXWindow: public QWidget
{
    Q_OBJECT
public:
    BLXWindow();
    ~BLXWindow();
    void createSceneMenu();
    void createTAMenu();
    void createViewMenu();
    void createObjMenu();
    void createScreenLog();
    void createSceneBar();
    void createLogScreen();
    QString getLogFile();

     void screen_shot();
     void change_bkg();

public slots:
    void setCameraUpView();
    void setCameraBottomView();
    void setCameraFrontView();
    void setCameraBackView();
    void setCameraLeftView();
    void setCameraRightView();

    void createSketchPlane();
    void createHalfPlane();
    void createBasePlane();

    void VSlider(int val);
    void HSlider(int val);
    void rotDial(int val);

     void addGrid();
     void addPlane();
     void resetScene();

private:
    BLXCore* m_object;

    QString log_file;
    QGroupBox* m_taff_box;
    QGroupBox* m_view_box;
    QGroupBox* menu_change_scene;

    QTextEdit *m_text;
    QGridLayout *principal_layout;

    QGroupBox *bar_menu;
};

#endif
