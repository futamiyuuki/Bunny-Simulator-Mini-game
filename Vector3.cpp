#include "Vector3.h"
#include <math.h>
#include <iostream>

Vector3::Vector3() { this->x = this->y = this->z = 0; }

Vector3::Vector3(double x, double y, double z) {
	this->x = x;
	this->y = y;
	this->z = z;
}

Vector3::~Vector3() {}

void Vector3::create(double x, double y, double z) {
    this->x = x;
    this->y = y;
    this->z = z;
}

Vector3 Vector3::operator+(const Vector3& v) {
	Vector3 *v1 = new Vector3(this->x + v.x, this->y + v.y, this->z + v.z);
	return *v1;
}

Vector3 Vector3::operator-(const Vector3& v) {
	Vector3 *v1 = new Vector3(this->x - v.x, this->y - v.y, this->z - v.z);
	return *v1;
}

void Vector3::negate() {
	x = -x;
	y = -y;
	z = -z;
}

Vector3 Vector3::scale(double s) {
    Vector3 *v1 = new Vector3(x*s,y*s,z*s);
    return *v1;
}

double Vector3::dot(const Vector3& v1, const Vector3& v2) {
	return(v1.x * v2.x + v1.y * v2.y + v1.z *v2.z);
}

Vector3 Vector3::cross(const Vector3& v1, const Vector3& v2) {
	x = v1.y * v2.z - v1.z * v2.y;
	y = v1.z * v2.x - v1.x * v2.z;
	z = v1.x * v2.y - v1.y * v2.x;
	Vector3 *v3 = new Vector3(x, y, z);
	return *v3;
}

Vector3 Vector3::cross(const Vector3& v) {
    double a = y * v.z - z * v.y;
    double b = z * v.x - x * v.z;
    double c = x * v.y - y * v.x;
    Vector3 *v3 = new Vector3(a, b, c);
    return *v3;
}

double Vector3::length() {
	return(sqrt(x*x + y*y + z*z));
}

void Vector3::normalize() {
    double l = length();
    this->x = this->x/l;
    this->y = this->y/l;
    this->z = this->z/l;
}

void Vector3::print(std::string s) {
	//printf("%s \n %d %d %d \n", s, x, y, z);
	std::cout << s << std::endl << x << " " << y << " " << z << std::endl;
}

double Vector3::getX() const {
	return this->x;
}

double Vector3::getY() const {
	return this->y;
}

double Vector3::getZ() const {
	return this->z;
}

void Vector3::setX(double xx) {
    this->x = xx;
}

void Vector3::setY(double yy) {
    this->y = yy;
}

void Vector3::setZ(double zz) {
    this->z = zz;
}