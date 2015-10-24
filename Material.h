#ifndef __PA5__Material__
#define __PA5__Material__

#include <stdio.h>
#include "Vector3.h"
#include "Vector4.h"

class Material {
private:
    Vector4 ambient;
    Vector4 diffuse;
    Vector4 specular;
    Vector4 emission;
    float shine[1];
public:
    Material();
    Material(Vector4 amb, Vector4 dif, Vector4 spec, Vector4 emis, float shi);
    void create();
    
};

#endif /* defined(__PA5__Material__) */
