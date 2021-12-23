#include "Vector3D.h"
Vector3D::Vector3D()
{
	x = y = z = 0;
}
Vector3D::Vector3D(float x, float y, float z)
{
	this->x = x;
	this->y = y;
	this->z = z;
}
Vector3D::Vector3D(const Vector3D& v)
{
	x = v.x;
	y = v.y;
	z = v.z;
}
Vector3D Vector3D::operator+ (const Vector3D& v)
{
	this->x += v.x;
	this->y += v.y;
	this->z += v.z;
	return *this;
}