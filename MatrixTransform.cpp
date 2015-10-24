//
//  MatrixTransform.cpp
//  PA4
//
//  Created by Hubert Hsiung on 11/13/14.
//  Copyright (c) 2014 Hubert Hsiung. All rights reserved.
//

#include "MatrixTransform.h"
#include <GLUT/glut.h>

MatrixTransform::MatrixTransform(Matrix4 c) {
    m = c;
}

void MatrixTransform::draw(Matrix4& c) {
    Matrix4 cnew = c * m;
    Group::draw(cnew);
}

void MatrixTransform::update() {}

void MatrixTransform::change(Matrix4 mm) {
    m = mm;
}

Matrix4 MatrixTransform::getM() {
    return m;
}