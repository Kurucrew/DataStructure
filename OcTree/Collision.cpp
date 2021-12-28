#include "Collision.h"
bool   Collision::ObjToPoint(Box rt, int x, int y, int z)
{
	if (rt.p1.x <= x && rt.p2.x >= x &&
		rt.p1.y <= y && rt.p2.y >= y &&
		rt.p1.z <= z && rt.p2.z >= z)
	{
		return true;
	}
	return false;
}
bool   Collision::ObjToPoint(Box rt, Vector3D v)
{
	if (rt.p1.x <= v.x && rt.p2.x >= v.x &&
		rt.p1.y <= v.y && rt.p2.y >= v.y &&
		rt.p1.z <= v.z && rt.p2.z >= v.z)
	{
		return true;
	}
	return false;
}
Box   Collision::UnionObj(Box rt1, Box rt2)
{
	Box bx;
	bx.p1.x = rt1.p1.x < rt2.p1.x ? rt1.p1.x : rt2.p1.x;
	bx.p1.y = rt1.p1.y < rt2.p1.y ? rt1.p1.y : rt2.p1.y;
	bx.p1.z = rt1.p1.z < rt2.p1.z ? rt1.p1.z : rt2.p1.z;

	bx.p2.x = rt1.p2.x < rt2.p2.x ? rt2.p2.x : rt1.p2.x;
	bx.p2.y = rt1.p2.y < rt2.p2.y ? rt2.p2.y : rt1.p2.y;
	bx.p2.z = rt1.p2.z < rt2.p2.z ? rt2.p2.z : rt1.p2.z;

	bx.size = bx.p2 - bx.p1;
	bx.mp = (bx.p1 + bx.p2) / 2.0f;
		return bx;
}
bool  Collision::IntersectObj(Box rt1, Box rt2, Box* rt)
{
	Box bx;
	Box ub = UnionObj(rt1, rt2);
	if (ub.size.x <= (rt1.size.x + rt2.size.x) &&
		ub.size.y <= (rt1.size.y + rt2.size.y) &&
		ub.size.z <= (rt1.size.z + rt2.size.z))
	{
		if (rt != nullptr)
		{
			rt->p1.x = rt1.p1.x < rt2.p1.x ? rt2.p1.x : rt1.p1.x;
			rt->p1.y = rt1.p1.y < rt2.p1.y ? rt2.p1.y : rt1.p1.y;
			rt->p1.z = rt1.p1.z < rt2.p1.z ? rt2.p1.z : rt1.p1.z;

			rt->p2.x = rt1.p2.x < rt2.p2.x ? rt1.p2.x : rt2.p2.x;
			rt->p2.y = rt1.p2.y < rt2.p2.y ? rt1.p2.y : rt2.p2.y;
			rt->p2.z = rt1.p2.z < rt2.p2.z ? rt1.p2.z : rt2.p2.z;

			rt->size = rt->p2 - rt->p1;
			rt->mp = (rt->p2 + rt->p1) / 2.0f;
		}
		return true;
	}
	return false;
}
CollisionType   Collision::ObjToObj(Box rt1, Box rt2) 
{
	Box ib;
	int ret = IntersectObj(rt1, rt2, &ib);
	if (ret <= 0)
	{
		return RECT_OUT;
	}
	if (ib == rt2)
	{
		return RECT_OVERLAP;
	}
	return RECT_IN;
}