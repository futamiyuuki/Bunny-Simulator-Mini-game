#ifndef __PA4__Cube__
#define __PA4__Cube__

#include "Geode.h"

class Cube : public Geode {
private:
    double x;
    double y;
    double z;
    double r;
    double g;
    double b;
    //void render(); //implenting render here instead of draw due to inheritance, see piazza.
public:
    Cube(double,double,double,double,double,double);
    void update();
    void render(); //implenting render here instead of draw due to inheritance, see piazza.
};

#endif /* defined(__PA4__Cube__) */
