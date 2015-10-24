#pragma once
#include <string>
#include "Vector3.h"
class Vector4
{
private:
	double x, y, z, w;

public:
	Vector4();
	Vector4(double, double, double, double);
	Vector4 operator+(const Vector4&);
	Vector4 operator-(const Vector4&);
    double operator*(const Vector4& v);
	~Vector4();

	void dehomogenize();
	void print(std::string);

	double getX() const;
	double getY() const;
	double getZ() const;
	double getW() const;
    void setX(double);
    void setY(double);
    void setZ(double);
    void setW(double);
    Vector3 turn3();
};

