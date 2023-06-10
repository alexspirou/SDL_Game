#pragma once
#include<math.h>
class Vector2D
{
public:
	Vector2D() = default;

	Vector2D(float x, float y) : m_x(x), m_y(y) {}
	
	float length() { return sqrt(m_x * m_x + m_y * m_y); }

	//Operator overloading

	Vector2D operator = (const float& assigned)
	{
		this->m_x = assigned;
		this->m_y = assigned;
		return *this;
	}
	Vector2D operator+(const Vector2D& rhs)
	{
		return  Vector2D(this->m_x + rhs.m_x, this->m_y + rhs.m_y);
	}
	friend Vector2D& operator+=(Vector2D& v1, Vector2D& v2)
	{
		v1.m_x += v2.m_x;
		v1.m_y += v2.m_y;
		return v1;
	}
	Vector2D operator-(const Vector2D& rhs)
	{
		return Vector2D(this->m_x - rhs.m_x, this->m_y - rhs.m_y);
	}
	friend Vector2D& operator -=(Vector2D& v1, Vector2D& v2)
	{
		v1.m_x -= v2.m_x;
		v1.m_y -= v2.m_y;
		return v1;

	}
	Vector2D operator*(const float scale)
	{
		return Vector2D(m_x * scale, m_y * scale);
	}
	Vector2D operator/(float scalar)
	{
		return Vector2D(m_x / scalar, m_y / scalar);
	}
	Vector2D operator*=(const float scale)
	{
		this->m_x *= scale;
		this->m_y *= scale;

	}

	Vector2D& operator/=(float scalar)
	{
		m_x /= scalar;
		m_y /= scalar;
		return *this;
	}
	void normalize()
	{
		float legnth = length();
		if (legnth > 0)
		{
			(*this) *= 1 / legnth;
		}
	}

	float m_x;
	float m_y;

private:

};