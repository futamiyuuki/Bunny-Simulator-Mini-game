#ifndef __Cube__Camera__
#define __Cube__Camera__

#include <GLUT/glut.h>
#include "Vector3.h"
#include "Matrix4.h"

class Camera
{
protected:
  Matrix4 c;
  Vector3 e;
  Vector3 d;
  Vector3 up;
  
public:
  Camera();
  Camera(Vector3, Vector3, Vector3);
  void update();
    void change(Matrix4 m);
  Vector3 ee() const { return e; }
  Vector3 dd() const { return d; }
  Vector3 upp() const { return up; }
  GLdouble* getGLMatrix();
    Matrix4 getMatrix();
    void move(Vector3,Vector3);
  
};

#endif /* defined(__Cube__Camera__) */
