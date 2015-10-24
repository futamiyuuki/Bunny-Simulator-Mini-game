#ifndef __Final__BC__
#define __Final__BC__

#include "Vector3.h"
#include "Matrix4.h"
#include "Geode.h"
#include "Shader.h"

class BC : public Geode {
private:
    double len;
    Vector3 ctrl[16];
    Vector4 gbezx,gbezy,gbezz;
    Matrix4 bbez = Matrix4(-1,3,-3,1,
                           3,-6,3,0,
                           -3,3,0,0,
                           1,0,0,0);
    
public:
    BC(Vector3*, double);
    void render();
    void update();
    Vector3 getBC(double);
    Vector3 getPoint(double);
};

#endif /* defined(__Final__BC__) */
