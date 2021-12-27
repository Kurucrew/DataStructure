#pragma once
#include <math.h>
struct Float3
{
	union
	{
		struct 
		{
			float x, y, z;
		};
		float v[3];
	};
};
class Vector3D : public Float3
{
public:
	Vector3D();
	Vector3D(float x, float y, float z);
	Vector3D(const Vector3D& v);
	Vector3D operator + (const Vector3D& v);
	Vector3D operator - (const Vector3D& v);
	Vector3D operator * (float vel);
	Vector3D operator / (float vel);
	bool operator == (const Vector3D& v);
	bool operator != (const Vector3D& v);
	// Á¤±ÔÈ­
	Vector3D Normalize();
	// Å©±â
	float Size();
	// º¤ÅÍ »¬¼À, ½ºÄ®¶ó °ö¼À
};

