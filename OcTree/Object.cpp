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
void Object::MoveObj(Vector3D vec)
{
	m_Pos.x = vec.x;
	m_Pos.y = vec.y;
	m_Pos.z = vec.z;
	float hw = (m_box.size.x / 2.0f);
	float hh = (m_box.size.y / 2.0f);
	float hl = (m_box.size.z / 2.0f);
	Vector3D v;
	v.x = m_Pos.x - hw;
	v.y = m_Pos.y - hh;
	v.z = m_Pos.z - hl;
	Box bx(v, hw * 2.0f, hh * 2.0f, hl * 2.0f);
	SetBox(bx);
}