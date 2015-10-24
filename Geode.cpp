#include "Geode.h"

using namespace std;

Geode::Geode() { }

void Geode::draw(Matrix4& c) {
    //cout << "ys this not printing" << endl;
    glMatrixMode(GL_MODELVIEW);
    glLoadMatrixd(c.getPointer());
    render();
};