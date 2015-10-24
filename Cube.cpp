#include <iostream>
#include "Cube.h"

using namespace std;

Cube::Cube(double xx, double yy, double zz, double rr, double gg, double bb) {
    x = xx;
    y = yy;
    z = zz;
    r = rr;
    g = gg;
    b = bb;
}

void Cube::update() {}

void Cube::render() {
    glColor3d(r,g,b);
    glScaled(1.0,y/x,z/x);
    
    glutSolidCube(x);
    //cout << "rock solid" << endl;
    
}