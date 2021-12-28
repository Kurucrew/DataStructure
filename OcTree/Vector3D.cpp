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
	Vector3D ret;
	ret.x = this->x + v.x;
	ret.y = this->y + v.y;
	ret.z = this->z + v.z;
	return ret;
}
Vector3D Vector3D::operator - (const Vector3D& v)
{
	{
		Vector3D ret;
		ret.x = this->x - v.x;
		ret.y = this->y - v.y;
		ret.z = this->z - v.z;
		return ret;
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
Vector3D Vector3D::operator / (float vel)
{
	{
		this->x /= vel;
		this->y /= vel;
		this->z /= vel;
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
bool Vector3D::operator != (const Vector3D& v)
{
	if (fabs(x - v.x) < 0.0001f)
	{
		if (fabs(y - v.y) < 0.0001f)
		{
			if (fabs(z - v.z) < 0.0001f)
			{
				return false;
			}
		}
	}
	return true;
}
float Vector3D::Size()
{
	float size = x * x + y * y + z * z;
	return sqrt(size);
}
Vector3D Vector3D::Normalize()
{
	Vector3D ret;
	float size = 1.0f / Size();
	ret.x = x * size;
	ret.y = y * size;
	ret.z = z * size;
	return ret;
}