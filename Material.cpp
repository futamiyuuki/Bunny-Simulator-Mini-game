#include "Material.h"
#include <GLUT/glut.h>

Material::Material() { }

Material::Material(Vector4 amb, Vector4 dif, Vector4 spec, Vector4 emis, float shi) {
    ambient = amb;
    diffuse = dif;
    specular = spec;
    emission = emis;
    shine[0] = shi;
}

void Material::create() {
    float amb[] = {ambient.getX(), ambient.getY(), ambient.getZ(), ambient.getW()};
    float dif[] = {diffuse.getX(), diffuse.getY(), diffuse.getZ(), diffuse.getW()};
    float spec[] = {specular.getX(), specular.getY(), specular.getZ(), specular.getW()};
    float emis[] = {emission.getX(), emission.getY(), emission.getZ(), emission.getW()};
    glMaterialfv(GL_FRONT,GL_AMBIENT,amb);
    glMaterialfv(GL_FRONT,GL_DIFFUSE,dif);
    glMaterialfv(GL_FRONT,GL_SPECULAR,spec);
    glMaterialfv(GL_FRONT,GL_SHININESS, shine);
    glMaterialfv(GL_FRONT,GL_EMISSION,emis);
}