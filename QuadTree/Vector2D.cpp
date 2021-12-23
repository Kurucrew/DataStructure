#include "Vector2D.h"
Vector2D::Vector2D()
{
	x = y = 0;
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
Vector2D Vector2D::operator+ (const Vector2D& v)
{
	this->x += x;
	this->y += y;
	return *this;
}