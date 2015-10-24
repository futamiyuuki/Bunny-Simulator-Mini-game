#ifndef __PA4__Group__
#define __PA4__Group__

#include <list>
#include "Node.h"

using namespace std;

class Group : public Node {
protected:
    list<Node*> child;
public:
    Group();
    ~Group();
    virtual void draw(Matrix4&);
    virtual void update();
    void addChild(Node*);
    void removeChild(Node*);
    void removeAll();
};

#endif /* defined(__PA4__Group__) */
