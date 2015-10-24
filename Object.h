#ifndef __PA5__Object__
#define __PA5__Object__

#include <vector>
#include "Geode.h"
#include "Parser.h"
#include "Vector3.h"

using namespace std;

class Object : public Geode {
private:
    vector<Vector3> *ver;
    vector<Vector3> *nor;
    vector<Vector3> *vi;
    vector<Vector3> *ni;
    vector<Vector3> *c;
    Vector3 max;
    Vector3 min;
public:
    Object(vector<Vector3> *vertex, vector<Vector3> *normal, vector<Vector3> *vindex, vector<Vector3> *nindex, vector<Vector3> *color, Vector3 mini, Vector3 maxi);
    void update();
    void render();
};

#endif /* defined(__PA5__Object__) */
