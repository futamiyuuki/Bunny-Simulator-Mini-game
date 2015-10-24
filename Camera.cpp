#include "Camera.h"

Camera::Camera() {
    c.identity();
}

Camera::Camera(Vector3 e, Vector3 d, Vector3 up) {
    this->e = e;
    this->d = d;
    this->up = up;
    update();
}

void Camera::update() {
    Vector3 w = e - d;
    w.normalize();
    Vector3 u = up.cross(w);
    u.normalize();
    Vector3 v = w.cross(u);
    w.normalize();
    e.setZ(e.getZ());
    Matrix4 rot;
    rot = Matrix4(u.getX(), u.getY(), u.getZ(),0,
                v.getX(), v.getY(), v.getZ(),0,
                w.getX(), w.getY(), w.getZ(),0,
                0, 0, 0, 1);
    Matrix4 trans;
    trans.identity();
    trans.makeTranslate(-e.getX(),-e.getY(),-e.getZ());
    c = rot * trans;
}

void Camera::change(Matrix4 x) {
    c = x * c;
}

GLdouble* Camera::getGLMatrix() {
    return c.getPointer();
}

Matrix4 Camera::getMatrix() {
    return c;
}

void Camera::move(Vector3 pos, Vector3 lookat) {
    this->e = pos;
    this->d = lookat;
    update();
}