#include <math.h>
#include "Matrix4.h"
#include <iostream>

Matrix4::Matrix4()
{
    identity();
}

Matrix4::Matrix4(double m00, double m01, double m02, double m03,
                   double m10, double m11, double m12, double m13,
                   double m20, double m21, double m22, double m23,
                   double m30, double m31, double m32, double m33) {
    m[0][0] = m00;
    m[1][0] = m01;
    m[2][0] = m02;
    m[3][0] = m03;
    m[0][1] = m10;
    m[1][1] = m11;
    m[2][1] = m12;
    m[3][1] = m13;
    m[0][2] = m20;
    m[1][2] = m21;
    m[2][2] = m22;
    m[3][2] = m23;
    m[0][3] = m30;
    m[1][3] = m31;
    m[2][3] = m32;
    m[3][3] = m33;
}

Matrix4& Matrix4::operator=(const Matrix4& m2)
{
  if (this != &m2)
  {
    for (int i=0; i<4; ++i)
    {
      for (int j=0; j<4; ++j)
      {
        m[i][j] = m2.m[i][j];
      }
    }
  }
  return *this;
}

double Matrix4::get(int a, int b) {
    return m[a][b];
}

// return pointer to matrix elements
double* Matrix4::getPointer()
{
  return &m[0][0];
}

// set matrix to identity matrix
void Matrix4::identity()
{
  for (int i=0; i<4; ++i)
  {
    for (int j=0; j<4; ++j)
    {
      if (i==j) 
        m[i][j] = 1.0; 
      else 
        m[i][j] = 0.0;
    }
  }
}

// transpose the matrix (mirror at diagonal)
void Matrix4::transpose()
{
  Matrix4 temp;
  for (int i=0; i<4; ++i)
  {
    for (int j=0; j<4; ++j)
    {
      temp.m[j][i] = m[i][j];
    }
  }
  *this = temp;  // copy temporary values to this matrix
}

// Creates a rotation matrix which rotates about the y axis.
// angle is expected in degrees
void Matrix4::makeRotateY(double angle)
{
  angle = angle / 180.0 * M_PI;  // convert from degrees to radians
  identity();
	m[0][0] = cos(angle);
	m[0][2] = -sin(angle);
	m[2][0] = sin(angle);
	m[2][2] = cos(angle);
}

Matrix4& Matrix4::operator*(const Matrix4& m) {
	Matrix4 *m1 = new Matrix4();
	
	for (int r = 0; r < 4; r++) {
		for (int c = 0; c < 4; c++) {
			double sum = 0.0;
			for (int i = 0; i < 4; i++) {
				sum += this->m[i][c] * m.m[r][i];
			}
			m1->m[r][c] = sum;
		}
	}
	return *m1;
}

Vector4& Matrix4::operator*(const Vector4& v) {
	Vector4 *v1 = new Vector4(
		v.getX()*this->m[0][0] + v.getY()*this->m[1][0] +
			v.getZ()*this->m[2][0] + v.getW()*this->m[3][0],
		v.getX()*this->m[0][1] + v.getY()*this->m[1][1] +
			v.getZ()*this->m[2][1] + v.getW()*this->m[3][1],
		v.getX()*this->m[0][2] + v.getY()*this->m[1][2] +
			v.getZ()*this->m[2][2] + v.getW()*this->m[3][2],
		v.getX()*this->m[0][3] + v.getY()*this->m[1][3] +
			v.getZ()*this->m[2][3] + v.getW()*this->m[3][3]);
	return *v1;
}

Vector4& Matrix4::reversemul(const Vector4& v) {
    Vector4 *v1 = new Vector4(
                              v.getX()*this->m[0][0] + v.getY()*this->m[0][1] +
                              v.getZ()*this->m[0][2] + v.getW()*this->m[0][3],
                              v.getX()*this->m[1][0] + v.getY()*this->m[1][1] +
                              v.getZ()*this->m[1][2] + v.getW()*this->m[1][3],
                              v.getX()*this->m[2][0] + v.getY()*this->m[2][1] +
                              v.getZ()*this->m[2][2] + v.getW()*this->m[2][3],
                              v.getX()*this->m[3][0] + v.getY()*this->m[3][1] +
                              v.getZ()*this->m[3][2] + v.getW()*this->m[3][3]);
    return *v1;
}

void Matrix4::makeRotateX(double angle) {
	angle = angle / 180.0 * M_PI;  // convert from degrees to radians
	identity();
	m[1][1] = cos(angle);
	m[1][2] = sin(angle);
	m[2][1] = -sin(angle);
	m[2][2] = cos(angle);
}

void Matrix4::makeRotateZ(double angle) {
	angle = angle / 180.0 * M_PI;  // convert from degrees to radians
	identity();
	m[0][0] = cos(angle);
	m[0][1] = sin(angle);
	m[1][0] = -sin(angle);
	m[1][1] = cos(angle);
}

void Matrix4::makeRotate(double a, const Vector3& v) {
	a = a / 180.0 * M_PI;
	double t = 1 - cos(a);
	double c = cos(a);
	double s = sin(a);
	double x = v.getX();
	double y = v.getY();
	double z = v.getZ();

	identity();
	m[0][0] = t * x * x + c;
	m[0][1] = t * x * y + s * z;
	m[0][2] = t * x * z - s * y;
	m[1][0] = t * x * y - s * z;
	m[1][1] = t * y * y + c;
	m[1][2] = t * y * z + s * x;
	m[2][0] = t * x * z + s * y;
	m[2][1] = t * y * z - s * x;
	m[2][2] = t * z * z + c;
}

void Matrix4::makeScale(double sx, double sy, double sz) {
	identity();
	this->m[0][0] = sx;
	this->m[1][1] = sy;
	this->m[2][2] = sz;
}

void Matrix4::makeTranslate(double tx, double ty, double tz) {
	identity();
	this->m[3][0] = tx;
	this->m[3][1] = ty;
	this->m[3][2] = tz;
}

void Matrix4::print(std::string s) {
	/*
	printf("%s \n %d %d %d %d \n %d %d %d %d \n %d %d %d %d \n %d %d %d %d \n",	s,
		this->m[0][0], this->m[0][1], this->m[0][2], this->m[0][3],
		this->m[1][0], this->m[1][1], this->m[1][2], this->m[1][3],
		this->m[2][0], this->m[2][3], this->m[2][3], this->m[2][3],
		this->m[3][0], this->m[3][1], this->m[3][2], this->m[3][3]);
	*/
	std::cout << s << std::endl;
	for (int r = 0; r < 4; r++) {
		for (int c = 0; c < 4; c++) {
			std::cout << this->m[c][r] << " ";
		}
		std::cout << std::endl;
	}
}

Vector3& Matrix4::getV3() {
	Vector3 *v = new Vector3(m[3][0], m[3][1], m[3][2]);
	return *v;
}

Matrix4::~Matrix4() {
    //delete[] &m;
}