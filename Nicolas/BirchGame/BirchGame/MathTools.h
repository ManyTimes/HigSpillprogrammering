#ifndef MATTEVERKTOY_H
#define MATTEVERKTOY_H


#include <math.h>

const double pi = 4.0 * atan(1.0);

struct Point3 {
	float x, y, z;
	Point3(float dx = 0, float dy = 0, float dz = 0)
		{x = dx; y = dy; z = dz;}
	Point3(float d[3])
		{x = d[0]; y = d[1]; z = d[2];}
	Point3(short d[3])
		{x = d[0]; y = d[1]; z = d[2];}
	void set(float dx, float dy, float dz)
		{x = dx; y = dy; z = dz;}
	void set(const Point3 & p)
		{x = p.x; y = p.y; z = p.z;}
	void build4tuple(float v[])
	{v[0] = x; v[1] = y; v[2] = z; v[3] = 1;}
	Point3 operator-(const Point3 & pt) 
	{	
		Point3 pRet;
		pRet.x = x - pt.x;
		pRet.y = y - pt.y;
		pRet.z = z - pt.z;
		return pRet;
	}
	friend Point3 operator*(const float m, const Point3 & pt) 
	{	
		Point3 pRet;
		pRet.x = m * pt.x;
		pRet.y = m * pt.y;
		pRet.z = m * pt.z;
		return pRet;
	}
	Point3 operator*(const float m) 
	{	
		Point3 pRet;
		pRet.x = m * x;
		pRet.y = m * y;
		pRet.z = m * z;
		return pRet;
	}
	float& operator[](int i) { float *p = &x; return p[i]; }
};

struct Vector3 {
	float x, y, z;
	friend Vector3 operator*(const float c, const Vector3 & v)
	{
		Vector3 res;
		res.x = c * v.x;
		res.y = c * v.y;
		res.z = c * v.z;
		return res;
	}
	Vector3 operator*(const float c) const
	{
		Vector3 res;
		res.x = c * x;
		res.y = c * y;
		res.z = c * z;
		return res;
	}

/*	Vector3 & operator=(const Vector3 & v)
	{
		x = v.x;
		y = v.y;
		z = v.z;
		return *this;
	}//*/

	Vector3 operator+(const Vector3 & v) const
	{
		Vector3 res;
		res.x = x + v.x;
		res.y = y + v.y;
		res.z = z + v.z;
		return res;
	}//*/

	Vector3 operator-(const Vector3 & v) const
	{
		Vector3 res;
		res.x = x - v.x;
		res.y = y - v.y;
		res.z = z - v.z;
		return res;
	}//*/

	Vector3(float dx = 0, float dy = 0, float dz = 0)
		{x = dx; y = dy; z = dz;}
	Vector3(Point3 pt)
		{x = pt.x; y = pt.y; z = pt.z;}
	void set(float dx, float dy, float dz)
		{x = dx; y = dy; z = dz;}
	void set(Vector3 & v)
		{x = v.x; y = v.y; z = v.z;}
	void normalize() 
		{float nInv = 1.0f / sqrt(x * x + y * y + z * z); 
			x *= nInv; y *= nInv; z *= nInv;}
	Vector3 cross(const Vector3 & v) const 
	{	
		Vector3 res;
		res.x = y * v.z - z * v.y;
		res.y = -x * v.z + z * v.x;
		res.z = x * v.y - y * v.x;
		return res;
	}
	float dot(const Vector3 & v) const
		{return x * v.x + y * v.y + z * v.z;}

	Vector3 fargeKode() const
	{
		Vector3 temp(*this);
		temp.normalize();
		temp = temp * 0.5 + Vector3(0.5, 0.5, 0.5);
		return temp;
	}

	float& operator[](int i) { float *p = &x; return p[i]; }
};
#endif