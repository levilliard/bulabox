
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

#ifndef BOXAPPLICATION_h
#define BOXAPPLICATION_h

#include <QtGui>
#if defined(Q_WS_X11)
 #include <QX11Info>
#endif

#include <OgreRoot.h>
#include <OgreCamera.h>
#include <OgreSceneManager.h>
#include <OgreRenderWindow.h>
#include <OgreCamera.h>
#include <OgreConfigFile.h>
#include <OgreEntity.h>
#include <OgreManualObject.h>
#include <OgreViewport.h>
#include <OgreSceneNode.h>

enum VIEW{
    UP,
    BOTTOM,
    LEFT,
    RIGHT,
    FRONT,
    BACK
};

enum SceneType
{
    wGrid,
    wPlane,
    Reset
};

class BLXCore: public QWidget
{
  Q_OBJECT

  public:
   BLXCore(QWidget *parent = 0);
   ~BLXCore();
   QPaintEngine *paintEngine() const;

   void createDefaultScene();
   void createCamera();
   void createViewport();
   void createLight();
   void createGrid(int whidth, int height, float _size);
   void createPlane();
   void switchScene(SceneType stype);
   Ogre::Vector3 getm_CameraPosition();
   Ogre::Quaternion getm_CameraOrientation();

   void setObjectScene(const Ogre::String m_Ent, const Ogre::Vector3 m_Dim, const Ogre::Vector3 m_Pos);
   void setCameraView(VIEW m_view);
   void setNodeYaw(int val);
   void take_screen_shot(const std::string m_string);

  public slots:
   void setCameraPosition(const Ogre::Vector3 &Position);
   void setBackground(QColor &m_color);
   void setSceneType(SceneType type);

 signals:
   void changeCameraPosition(const Ogre::Vector3 &position);

 protected:
   virtual void setupOgreSystem();
   virtual void keyPressEvent(QKeyEvent *evt);
   virtual void mousePressEvent(QMouseEvent *evt);
   virtual void mouseMoveEvent(QMouseEvent *evt);
   virtual void mouseReleaseEvent(QMouseEvent *evt);
   virtual void paintEvent(QPaintEvent *evt);
   virtual void moveEvent(QMoveEvent *evt);
   virtual void showEvent(QShowEvent *evt);
   virtual void resizeEvent(QResizeEvent *evt);
   virtual void wheelEvent(QWheelEvent *evt);

 private:
   Ogre::Root*         m_Root;
   Ogre::SceneManager* m_SceneMgr;
   Ogre::RenderWindow* m_Window;
   Ogre::Camera*       m_Camera;
   Ogre::Viewport*     m_Viewport;
   Ogre::SceneNode*    m_Node;
   Ogre::SceneNode*    otherNode;
   Ogre::SceneNode*    principalNode;
   Ogre::Entity*       m_Entity;
   Ogre::Light*        m_Light;
   SceneType           m_type;

   Ogre::String        m_EntityName;
   Ogre::Vector3       m_Dimension;
   Ogre::Vector3       m_Position;

   QPoint old_position;
   static const Ogre::Real turbo_modifier;
   static const QPoint invalid_mouse_point;
};

#endif	//BOXAPPLICATION_h
