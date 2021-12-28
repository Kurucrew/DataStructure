#pragma once
#include "Vector3D.h"
enum CollisionType
{
	RECT_OUT = 0,
	RECT_IN,
	RECT_OVERLAP,
};
struct Rect
{
	Vector2D vMin;
	Vector2D vMax;
	Vector2D vMiddle;
	Vector2D size;
	bool operator == (const Rect& v)
	{
		if (fabs((vMin - v.vMin).Length()) < 0.0001f)
		{
			if (fabs((vMax - v.vMax).Length()) < 0.0001f)
			{
				return true;
			}
		}
		return false;
	}
	Rect() {};
	Rect(Vector2D vMin, Vector2D vMax)
	{
		this->vMin = vMin;
		this->vMax = vMax;
		vMiddle = (vMax + vMin) / 2.0f;
		size.x = vMax.x - vMin.x;
		size.y = vMax.y - vMin.y;
	}
	Rect(Vector2D v, float w, float h)
	{
		this->vMin = v;
		this->vMax = vMin + Vector2D(w, h);
		vMiddle = (vMax + vMin) / 2.0f;
		this->size.x = w;
		this->size.y = h;
	}
};
struct Box
{
	Vector3D vMin;
	Vector3D vMax;
	Vector3D vMiddle;
	Vector3D size;
	bool operator == (const Box& v)
	{
		if (fabs((vMin - v.vMin).Length()) < 0.0001f)
		{
			if (fabs((vMax - v.vMax).Length()) < 0.0001f)
			{
				return true;
			}
		}
		return false;
	}
	Box() {};
	Box(Vector3D vMin, Vector3D vMax)
	{
		this->vMin = vMin;
		this->vMax = vMax;
		vMiddle = (vMax + vMin) / 2.0f;
		size.x = vMax.x - vMin.x;
		size.y = vMax.y - vMin.y;
	}
	Box(Vector3D v, float w, float h, float q)
	{
		this->vMin = v;
		this->vMax = vMin + Vector3D(w, h,q);
		vMiddle = (vMax + vMin) / 2.0f;
		this->size.x = w;
		this->size.y = h;
	}
};
class Collision
{
public:
	static bool   RectToPoint(Rect rt, int x, int y);
	static bool   RectToPoint(Rect rt, Vector2D v);
	static CollisionType    RectToRect(Rect,Rect);
	static Rect  UnionRect(Rect rt1, Rect rt2);
	static bool  IntersectRect(Rect rt1, Rect rt2, Rect* rt);
	
	static bool   BoxToPoint(Box rt, int x, int y, int z);
	static bool   BoxToPoint(Box rt, Vector3D v);
	static CollisionType    BoxToBox(Box, Box);
	static Box   UnionBox(Box rt1, Box rt2);
	static bool  IntersectBox(Box rt1, Box rt2, Box* rt);
};

