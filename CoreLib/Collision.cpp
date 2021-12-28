#include "Collision.h"
bool   Collision::RectToPoint(Rect rt, int x, int y)
{
	if (rt.vMin.x <= x && rt.vMax.x >= x &&
		rt.vMin.y <= y && rt.vMax.y >= y)
	{
		return true;
	}
	return false;
}
bool   Collision::RectToPoint(Rect rt, Vector2D v)
{
	if (rt.vMin.x <= v.x && rt.vMax.x >= v.x &&
		rt.vMin.y <= v.y && rt.vMax.y >= v.y)
	{
		return true;
	}
	return false;
}
Rect   Collision::UnionRect(Rect rt1, Rect rt2)
{
	Rect rt;
	rt.vMin.x = rt1.vMin.x < rt2.vMin.x ? rt1.vMin.x : rt2.vMin.x;
	rt.vMin.y = rt1.vMin.y < rt2.vMin.y ? rt1.vMin.y : rt2.vMin.y;
	rt.vMax.x = rt1.vMax.x < rt2.vMax.x ? rt2.vMax.x : rt1.vMax.x;
	rt.vMax.y = rt1.vMax.y < rt2.vMax.y ? rt2.vMax.y : rt1.vMax.y;
	rt.size.x = rt.vMax.x - rt.vMin.x;
	rt.size.y = rt.vMax.y - rt.vMin.y;
	rt.vMiddle = (rt.vMin + rt.vMax) / 2.0f;
	return rt;
}
bool   Collision::IntersectRect(
	Rect rt1, Rect rt2, Rect* pRect)
{
	Rect rt;
	Rect rtUnion = UnionRect(rt1, rt2);
	if (rtUnion.size.x <= (rt1.size.x + rt2.size.x) &&
		rtUnion.size.y <= (rt1.size.y + rt2.size.y))
	{
		if (pRect != nullptr)
		{
			pRect->vMin.x = rt1.vMin.x < rt2.vMin.x ?
				rt2.vMin.x : rt1.vMin.x;
			pRect->vMin.y = rt1.vMin.y < rt2.vMin.y ?
				rt2.vMin.y : rt1.vMin.y;

			pRect->vMax.x = rt1.vMax.x < rt2.vMax.x ?
				rt1.vMax.x : rt2.vMax.x;
			pRect->vMax.y = rt1.vMax.y < rt2.vMax.y ?
				rt1.vMax.y : rt2.vMax.y;

			pRect->size.x = pRect->vMax.x - pRect->vMin.x;
			pRect->size.y = pRect->vMax.y - pRect->vMin.y;
			pRect->vMiddle = (pRect->vMax + pRect->vMin) / 2.0f;
		}
		return true;
	}
	return false;
}
// 0 :  떨어져 있다.
// 1 :  안에 있다.
// 2 :  걸쳐 있다.
CollisionType   Collision::RectToRect(Rect rt1, 
	Rect rt2)
{	
	Rect rtInterction;
	int iRet = IntersectRect(rt1, rt2, &rtInterction);
	if (iRet <= 0)
	{
		return RECT_OUT;
	}
	if (rtInterction == rt2) return RECT_OVERLAP;
	return RECT_IN;
}


bool   Collision::BoxToPoint(Box rt, int x, int y, int z)
{
	if (rt.vMin.x <= x && rt.vMax.x >= x &&
		rt.vMin.y <= y && rt.vMax.y >= y &&
		rt.vMin.z <= z && rt.vMax.z >= z)
	{
		return true;
	}
	return false;
}
bool   Collision::BoxToPoint(Box rt, Vector3D v)
{
	if (rt.vMin.x <= v.x && rt.vMax.x >= v.x &&
		rt.vMin.y <= v.y && rt.vMax.y >= v.y &&
		rt.vMin.z <= v.z && rt.vMax.z >= v.z)
	{
		return true;
	}
	return false;
}
Box   Collision::UnionBox(Box rt1, Box rt2)
{
	Box rt;
	rt.vMin.x = rt1.vMin.x < rt2.vMin.x ? rt1.vMin.x : rt2.vMin.x;
	rt.vMin.y = rt1.vMin.y < rt2.vMin.y ? rt1.vMin.y : rt2.vMin.y;
	rt.vMin.z = rt1.vMin.z < rt2.vMin.z ? rt1.vMin.z : rt2.vMin.z;

	rt.vMax.x = rt1.vMax.x < rt2.vMax.x ? rt2.vMax.x : rt1.vMax.x;
	rt.vMax.y = rt1.vMax.y < rt2.vMax.y ? rt2.vMax.y : rt1.vMax.y;
	rt.vMax.z = rt1.vMax.z < rt2.vMax.z ? rt2.vMax.z : rt1.vMax.z;

	rt.size = rt.vMax - rt.vMin;
	rt.vMiddle = (rt.vMin + rt.vMax) / 2.0f;
	return rt;
}
bool   Collision::IntersectBox(
	Box rt1, Box rt2, Box* pRect)
{
	Box rt;
	Box rtUnion = UnionBox(rt1, rt2);
	if (rtUnion.size.x <= (rt1.size.x + rt2.size.x) &&
		rtUnion.size.y <= (rt1.size.y + rt2.size.y) &&
		rtUnion.size.z <= (rt1.size.z + rt2.size.z))
	{
		if (pRect != nullptr)
		{
			pRect->vMin.x = rt1.vMin.x < rt2.vMin.x ?
				rt2.vMin.x : rt1.vMin.x;
			pRect->vMin.y = rt1.vMin.y < rt2.vMin.y ?
				rt2.vMin.y : rt1.vMin.y;
			pRect->vMin.z = rt1.vMin.z < rt2.vMin.z ?
				rt2.vMin.z : rt1.vMin.z;

			pRect->vMax.x = rt1.vMax.x < rt2.vMax.x ?
				rt1.vMax.x : rt2.vMax.x;
			pRect->vMax.y = rt1.vMax.y < rt2.vMax.y ?
				rt1.vMax.y : rt2.vMax.y;
			pRect->vMax.z = rt1.vMax.z < rt2.vMax.z ?
				rt1.vMax.z : rt2.vMax.z;

			pRect->size = pRect->vMax - pRect->vMin;
			pRect->vMiddle = (pRect->vMax + pRect->vMin) / 2.0f;
		}
		return true;
	}
	return false;
}
// 0 :  떨어져 있다.
// 1 :  안에 있다.
// 2 :  걸쳐 있다.
CollisionType   Collision::BoxToBox(Box rt1, Box rt2)
{
	Box rtInterction;
	int iRet = IntersectBox(rt1, rt2, &rtInterction);
	if (iRet <= 0)
	{
		return RECT_OUT;
	}
	if (rtInterction == rt2) return RECT_OVERLAP;
	return RECT_IN;
}