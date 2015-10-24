#ifndef __PA5__Cone__
#define __PA5__Cone__

#include <stdio.h>
#include "Geode.h"
#include "Material.h"

class Cone : public Geode {
private:
    double b;
    double h;
    int sta, sli;
    //Material *mat;
public:
    Cone(double base, double height, int stack, int slice);
    void render();
    void update();
};

#endif /* defined(__PA5__Cone__) */
