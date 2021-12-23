#pragma once
struct Float2
{
	union
	{
		float x, y;
		float v[2];
	};
};
class Vector2D : public Float2
{
public:
	Vector2D();
	Vector2D(float x, float y);
	Vector2D(const Vector2D& v);
	Vector2D operator + (const Vector2D& v);
};

