#ifndef PA4_Node_h
#define PA4_Node_h

#include "Matrix4.h"

class Node {
public:
    Node();
    virtual void draw(Matrix4&) = 0;
    virtual void update() = 0;
};

#endif
