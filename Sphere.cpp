#include <iostream>
#include "Sphere.h"

using namespace std;

Sphere::Sphere(double radius, int slice, int stack, string state, double rrr, double ggg, double bbb) {
    r = radius;
    sl = slice;
    st = stack;
    s = state;
    rr = rrr;
    gg = ggg;
    bb = bbb;
    //mat = material;
}

void Sphere::render() {
    //glDisable(GL_LIGHTING);
    glColor3d(1,0,1);
    if(s.compare("solid")==0)
        glutSolidSphere(r,sl,st);
    else if(s.compare("wire")==0)
        glutWireSphere(r,sl,st);
    else
        cout << "gg I don't know string" << endl;
    //glEnable(GL_LIGHTING);
    ////mat->create();
        
}

void Sphere::update() { }