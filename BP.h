#ifndef __PA6__BP__
#define __PA6__BP__

#include "Vector3.h"
#include "Matrix4.h"
#include "Geode.h"
#include "Shader.h"

class BP : public Geode {
private:
    Vector3 ctrl[16];
    int x, y;
    GLuint cm;
    Matrix4 gx,gy,gz;
    Matrix4 cx,cy,cz;
    Matrix4 bbez = Matrix4(-1,3,-3,1,
                            3,-6,3,0,
                            -3,3,0,0,
                            1,0,0,0);
    bool shade = false;
    double coeff(double,double,double);
    double combo(double,double);
    double factorial(double);
    Shader *shader;
    
public:
    BP(Vector3*, int, int);
    void render();
    void update();
    Vector3 getPoint(double,double);
    void wave(double,double);
    void setCM(GLuint s);
    void shadeSwitch();
};

#endif /* defined(__PA6__BP__) */
