#pragma once
#include <iostream>
#include <math.h>

struct Float2
{
	union
	{
		struct { float x, y; };
		float v[2];
	};
};
class Vector2D : public Float2
{
public:
	Vector2D();
	Vector2D(float x, float y);
	Vector2D(const Vector2D& v);
public:
	Vector2D operator + (const Vector2D& v);
	Vector2D operator - (const Vector2D& v);
	Vector2D operator * (float fValue);
	Vector2D operator / (float fValue);
	bool operator == (const Vector2D& v);
	bool operator != (const Vector2D& v);
	// 정규화
	Vector2D Normalize();
	Vector2D Normal();
	friend Vector2D Normalize(Vector2D& v);
	// 크기
	float Length();
};

