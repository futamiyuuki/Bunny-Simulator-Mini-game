#include "Light.h"
#include "Matrix4.h"
#include <GLUT/glut.h>

Light::Light(Vector4 amb, Vector4 dif, Vector4 spec, Vector4 pos) {
    ambient = amb;
    diffuse = dif;
    specular = spec;
    position = pos;
    dir = Vector3(0.0,0.0,-1.0); //default values for spotlight
    exp = 0.0;
    cutoff = 180.0;
    constAtt = 1.0;
    linAtt = 0.0;
    quaAtt = 0.0;
    spotlight = false; //this is a constructor for point light
}

Light::Light(Vector4 amb, Vector4 dif, Vector4 spec, Vector4 pos, Vector3 d, float e, float c, float ca, float la, float qa) {
    ambient = amb;
    diffuse = dif;
    specular = spec;
    position = pos;
    dir = d;
    exp = e;
    cutoff = c;
    constAtt = ca;
    linAtt = la;
    quaAtt = qa;
    spotlight = true; //constructor for spotlight
}

void Light::create() {
    glMatrixMode(GL_MODELVIEW);
    Matrix4 id = Matrix4();
    glLoadMatrixd(id.getPointer());
    float amb[] = {ambient.getX(), ambient.getY(), ambient.getZ(), ambient.getW()};
    float dif[] = {diffuse.getX(), diffuse.getY(), diffuse.getZ(), diffuse.getW()};
    float spec[] = {specular.getX(), specular.getY(), specular.getZ(), specular.getW()};
    float pos[] = {position.getX(), position.getY(), position.getZ(), position.getW()};
    if(!spotlight) {
        glLightfv(GL_LIGHT1, GL_AMBIENT, amb);
        glLightfv(GL_LIGHT1, GL_DIFFUSE, dif);
        glLightfv(GL_LIGHT1, GL_SPECULAR, spec);
        glLightfv(GL_LIGHT1, GL_POSITION, pos);
        glLightf(GL_LIGHT1, GL_CONSTANT_ATTENUATION, constAtt);
        glLightf(GL_LIGHT1, GL_LINEAR_ATTENUATION, linAtt);
        glLightf(GL_LIGHT1, GL_QUADRATIC_ATTENUATION, quaAtt);
        glEnable(GL_LIGHT1);
    } else {
        float sd[] = {dir.getX(), dir.getY(), dir.getZ()};
        glLightfv(GL_LIGHT0, GL_AMBIENT, amb);
        glLightfv(GL_LIGHT0, GL_DIFFUSE, dif);
        glLightfv(GL_LIGHT0, GL_SPECULAR, spec);
        glLightfv(GL_LIGHT0, GL_POSITION, pos);
        glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION, constAtt);
        glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION, linAtt);
        glLightf(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, quaAtt);
        glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, cutoff);
        glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, sd);
        glLightf(GL_LIGHT0, GL_SPOT_EXPONENT, exp);
        glEnable(GL_LIGHT0);
    }
    
}