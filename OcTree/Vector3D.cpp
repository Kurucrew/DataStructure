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
Vector3D Vector3D::operator - (const Vector3D& v)
{
	{
		this->x -= v.x;
		this->y -= v.y;
		this->z -= v.z;
		return *this;
	}
}
Vector3D Vector3D::operator * (float vel)
{
	{
		this->x *= vel;
		this->y *= vel;
		this->z *= vel;
		return *this;
	}
}
bool Vector3D::operator == (const Vector3D& v)
{
	if (fabs(x - v.x) < 0.0001f)
	{
		if (fabs(y - v.y) < 0.0001f)
		{
			if (fabs(z - v.z) < 0.0001f)
			{
				return true;
			}
		}
	}
	return false;
}
Vector3D Vector3D::operator != (const Vector3D& v)
{

}
float Vector3D::Size()
{
	float size = x * x + y * y + z * z;
	return sqrt(size);
}
Vector3D Vector3D::Normalize()
{
	float size = 1.0f / Size();
	x *= size;
	y *= size;
	z *= size;
	return *this;
}