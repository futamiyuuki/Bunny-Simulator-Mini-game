#include "Cone.h"
#include <GLUT/glut.h>

Cone::Cone(double base, double height, int stack, int slice) {
    b = base;
    h = height;
    sta = stack;
    sli = slice;
}

void Cone::render() {
    glDisable(GL_LIGHTING);
    glColor3d(0,1,0);
    glutSolidCone(b,h,sli,sta);
    glEnable(GL_LIGHTING);
}

void Cone::update() {}