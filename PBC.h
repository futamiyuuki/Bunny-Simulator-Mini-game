#ifndef __Final__PBC__
#define __Final__PBC__

#include "Vector3.h"
#include "Matrix4.h"
#include "Shader.h"
#include "BC.h"
#include "Geode.h"

class PBC : public Geode{
private:
    int num;
    BC **set;
    Vector3 ctrl[4][4];
    Vector4 gbezx,gbezy,gbezz;
    Matrix4 bbez = Matrix4(-1,3,-3,1,
                           3,-6,3,0,
                           -3,3,0,0,
                           1,0,0,0);
    
public:
    PBC(Vector3*, int, int);
    void render();
    void update();
    Vector3 getBC(double);
    Vector3 getPoint(double);
};

#endif /* defined(__Final__PBC__) */
