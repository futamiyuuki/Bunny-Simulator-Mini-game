#ifndef __PA4__Sphere__
#define __PA4__Sphere__

#include "Geode.h"
#include "Material.h"

class Sphere : public Geode {
private:
    double r;
    int sl;
    int st;
    std::string s;
    double rr, gg, bb;
    Material *mat;
public:
    Sphere(double, int, int, std::string, double, double, double);
    void render(); //implenting render here instead of draw due to inheritance, see piazza.
    void update();
};

#endif /* defined(__PA4__Sphere__) */
