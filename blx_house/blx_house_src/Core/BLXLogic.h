
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

#ifndef __BLXLOGIC_h
#define __BLXLOGIC_h

#include <QtGui>
#include <iostream>
#include <fstream>

extern std::string convertToString(int value);
extern std::string convertToCapital(std::string str);
extern std::string readCode();

struct Mesh
{
  std::string mesh_name;
  float mesh_position[3];
  float mesh_scale[3];
};

typedef struct Mesh Mesh;

class BLXLogic: public QWidget
{

    Q_OBJECT

public:
  BLXLogic();
  void write_in(const std::string &m_file, Mesh* m_Mesh);
  void copyBLXObject(const QString m_file);     //copy a file box to database
  void saveBLXObject();
  void deleteBLXObject(const std::string m_file);    //delete a file box to database
  QVector<Mesh>selectBLXObject(const QString &blx_file, const QString &object_code);    //select a mod from the database
  void updateBLXFileConfig(const std::string &new_file);

public slots:
  void chooseBLXObject();
  void setCode();

private:
   std::string code;
};
#endif	//__BLXLOGIC_h
