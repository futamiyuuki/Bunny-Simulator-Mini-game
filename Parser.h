#ifndef __Qube__Parser__
#define __Qube__Parser__

#include <vector>
#include "Vector3.h"

using namespace std;

struct XYZ{
    float x, y, z;
};

class Parser
{
public:
    static void parseObj(char* name, vector<Vector3> &vertex, vector<Vector3> &normal, vector<Vector3> &vi, vector<Vector3> &ni, vector<Vector3> &color, Vector3 &max, Vector3 &min, bool bunny);
};

#endif /* defined(__Qube__Parser__) */
