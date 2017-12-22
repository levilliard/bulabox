
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


/* This file is the core of the app............................................*/
#include "Core/BLXCore.h"
//#include "Core/BLXLogic.h"
const QPoint BLXCore::invalid_mouse_point(-400, -400);
const Ogre::Real BLXCore::turbo_modifier(5);


BLXCore::BLXCore(QWidget *parent): QWidget(parent),
m_Root(0),
m_SceneMgr(0),
m_Window(0),
m_Camera(0),
m_Viewport(0),
m_Node(0),
otherNode(0),
principalNode(0),
m_Entity(0)
{
  setAttribute(Qt::WA_OpaquePaintEvent);
  setAttribute(Qt::WA_PaintOnScreen);
  setFocusPolicy(Qt::ClickFocus);

  setWindowTitle("BULABOX 1.0");
  //m_type = Reset;

  //BLXLogic logic;
  //std::string code = readCode();
  //QVector<Mesh>temp = logic.selectBLXObject("home", QString::fromStdString(code));
  //if(!temp.empty())
  //{
    m_EntityName = "test_sketch_001.mesh";
    m_Dimension = Ogre::Vector3(1, 60, 1);
    m_Position = Ogre::Vector3(0, 0, 0);
 //}
  //else
  //{
    // QMessageBox::about(this, "ERROR", "LOADING FAILDED");
  //}
}

/*----------Ogre3D functions------------*/
BLXCore::~BLXCore()
{
  if(m_Window)
  {
    m_Window->removeAllViewports();
  }

  if(m_Root)
  {
    m_Root->detachRenderTarget(m_Window);

    if(m_SceneMgr)
    {
      m_Root->destroySceneManager(m_SceneMgr);
    }
  }

  delete m_Root;
}

void BLXCore::setupOgreSystem()
{
    m_Root = new Ogre::Root();

    Ogre::RenderSystem *render_system = m_Root->getRenderSystemByName("OpenGL Rendering Subsystem");
    m_Root->setRenderSystem(render_system);
    m_Root->initialise(false);

    m_SceneMgr = m_Root->createSceneManager(Ogre::ST_GENERIC);
    m_SceneMgr->setAmbientLight(Ogre::ColourValue(0.8, 0.8, 0.8));

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

    Ogre::NameValuePairList view_config;
    Ogre::String widget_handle;
#ifdef Q_WS_WIN
    widget_handle = Ogre::StringConverter::toString((size_t)((HWND)winId()));
#else
   QX11Info x_info = x11Info();
   widget_handle = Ogre::StringConverter::toString((unsigned long)x_info.display())+
           ":" + Ogre::StringConverter::toString((unsigned int)x_info.screen())+
           ":"+ Ogre::StringConverter::toString((unsigned long)this->winId());
#endif

    view_config["externalWindowHandle"] = widget_handle;
    m_Window = m_Root->createRenderWindow(" The OgreRenderWindow", width(), height(), false, &view_config);

    createCamera();
    createViewport();
    //createLight();
    createDefaultScene();
    //setSceneType(m_type);
  }

void BLXCore::setObjectScene(const Ogre::String m_Ent, const Ogre::Vector3 m_Dim, const Ogre::Vector3 m_Pos)
{
    m_EntityName = m_Ent;
    m_Dimension =  m_Dim;
    m_Position = m_Pos;
    m_SceneMgr->destroyAllEntities();
    m_Entity = m_SceneMgr->createEntity("home_test", m_EntityName);
    m_Node->setPosition(m_Position);
    m_Node->setScale(m_Dimension);
}

void BLXCore::createDefaultScene()
{
    principalNode = m_SceneMgr->getRootSceneNode()->createChildSceneNode("principal_node");
    principalNode->setScale(150, 1, 150);
    principalNode->setPosition(Ogre::Vector3::ZERO);

    m_Entity = m_SceneMgr->createEntity("home_test", m_EntityName);
    m_Node = principalNode->createChildSceneNode("node_test");
    m_Node->attachObject(m_Entity);
    m_Node->setPosition(m_Position);
    m_Node->setScale(m_Dimension);
}

void BLXCore::switchScene(SceneType stype)
{/*
    switch(stype)
    {
    case Reset:
        m_SceneMgr->clearScene();
        createLight();
        createDefaultScene();
        break;

    case wGrid:
        m_SceneMgr->clearScene();
        createLight();
        createDefaultScene();
        createGrid(30, 30, 0.12);
        break;

    case wPlane:
        m_SceneMgr->clearScene();
        createDefaultScene();
        createLight();
        createPlane();
        break;
   }
    update();
    */
}

void BLXCore::setSceneType(SceneType type)
{/*
    m_type = type;
   // m_SceneMgr->destroyAllEntities();
    switchScene(m_type);
 */
}


void BLXCore::createCamera()
{
    m_Camera = m_SceneMgr->createCamera("m_Camera");
    static const Ogre::Vector3 camera_pos(0, 10, 300);
    m_Camera->setPosition(camera_pos);
    m_Camera->lookAt(0, 0, 0);
    m_Camera->setNearClipDistance(3);
    m_Camera->setFarClipDistance(3000);
    //cam_orientation =  m_Camera->getOrientation();

}

void BLXCore::createLight()
{
    Ogre::Light *house_light = m_SceneMgr->createLight("main light");
    //house_light->setType(Ogre::Light::LT_SPOTLIGHT);
    //house_light->setAttenuation();
    house_light->setDiffuseColour(1, 1, 1);
    house_light->setSpecularColour(1, 1, 1);
    house_light->setPosition(0, 100, 100);
}

void BLXCore::createViewport()
{
    m_Viewport = m_Window->addViewport(m_Camera);
    m_Viewport->setBackgroundColour(Ogre::ColourValue(0, 0, 0));
    m_Camera->setAspectRatio(Ogre::Real(width()) / Ogre::Real(height()));
}

void BLXCore::createGrid(int n_col, int n_row, float size)
{
    //Have create otherNode befor call this function
    //m_SceneMgr->destroyEntity("object_scene");

    Ogre::ManualObject* m_object = m_SceneMgr->createManualObject("object_scene");
    otherNode = principalNode->createChildSceneNode("object_scene");

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

    otherNode->setPosition(0, -0.41, 0);
    otherNode->attachObject(m_object);

}

void BLXCore::createPlane()
{
    //Have to create otherNode befor call this function
    //m_SceneMgr->destroyEntity("object_scene");

    Ogre::Entity *m_plane = m_SceneMgr->createEntity("object_scene", "Plane.mesh");
    otherNode = principalNode->createChildSceneNode("plane node");
    otherNode->setScale(5, 1, 5);
    otherNode->setPosition(0, -0.4, 0);
    otherNode->attachObject(m_plane);
}

void BLXCore::setCameraPosition(const Ogre::Vector3 &Position)
{
    m_Camera->setPosition(Position);
    update();
    emit changeCameraPosition(Position);
}

void BLXCore::setBackground(QColor &m_color)
{
    if(m_Viewport)
    {
        Ogre::ColourValue ogre_colour;
        ogre_colour.setAsARGB(m_color.rgba());
        m_Viewport->setBackgroundColour(ogre_colour);
    }
}

void BLXCore::take_screen_shot(const std::string m_string)
{
    m_Window->writeContentsToTimestampedFile("blx_"+m_string, ".png");
}

void BLXCore::setCameraView(VIEW m_view)
{
    m_Camera->setFixedYawAxis(false);
    m_Camera->setOrientation(Ogre::Quaternion::IDENTITY);
   //  m_Node->setPosition(Ogre::Vector3(0, 0, 0));
   // m_Node->setOrientation(Ogre::Quaternion::IDENTITY);

    switch (m_view) {
    case UP:
       setCameraPosition(Ogre::Vector3(0, 300, 0));
        break;

    case BOTTOM:
        setCameraPosition(Ogre::Vector3(0, -300, 0));
        break;

    case FRONT:
        setCameraPosition(Ogre::Vector3(0, 0, 300));
        break;

    case BACK:
        setCameraPosition(Ogre::Vector3(0, 0, -300));
        break;
    case LEFT:
       setCameraPosition(Ogre::Vector3(-300, 0, 0));
        break;

    case RIGHT:
        setCameraPosition(Ogre::Vector3(300, 0, 0));
        break;

    }

    m_Camera->lookAt(0, -1, 0);
}

Ogre::Vector3 BLXCore::getm_CameraPosition()
{
    Ogre::Vector3 v = m_Camera->getPosition();
    return v;
}

Ogre::Quaternion BLXCore::getm_CameraOrientation()
{
    return m_Camera->getOrientation();
}

void BLXCore::setNodeYaw(int val)
{
    m_Node->yaw(Ogre::Degree(val));
    update();
}

void BLXCore::keyPressEvent(QKeyEvent *evt)
{
    static QMap< int, Ogre::Vector3> key_coord_modification_mapping;
     static bool mapping_initialised = false;

     if(!mapping_initialised)
     {
       key_coord_modification_mapping[Qt::Key_PageUp]      = Ogre::Vector3(0, 5, 0);
       key_coord_modification_mapping[Qt::Key_PageDown]    = Ogre::Vector3(0, -5, 0);

       key_coord_modification_mapping[Qt::Key_Up]          = Ogre::Vector3(0, 0, -5);
       key_coord_modification_mapping[Qt::Key_Down]        = Ogre::Vector3(0, 0, 5);
       key_coord_modification_mapping[Qt::Key_Left]        = Ogre::Vector3(5, 0, 0);
       key_coord_modification_mapping[Qt::Key_Right]       = Ogre::Vector3(-5, 0, 0);
     }

     mapping_initialised = true;

     QMap<int, Ogre::Vector3>::iterator key_pressed = key_coord_modification_mapping.find(evt->key());
     if(key_pressed !=  key_coord_modification_mapping.end() && m_Camera)
     {
           const Ogre::Vector3 &actual_camera_pos = m_Camera->getPosition();
           const Ogre::Vector3 &n_position = m_Camera->getOrientation()*key_pressed.value();
           setCameraPosition(actual_camera_pos + n_position);
           evt->accept();
     }

   // m_Node->setPosition(Ogre::Vector3(0, 0, 0));
  //  m_Node->setOrientation(Ogre::Quaternion::IDENTITY);

     switch (evt->key())
     {
     case Qt::Key_U:
            setCameraView(UP);
             break;

     case Qt::Key_J:
            setCameraView(BOTTOM);
             break;

     case Qt::Key_I:
           setCameraView(LEFT);
             break;

     case Qt::Key_K:
           setCameraView(RIGHT);
             break;

     case Qt::Key_O:
           setCameraView(FRONT);
             break;
     case Qt::Key_L:
           setCameraView(BACK);
             break;

     case Qt::Key_R:
           m_Camera->yaw(Ogre::Degree(2));
             break;

     case Qt::Key_T:
             m_Camera->yaw(Ogre::Degree(-2));
             break;

     case Qt::Key_F:
              m_Node->yaw(Ogre::Degree(2));
              break;
     case Qt::Key_G:
              m_Node->yaw(Ogre::Degree(-2));
              break;

     default:
         evt->ignore();
         break;
     }
     update();
     evt->accept();

}

void BLXCore::mouseMoveEvent(QMouseEvent *evt)
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
        const Ogre::Vector3 &actual_camera_pos = m_Camera->getPosition();
        setCameraPosition(actual_camera_pos + camera_translation);

        old_position = pos;
        evt->accept();

    }
    else
    {
        evt->accept();
    }

}


void BLXCore::mousePressEvent(QMouseEvent *evt)
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

void BLXCore::mouseReleaseEvent(QMouseEvent *evt)
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

QPaintEngine *BLXCore::paintEngine() const
{
    return NULL;
}

void BLXCore::moveEvent(QMoveEvent *evt)
{
   QWidget::moveEvent(evt);

   if(evt->isAccepted() && m_Window)
   {
       m_Window->windowMovedOrResized();
       update();
   }
}

void BLXCore::paintEvent(QPaintEvent *evt)
{
   if(!m_Root)
   {
       setupOgreSystem();
   }

   m_Root->_fireFrameStarted();
   m_Window->update();
   m_Root->_fireFrameEnded();
    evt->accept();
}

void BLXCore::resizeEvent(QResizeEvent *evt)
{
    QWidget::resizeEvent(evt);

    if(evt->isAccepted())
    {
        const QSize &new_size = evt->size();
        if(m_Window)
        {
            m_Window->resize(new_size.width(), new_size.height());
            m_Window->windowMovedOrResized();
        }

        if(m_Camera)
        {
            Ogre::Real aspect_ratio = Ogre::Real(new_size.width()/Ogre::Real(new_size.height()));
            m_Camera->setAspectRatio(aspect_ratio);
        }
    }
}

void BLXCore::showEvent(QShowEvent *evt)
{
    QWidget::showEvent(evt);
}

void BLXCore::wheelEvent(QWheelEvent *evt)
{
   Ogre::Vector3 z_translation(evt->delta()/20, evt->delta()/20, evt->delta()/20);

   if(evt->modifiers().testFlag(Qt::ControlModifier))
   {
       z_translation.z *= turbo_modifier;
   }

   const Ogre::Vector3 &actual_camera_position = m_Camera->getPosition();
   setCameraPosition(actual_camera_position + z_translation);

   evt->accept();
}

