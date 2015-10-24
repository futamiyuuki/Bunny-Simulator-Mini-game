#include "BC.h"
#include "math.h"


BC::BC(Vector3 *arr, double numo) {
    len = numo;
    for(int i = 0; i < 4; i++)
        ctrl[i] = arr[i];
    
    
    gbezx = Vector4(ctrl[0].getX(),ctrl[1].getX(),ctrl[2].getX(),ctrl[3].getX());
    gbezy = Vector4(ctrl[0].getY(),ctrl[1].getY(),ctrl[2].getY(),ctrl[3].getY());
    gbezz = Vector4(ctrl[0].getZ(),ctrl[1].getZ(),ctrl[2].getZ(),ctrl[3].getZ());
    
}

void BC::update() { }

Vector3 BC::getBC(double t) {
    Vector4 tvector(t * t * t, t * t, t, 1);
    Vector4 resx = bbez.reversemul(gbezx);
    Vector4 resy = bbez.reversemul(gbezy);
    Vector4 resz = bbez.reversemul(gbezz);
    return Vector3(resx * tvector,
                   resy * tvector,
                   resz * tvector);
}

void BC::render() {
    glColor3f(1.0,1.0,1.0);
    glLineWidth(40);
    glBegin(GL_LINE_STRIP);
    for(int i = 0; i < len; i++) {
        double t = i / (len - 1);
        Vector3 temp = getBC(t);
        glVertex3f(temp.getX(),temp.getY(),temp.getZ());
    }
    glEnd();
}

Vector3 BC::getPoint(double i) {
    double t = i / (len - 1);
    Vector3 temp = getBC(t);
    return temp;
}