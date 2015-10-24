#ifndef __PA4__MatrixTransform__
#define __PA4__MatrixTransform__

#include "Matrix4.h"
#include "Vector4.h"
#include "Group.h"

class MatrixTransform : public Group {
private:
    Matrix4 m;
public:
    MatrixTransform(Matrix4 c);
    void draw(Matrix4& c);
    void update();
    void change(Matrix4 mm);
    Matrix4 getM();
};

#endif /* defined(__PA4__MatrixTransform__) */
