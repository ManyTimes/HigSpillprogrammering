#ifndef _MATH_H
#define _MATH_H

#include <math.h>

namespace cgl
{
	const double PI = 4.0 * atan(1.0);

	struct Vector3i
	{
		int x,y,z;
		Vector3i::Vector3i(int deltax = 0, int deltay = 0, int deltaz = 0)
		{
			x = deltax;
			y = deltay;
			z = deltaz;
		}
		//OPERATORS
		friend Vector3i Vector3i::operator*(const int scale, const Vector3i &vector)
		{
			Vector3i res;
			res.x = scale * vector.x;
			res.y = scale * vector.y;
			res.z = scale * vector.z;
			return res;
		}
		Vector3i Vector3i::operator*(const float scale) const
		{
			Vector3i res;
			res.x = scale * x;
			res.y = scale * y;
			res.z = scale * z;
			return res;
		}

		Vector3i operator+(const Vector3i & vector) const
		{
			Vector3i res;
			res.x = x + vector.x;
			res.y = y + vector.y;
			res.z = z + vector.z;
			return res;
		}
		void Vector3i::Set(float deltax, float deltay, float deltaz)
		{
			x = deltax; 
			y = deltay; 
			z = deltaz;
		}
	};

	struct Vector3f 
	{
		float x, y, z;
		Vector3f::Vector3f(float dx = 0, float dy = 0, float dz = 0)
		{
			x = dx; 
			y = dy; 
			z = dz;
		}

		//OPERATORS
		friend Vector3f Vector3f::operator*(const float c, const Vector3f & v)
		{
			Vector3f res;
			res.x = c * v.x;
			res.y = c * v.y;
			res.z = c * v.z;
			return res;
		}
		Vector3f Vector3f::operator*(const float c) const
		{
			Vector3f res;
			res.x = c * x;
			res.y = c * y;
			res.z = c * z;
			return res;
		}
		const Vector3f &Vector3f::operator*=(float scale) 
		{
			x *= scale;
			y *= scale;
			z *= scale;
			return *this;
		}
		const Vector3f &Vector3f::operator/=(float scale) 
		{
			x /= scale;
			y /= scale;
			z /= scale;
			return *this;
		}
		const Vector3f &Vector3f::operator+=(const Vector3f &other)
		{
			x += other.x;
			y += other.y;
			z += other.z;
			return *this;
		}
		const Vector3f &Vector3f::operator-=(const Vector3f &other) 
		{
			x -= other.x;
			y -= other.y;
			z -= other.z;
			return *this;
		}
		Vector3f operator+(const Vector3f & v) const
		{
			Vector3f res;
			res.x = x + v.x;
			res.y = y + v.y;
			res.z = z + v.z;
			return res;
		}

		Vector3f operator-(const Vector3f & v) const
		{
			Vector3f res;
			res.x = x - v.x;
			res.y = y - v.y;
			res.z = z - v.z;
			return res;
		}

		Vector3f operator=(const Vector3f & v) const
		{
			Vector3f res;
			res.x = v.x;
			res.y = v.y;
			res.z = v.z;
			return res;
		}
		//METHODS
		void Vector3f::Set(float dx, float dy, float dz)
		{
			x = dx; y = dy; z = dz;
		}
		void Vector3f::Set(Vector3f& v)
		{
			x = v.x; y = v.y; z = v.z;
		}
		void Vector3f::Set(const Vector3f & v)
		{
			x = v.x; y = v.y; z = v.z;
		}
		void Vector3f::Normalize() 
		{
			float nInv = 1.0f / sqrt(x * x + y * y + z * z); 
			x *= nInv; 
			y *= nInv; 
			z *= nInv;
		}
		Vector3f Vector3f::Normalize(int zero) const 
		{
			float length = sqrt(x * x + y * y + z * z);
			return Vector3f(x / length, y /length, z / length);
		}
		Vector3f Vector3f::Cross(const Vector3f & v) const 
		{	
			Vector3f res;
			res.x = y * v.z - z * v.y;
			res.y = -x * v.z + z * v.x;
			res.z = x * v.y - y * v.x;
			return res;
		}
		Vector3f Vector3f::ColorCode() const
		{
			Vector3f temp(*this);
			temp.Normalize();
			temp = temp * 0.5 + Vector3f(0.5, 0.5, 0.5);
			return temp;
		}
		float Vector3f::Dot(const Vector3f & v) const
		{
			return x * v.x + y * v.y + z * v.z;
		}

		float& Vector3f::operator[](int i) 
		{
			float *p = &x; 
			return p[i]; 
		}

		float Vector3f::magnitude() const 
		{
			return sqrt(x * x + z * z + y * y);
		}

		//EXTRA

		float Vector3f::operator[](int index) const 
		{
			if(index == 0)
			{
				return x;
			}
			if(index == 1)
			{
				return y;
			}
			return z;
		}

		/*Vector3f Vector3f::operator*(float scale) const 
		{
			return Vector3f(v[0] * scale, v[1] * scale, v[2] * scale);
		}*/

		Vector3f Vector3f::operator/(float scale) const 
		{
			return Vector3f(x / scale, y / scale, z / scale);
		}

		/*Vector3f Vector3f::operator+(const Vector3f &other) const 
		{
			return Vector3f(v[0] + other.v[0], v[1] + other.v[1], v[2] + other.v[2]);
		}*/

		/*Vector3f Vector3f::operator-(const Vector3f &other) const 
		{
			return Vector3f(x - other.x, y - other.y, z - other.z);
		}*/

		Vector3f Vector3f::operator-() const
		{
			return Vector3f(-x, -y, -z);
		}

		/*	const Vector3f &Vector3f::operator*=(float scale) 
		{
			x *= scale;
			y *= scale;
			z *= scale;
			return *this;
		}*/

		/*const Vector3f &Vector3f::operator/=(float scale) 
		{
			x /= scale;
			y /= scale;
			z /= scale;
			return *this;
		}*/

		/*const Vector3f &Vector3f::operator+=(const Vector3f &other)
		{
			x += other.x;
			y += other.y;
			z += other.z;
			return *this;
		}*/

	};

}
#endif