#ifndef PA4_Geode_h
#define PA4_Geode_h

#include <iostream>
#include <GLUT/glut.h>
#include "Node.h"

class Geode : public Node {
public:
    Geode();
    void draw(Matrix4& c);
    virtual void update() = 0;
protected:
    virtual void render() = 0;
};

#endif
