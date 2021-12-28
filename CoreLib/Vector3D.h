#pragma once
#include "Vector2D.h"
struct Float3
{
	union
	{
		struct { float x, y, z; };
		float v[3];
	};
};
class Vector3D : public Float3
{
public:
	Vector3D();
	Vector3D(float x, float y, float z);
	Vector3D(const Vector3D& v);
public:
	Vector3D operator + (const Vector3D& v);
	Vector3D operator - (const Vector3D& v);
	Vector3D operator * (float fValue);
	Vector3D operator / (float fValue);
	bool operator == (const Vector3D& v);
	bool operator != (const Vector3D& v);
	// 정규화
	Vector3D Normalize();
	Vector3D Normal();
	friend Vector3D Normalize(Vector3D& v);
	// 크기
	float Length();
};

