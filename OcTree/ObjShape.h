#pragma once
#include "Vector3D.h"
struct Box
{
	Vector3D p1;
	Vector3D p2;
	Vector3D mp;
	Vector3D size;
	bool operator == (const Box& v)
	{
		if (fabs((p1 - v.p1).Size()) < 0.0001f)
		{
			if (fabs((p2 - v.p2).Size()) < 0.0001f)
			{
				return true;
			}
		}
		return false;
	}
	Box() {};
	Box(Vector3D vMin, Vector3D vMax)
	{
		this->p1 = vMin;
		this->p2 = vMax;
		mp = (vMax + vMin) / 2.0f;
		size.x = vMax.x - vMin.x;
		size.y = vMax.y - vMin.y;
		size.z = vMax.z - vMin.z;
	}
	Box(Vector3D v, float w, float h, float l)
	{
		this->p1 = v;
		this->p2 = p1 + Vector3D(w, h, l);
		mp = (p2 + p1) / 2.0f;
		this->size.x = w;
		this->size.y = h;
		this->size.z = l;
	}
};