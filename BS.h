#ifndef __Final__BS__
#define __Final__BS__

#include <stdio.h>
#include "Vector3.h"

class BS {
private:
    Vector3 c;
    double r;
public:
    BS() { };
    BS(Vector3,double);
    Vector3 getCenter();
    double getRadius();
    void setCenter(Vector3);
    void setRadius(double);
};

#endif /* defined(__Final__BS__) */
