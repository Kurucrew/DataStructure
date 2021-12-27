#include "Object.h"
void   Object::SetPos(float x, float y, float z)
{
	m_Pos.x = x;
	m_Pos.y = y;
	m_Pos.z = z;
}
void  Object::SetBox(Box rt)
{
	m_box = rt;
}