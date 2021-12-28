#include "Vector2D.h"
Vector2D::Vector2D()
{
	x = y = 0.0f;
}
Vector2D::Vector2D(float x, float y)
{
	this->x = x;
	this->y = y;
}
Vector2D::Vector2D(const Vector2D& v)
{
	x = v.x;
	y = v.y;
}
Vector2D Vector2D::operator + (const Vector2D& v)
{
	Vector2D ret;
	ret.x = this->x + v.x;
	ret.y = this->y + v.y;	
	return ret;
}
Vector2D Vector2D::operator - (const Vector2D& v)
{
	Vector2D ret;
	ret.x = this->x - v.x;
	ret.y = this->y - v.y;
	return ret;
}
Vector2D Vector2D::operator * (float fValue)
{
	this->x *= fValue;
	this->y *= fValue;
	return *this;
}
Vector2D Vector2D::operator / (float fValue)
{
	this->x /= fValue;
	this->y /= fValue;
	return *this;
}
bool Vector2D::operator == (const Vector2D& v)
{
	if (fabs(x - v.x) < 0.0001f)
	{
		if (fabs(y - v.y) < 0.0001f)
		{
			return true;
		}
	}
	return false;
}
bool Vector2D::operator != (const Vector2D& v)
{
	if (fabs(x - v.x) < 0.0001f)
	{
		if (fabs(y - v.y) < 0.0001f)
		{
			return false;
		}
	}
	return true;
}

Vector2D Vector2D::Normal()
{
	Vector2D ret;
	float length = 1.0f / Length();
	ret.x = x * length;
	ret.y = y * length;
	return ret;
}
Vector2D Vector2D::Normalize()
{
	float length = 1.0f / Length();
	x *= length;
	y *= length;
	return *this;
}
Vector2D Normalize( Vector2D& v)
{
	Vector2D ret;
	float length = 1.0f / v.Length();
	ret.x = v.x * length;
	ret.y = v.y * length;
	return ret;
}
// Å©±â
float Vector2D::Length()
{
	float ret = x * x + y * y;
	return sqrt(ret);
}