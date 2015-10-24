#ifndef __PA5__Light__
#define __PA5__Light__

#include <stdio.h>
#include "Vector3.h"
#include "Vector4.h"

class Light {
private:
    Vector4 ambient;
    Vector4 diffuse;
    Vector4 specular;
    Vector4 position;
    Vector3 dir;
    float exp,cutoff,constAtt,linAtt,quaAtt;
    bool spotlight;
public:
    Light(Vector4 amb, Vector4 dif, Vector4 spec, Vector4 pos);
    Light(Vector4 amb, Vector4 dif, Vector4 spec, Vector4 pos, Vector3 d, float e, float c, float ca, float la, float qa);
    void create();
};

#endif /* defined(__PA5__Light__) */
