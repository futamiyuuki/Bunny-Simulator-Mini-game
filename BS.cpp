#include "BS.h"

BS::BS(Vector3 center, double radius) {
    c = center;
    r = radius;
}

Vector3 BS::getCenter() {
    return c;
}

double BS::getRadius() {
    return r;
}

void BS::setCenter(Vector3 center) {
    c = center;
}

void BS::setRadius(double radius) {
    r = radius;
}