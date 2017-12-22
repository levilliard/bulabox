
// test bulabox

#include "BoxApplication.h"
#include <QMessageBox>
#include <QPushButton>
#include <QtGui>

const QPoint BoxApplication::invalid_mouse_point(-400, -400);
const Ogre::Real BoxApplication::turbo_modifier(5);

BoxApplication::BoxApplication(QWidget *parent): QWidget(parent),
m_root(0),
m_scene_mgr(0),
m_window(0),
m_camera(0),
m_viewport(0),
m_node(0),
m_entity(0)
{
  setAttribute(Qt::WA_OpaquePaintEvent);
  setAttribute(Qt::WA_PaintOnScreen);
  setFocusPolicy(Qt::StrongFocus);

  setWindowTitle("BULABOX 1.0");

}

/*----------Ogre3D functions------------*/
BoxApplication::~BoxApplication()
{
  if(m_window)
  {
    m_window->removeAllViewports();
  }
  
  if(m_root)
  {
    m_root->detachRenderTarget(m_window);
   
    if(m_scene_mgr)
    {
      m_root->destroySceneManager(m_scene_mgr);
    }
  }
  
  delete m_root;
}

void BoxApplication::setup_ogre_system()
{
    m_root = new Ogre::Root();
    
    Ogre::RenderSystem *render_system = m_root->getRenderSystemByName("OpenGL Rendering Subsystem");
    m_root->setRenderSystem(render_system);
    m_root->initialise(false);
    
    m_scene_mgr = m_root->createSceneManager(Ogre::ST_GENERIC);
    m_scene_mgr->setAmbientLight(Ogre::ColourValue(0, 0, 0));
    setup_resources();
    
    Ogre::NameValuePairList view_config;
    Ogre::String widget_handle;
    widget_handle = Ogre::StringConverter::toString((size_t)(HWND)this->winId());
    view_config["externalWindowHandle"] = widget_handle;
//    view_config["FSAA"] = Ogre::String("8");
    m_window = m_root->createRenderWindow("TheOgreRenderWindow", width(), height(), false, &view_config);
     QMessageBox::about(this, "ERROR", "befor view config");
    create_camera();
    create_viewport();
    create_light();

    create_default_scene();

  }

void BoxApplication::setup_resources()
{
    Ogre::ConfigFile config_file;
    config_file.load("resources.cfg");
    
    Ogre::ConfigFile::SectionIterator seci = config_file.getSectionIterator();
    Ogre::String secName, typeName, archName;
    while(seci.hasMoreElements())
    {
      secName = seci.peekNextKey();
      Ogre::ConfigFile::SettingsMultiMap *settings = seci.getNext();
      Ogre::ConfigFile::SettingsMultiMap::iterator i;
      for(i = settings->begin(); i != settings->end(); ++i)
      {
          typeName = i->first;
          archName = i->second;
          
#if OGRE_PLATFORM == OGRE_PLATFORM_APPLE
          Ogre::ResourceGroupManager::getSingleton().addResourceLocation(
                      Ogre::String(macBundlePath() + "/" + archName), typeName, secName);
#else
          Ogre::ResourceGroupManager::getSingleton().addResourceLocation(archName, typeName, secName);
#endif
      }
    }
    
    Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();
    
}
void BoxApplication::create_default_scene()
{ 
    //house
    Ogre::Entity *m_entity = m_scene_mgr->createEntity("house", "robot.mesh");
    m_node = m_scene_mgr->getRootSceneNode()->createChildSceneNode("home");
    m_node->attachObject(m_entity);
    m_node->setPosition(0, 0, 0);
    m_node->setScale(1, 1, 1); //60 1 30
    
  /*  Ogre::Vector3 v1, v2;
    v1 = Ogre::Vector3(5, 0, 5);
    v2 = Ogre::Vector3(5, 100, 5);
    create_movable_text(v1, v2, "Position", "ParentNod");
    //create_grid(10, 10, 50);
   */
}

void BoxApplication::setup_scene(const Ogre::String &n_ent, const Ogre::Vector3 &dimension, const Ogre::Vector3 &position)
{
  mesh_entity = n_ent;
  node_dimension = dimension;
  node_position = position;
}

/*void BoxApplication::create_line(Ogre::Vector3 &pos1, Ogre::Vector3 &pos2, const Ogre::String desc)
{

    //create the line
    Ogre::ManualObject *m_object = m_scene_mgr->createManualObject(desc);
    m_object->begin("BaseWhiteNoLighting", Ogre::RenderOperation::OT_LINE_LIST);
    m_object->position(pos1);
    m_object->position(pos2);
    m_object->end();

    Ogre::SceneNode *m_node = m_scene_mgr->getRootSceneNode()->createChildSceneNode(desc);
    m_node->attachObject(m_object);
}
*/
void BoxApplication::create_camera()
{
    m_camera = m_scene_mgr->createCamera("m_camera");
    Ogre::Vector3 camera_pos(0, 1, 100);
    m_camera->setFixedYawAxis(false);
    m_camera->setPosition(camera_pos);
    m_camera->lookAt(0, 0, 0);
    m_camera->setNearClipDistance(3);
    m_camera->setFarClipDistance(3000);

}

void BoxApplication::create_light()
{
    Ogre::Light *house_light = m_scene_mgr->createLight("main light");
   // house_light->setType(Ogre::Light::LT_SPOTLIGHT);
    //house_light->setAttenuation(300, 1, 0.007, 0);
   // house_light->setSpotlightRange(Ogre::Degree(60), Ogre::Degree(60), 1.0);
    house_light->setDiffuseColour(0, 0, 1);
    house_light->setSpecularColour(0, 0, 1);
   // house_light->setPosition(100,80, 250);
   // house_light->setDirection(0, -30, 0);
}

void BoxApplication::create_viewport()
{
    m_viewport = m_window->addViewport(m_camera);
    m_viewport->setBackgroundColour(Ogre::ColourValue(0.1, 0, 0.1));
    m_camera->setAspectRatio(Ogre::Real(width()) / Ogre::Real(height()));

}
/*
void BoxApplication::create_movable_text(Ogre::Vector3 &pos1, Ogre::Vector3 &pos2, Ogre::String line_name, Ogre::String node_name)
{
    //create the line
    Ogre::ManualObject *m_object = m_scene_mgr->createManualObject(line_name);
    m_object->begin("BaseWhiteNoLighting", Ogre::RenderOperation::OT_LINE_LIST);
    m_object->position(pos1);
    m_object->position(pos2);
    m_object->end();

      Ogre::SceneNode *m_node = m_scene_mgr->getRootSceneNode()->createChildSceneNode(node_name);
    m_node->attachObject(m_object);

    Ogre::Real l = pos1.distance(pos2);
    char chaine[10];
    sprintf(chaine, "%.2fm", 0.1*l);
    Ogre::SceneNode *labe1 = m_scene_mgr->getRootSceneNode()->createChildSceneNode(line_name);
    Ogre::MovableText* msg = new Ogre::MovableText("TXT_001", chaine, "BlueHighway-16", 1.0, Ogre::ColourValue::Black);
    msg->setTextAlignment(Ogre::MovableText::H_CENTER, Ogre::MovableText::V_ABOVE);

    msg->setCharacterHeight(0.4);
    msg->setColor(Ogre::ColourValue::Red);
    labe1->attachObject(msg);
    Ogre::Vector3 v1 = 0.5*(pos1 + pos2);
    v1.y = v1.y - 3;
    labe1->setScale(10, 10, 10);
    labe1->setPosition(v1);

}

*/
void BoxApplication::create_grid(int n_col, int n_row, float size)
{
    Ogre::ManualObject* m_object = m_scene_mgr->createManualObject("GRID");
    Ogre::SceneNode *object_node = m_scene_mgr->getRootSceneNode()->createChildSceneNode("object");

    m_object->begin("BaseWhiteNoLighting", Ogre::RenderOperation::OT_LINE_LIST);

    float h = 0;
    float width = (float)n_col * size;
    float depth = (float)n_row * size;
    Ogre::Vector3 center = Ogre::Vector3(-width / 2.0f, h, -depth / 2.0f);

    for (int i = 0; i < n_row; ++i)
    {
        Ogre::Vector3 s, e;
        s.x = 0.0f;
        s.z = i * size;
        s.y = h;

        e.x = width;
        e.z = i * size;
        e.y = h;

        m_object->position(s + center);
        m_object->position(e + center);
    }
    m_object->position(Ogre::Vector3(0.0f, h, n_row * size) + center);
    m_object->position(Ogre::Vector3(width, h, n_row * size) + center);

    for (int i = 0; i < n_col; ++i)
    {
        Ogre::Vector3 s, e;
        s.x = i * size;
        s.z = depth;
        s.y = h;

        e.x = i * size;
        e.z = 0.0f;
        e.y = h;

        m_object->position(s + center);
        m_object->position(e + center);
    }

    m_object->position(Ogre::Vector3(n_col * size, h, 0.0f) + center);
    m_object->position(Ogre::Vector3(n_col * size, h, depth) + center);
    m_object->end();

    object_node->setPosition(0, -50, 0);
    object_node->attachObject(m_object);

}


void BoxApplication::set_camera_position(const Ogre::Vector3 &position)
{
    m_camera->setPosition(position);
    //m_camera->lookAt(0, 0, 0);
    update();
    emit change_camera_position(position);
}

void BoxApplication::set_node_position(Ogre::Real real)
{
    m_node->yaw(Ogre::Degree(real));
}

void BoxApplication::keyPressEvent(QKeyEvent *evt)
{

}

void BoxApplication::mouseMoveEvent(QMouseEvent *evt)
{
    if(evt->buttons().testFlag(Qt::LeftButton))
    {
        const QPoint &pos = evt->pos();
        Ogre::Real pos_x = pos.x() - old_position.x();
        Ogre::Real pos_y = pos.y() - old_position.y();

        if(evt->modifiers().testFlag(Qt::ControlModifier))
        {
            pos_x *= turbo_modifier;
            pos_y *= turbo_modifier;
        }

        Ogre::Vector3 camera_translation(pos_x, pos_y, 0);
        const Ogre::Vector3 &actual_camera_pos = m_camera->getPosition();
        set_camera_position(actual_camera_pos + camera_translation);

        old_position = pos;
        evt->accept();

    }
    else
    {
        evt->accept();
    }

}


void BoxApplication::mousePressEvent(QMouseEvent *evt)
{
   if(evt->buttons().testFlag(Qt::LeftButton))
   {
       old_position = evt->pos();
       evt->accept();
   }
   else
   {
       evt->ignore();
   }
}

void BoxApplication::mouseReleaseEvent(QMouseEvent *evt)
{
    if(!evt->buttons().testFlag(Qt::LeftButton))
    {
        old_position = QPoint(invalid_mouse_point);
        evt->accept();
    }
    else
    {
        evt->ignore();
    }
}

QPaintEngine *BoxApplication::paintEngine() const
{
    return NULL;
}

void BoxApplication::moveEvent(QMoveEvent *evt)
{
   QWidget::moveEvent(evt);

   if(evt->isAccepted() && m_window)
   {
       m_window->windowMovedOrResized();
       update();
   }
}

void BoxApplication::paintEvent(QPaintEvent *evt)
{
   if(!m_root)
   {
       setup_ogre_system();
   }

   m_root->_fireFrameStarted();
   m_window->update();
   m_root->_fireFrameEnded();
    evt->accept();
}

void BoxApplication::resizeEvent(QResizeEvent *evt)
{
    QWidget::resizeEvent(evt);

    if(evt->isAccepted())
    {
        const QSize &new_size = evt->size();
        if(m_window)
        {
            m_window->resize(new_size.width(), new_size.height());
            m_window->windowMovedOrResized();
        }

        if(m_camera)
        {
            Ogre::Real aspect_ratio = Ogre::Real(new_size.width()/Ogre::Real(new_size.height()));
            m_camera->setAspectRatio(aspect_ratio);
        }
    }
}

void BoxApplication::showEvent(QShowEvent *evt)
{
    QWidget::showEvent(evt);
}

void BoxApplication::wheelEvent(QWheelEvent *evt)
{
   Ogre::Vector3 z_translation(evt->delta()/20, evt->delta()/20, evt->delta()/20);

   if(evt->modifiers().testFlag(Qt::ControlModifier))
   {
       z_translation.z *= turbo_modifier;
   }

   const Ogre::Vector3 &actual_camera_position = m_camera->getPosition();
   set_camera_position(actual_camera_position + z_translation);

   evt->accept();
}

