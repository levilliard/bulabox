
/*| BULABOX 1.0
 *| Module HOMEBOX
 * Copyright 2014 june, levilliard@gmail.com
 */

#ifndef BOXAPPLICATION_h
#define BOXAPPLICATION_h

#include <QtGui>
#include <QWidget>

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
#include "MovableText.h"

class BoxApplication: public QWidget
{
  Q_OBJECT

  public:
   BoxApplication(QWidget *parent = 0);
   ~BoxApplication();
   QPaintEngine *paintEngine() const;

   virtual void create_default_scene();
   virtual void create_camera();
   virtual void create_viewport();
   virtual void create_light();
   virtual void create_grid(int whidth, int height, float _size);

  // virtual void create_movable_text(Ogre::Vector3 &pos1, Ogre::Vector3 &pos2, Ogre::String line_name, Ogre::String node_name);
   void setup_scene(const Ogre::String &entity, const Ogre::Vector3 &dimension, const Ogre::Vector3 &position);
   //void create_line(Ogre::Vector3 &pos1, Ogre::Vector3 &pos2, const Ogre::String desc);

 public slots:
   void set_camera_position(const Ogre::Vector3 &position);
   void set_node_position(Ogre::Real real);
   
 signals:
   void change_camera_position(const Ogre::Vector3 &position);

 protected:
   virtual void setup_ogre_system();
   virtual void setup_resources();
   virtual void keyPressEvent(QKeyEvent *evt);
   virtual void mousePressEvent(QMouseEvent *evt);
   virtual void mouseMoveEvent(QMouseEvent *evt);
   virtual void mouseReleaseEvent(QMouseEvent *evt);
   virtual void paintEvent(QPaintEvent *evt);
   virtual void moveEvent(QMoveEvent *evt);
   virtual void showEvent(QShowEvent *evt);
   virtual void resizeEvent(QResizeEvent *evt);
   virtual void wheelEvent(QWheelEvent *evt);

 protected:
   Ogre::Root          *m_root;
   Ogre::SceneManager  *m_scene_mgr;
   Ogre::RenderWindow  *m_window;
   Ogre::Camera        *m_camera;
   Ogre::Viewport      *m_viewport;
   Ogre::SceneNode     *m_node;
   Ogre::Entity	       *m_entity;

   Ogre::String        mesh_entity;
   Ogre::Vector3       node_dimension;
   Ogre::Vector3       node_position;

   Ogre::Real          angle;
   QPoint              old_position;

  private:
   static const Ogre::Real turbo_modifier;
   static const QPoint invalid_mouse_point;
};

#endif	//BOXAPPLICATION_h
