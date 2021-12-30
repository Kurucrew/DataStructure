#pragma once
#include "ObjShape.h"
enum CollisionType
{
	RECT_OUT = 0,
	RECT_IN,
	RECT_OVERLAP,
};
class Collision
{
public:
	/*static bool   ObjToPoint(Box rt, int x, int y, int z);
	static bool   ObjToPoint(Box rt, Vector3D v);*/
	static CollisionType    ObjToObj(Box, Box);
	static Box   UnionObj(Box rt1, Box rt2);
	static bool  IntersectObj(Box rt1, Box rt2, Box* rt);
};

