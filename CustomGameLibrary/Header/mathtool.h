#ifndef _MATH_H
#define _MATH_H

//CONTAINS:
//Vertex3i, Vertex3f, Volumei, Volumef, Vector2f, Vector3i, Vector3f
#include <iostream>
#include <math.h>

namespace cgl
{
const double PI = 4.0 * atan(1.0);
const float PIdiv180 = PI/180;

struct Vertex3i
{
	int x,y,z;

	//CONSTRUCTORS
	Vertex3i(int x1,int y1, int z1)
	{
		x = x1;
		y = y1;
		z = z1;
	}
	Vertex3i()
	{
		x = y = z = 0.0;
	}

	//DISPLAY LINE
	void Vertex3i::operator<<(const Vertex3i &value) const
	{
		std::cout << "Value XYZ: " << value.x << ", " << value.y << ", " << value.z << std::endl;
	}

	//OPERATORS
	Vertex3i Vertex3i::operator=(int value)
	{
		x = value;
		y = value;
		z = value;
		return *this;
	}

	Vertex3i& operator=(const Vertex3i &value)
	{
		if(this == &value)
		{
			return *this;
		}
		x = value.x;
		y =  value.y;
		z = value.z;
		return *this;
	}

	Vertex3i& operator+=(const Vertex3i &value)
	{
		if(this == &value)
		{
			return *this;
		}
		x += value.x;
		y += value.y;
		z += value.z;
		return *this;
	}

	Vertex3i& operator+=(const int value)
	{
		x += value;
		y += value;
		z += value;
		return *this;
	}


	Vertex3i& operator-=(const Vertex3i &value)
	{
		if(this == &value)
		{
			return *this;
		}
		x -= value.x;
		y -= value.y;
		z -= value.z;
		return *this;
	}

	
	Vertex3i& operator-=(const int value)
	{
		x -= value;
		y -= value;
		z -= value;
		return *this;
	}

	Vertex3i& operator*=(const Vertex3i &value)
	{
		if(this == &value)
		{
			return *this;
		}
		x *= value.x;
		y *= value.y;
		z *= value.z;
		return *this;
	}

	
	Vertex3i& operator*=(const int value)
	{
		x *= value;
		y *= value;
		z *= value;
		return *this;
	}
		
	Vertex3i& operator/=(const Vertex3i &value)
	{
		if(this == &value)
		{
			return *this;
		}
		x /= value.x;
		y /= value.y;
		z /= value.z;
		return *this;
	}

	Vertex3i& operator/=(const int value)
	{
		x /= value;
		y /= value;
		z /= value;
		return *this;
	}

	Vertex3i& operator+(const Vertex3i &value)
	{
		return Vertex3i(*this) += value;
	}

	Vertex3i& operator+(const int value)
	{
		Vertex3i temp(value, value, value);
		return Vertex3i(*this) += temp;
	}

	Vertex3i& operator-(const Vertex3i &value)
	{
		return Vertex3i(*this) -= value;
	}

	Vertex3i& operator-(const int value)
	{
		Vertex3i temp(value, value, value);
		return Vertex3i(*this) -= temp;
	}
	
	Vertex3i& operator/(const Vertex3i &value)
	{
		return Vertex3i(*this) /= value;
	}

	Vertex3i& operator/(const int value)
	{
		Vertex3i temp(value, value, value);
		return Vertex3i(*this) /= temp;
	}

	Vertex3i& operator*(const Vertex3i &value)
	{
		return Vertex3i(*this) *= value;
	}

	Vertex3i& operator*(const int value)
	{
		Vertex3i temp(value, value, value);
		return Vertex3i(*this) *= temp;
	}

	int operator[](int index) const
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

	//BOOL OPERATORS
	bool Vertex3i::operator==(const Vertex3i &value) const
	{
		if(this->x == value.x && this->y == value.y && this->z == value.z)
		{
			return true;
		}
		return false;
	}

	bool Vertex3i::operator!=(const Vertex3i &value) const
	{
		return !(*this == value);
	}

	Vertex3i operator-() const
	{
		return Vertex3i(-x, -y, -z);
	}

	//FUNCTIONS
	int Vertex3i::Magnitude()
	{
		return (int)sqrt((float)(x * x + z * z + y * y));
	}

	int Vertex3i::Dot(const Vertex3i &value)
	{
		return x * value.x + y * value.y + z * value.z;
	}

	Vertex3i Vertex3i::Normalize()
	{
		int length = this->Magnitude();
		return Vertex3i(x/length, y/length, z/length);
	}


	Vertex3i Vertex3i::Cross(const Vertex3i &value) const 
	{	
		Vertex3i res;
		res.x = y * value.z - z * value.y;
		res.y = -x * value.z + z * value.x;
		res.z = x * value.y - y * value.x;
		return res;
	}

	//Friend operators
	friend Vertex3i Vertex3i::operator*(const int factor, const Vertex3i& value)
	{
		Vertex3i res;
		res.x = factor * value.x;
		res.y = factor * value.y;
		res.z = factor * value.z;
		return res;
	}


	int& Vertex3i::operator[](int i) 
	{
		int *p = &x; 
		return p[i]; 
	}
};


struct Vertex3f
{
	float x,y,z;

	//CONSTRUCTORS
	Vertex3f(float x1,float y1, float z1)
	{
		x = x1;
		y = y1;
		z = z1;
	}
	Vertex3f()
	{
		x = y = z = 0.0;
	}

	//DISPLAY LINE
	void Vertex3f::operator<<(const Vertex3f &value) const
	{
		std::cout << "Value XYZ: " << value.x << ", " << value.y << ", " << value.z << std::endl;
	}

	//OPERATORS
	Vertex3f Vertex3f::operator=(float value)
	{
		x = value;
		y = value;
		z = value;
		return *this;
	}

	Vertex3f& operator=(const Vertex3f &value)
	{
		if(this == &value)
		{
			return *this;
		}
		x = value.x;
		y =  value.y;
		z = value.z;
		return *this;
	}

	Vertex3f& operator+=(const Vertex3f &value)
	{
		if(this == &value)
		{
			return *this;
		}
		x += value.x;
		y += value.y;
		z += value.z;
		return *this;
	}

	Vertex3f& operator+=(const float value)
	{
		x += value;
		y += value;
		z += value;
		return *this;
	}


	Vertex3f& operator-=(const Vertex3f &value)
	{
		if(this == &value)
		{
			return *this;
		}
		x -= value.x;
		y -= value.y;
		z -= value.z;
		return *this;
	}

	
	Vertex3f& operator-=(const float value)
	{
		x -= value;
		y -= value;
		z -= value;
		return *this;
	}

	Vertex3f& operator*=(const Vertex3f &value)
	{
		if(this == &value)
		{
			return *this;
		}
		x *= value.x;
		y *= value.y;
		z *= value.z;
		return *this;
	}

	
	Vertex3f& operator*=(const float value)
	{
		x *= value;
		y *= value;
		z *= value;
		return *this;
	}
		
	Vertex3f& operator/=(const Vertex3f &value)
	{
		if(this == &value)
		{
			return *this;
		}
		x /= value.x;
		y /= value.y;
		z /= value.z;
		return *this;
	}

	Vertex3f& operator/=(const float value)
	{
		x /= value;
		y /= value;
		z /= value;
		return *this;
	}

	Vertex3f& operator+(const Vertex3f &value)
	{
		return Vertex3f(*this) += value;
	}

	Vertex3f& operator+(const float value)
	{
		Vertex3f temp(value, value, value);
		return Vertex3f(*this) += temp;
	}

	Vertex3f& operator-(const Vertex3f &value)
	{
		return Vertex3f(*this) -= value;
	}

	Vertex3f& operator-(const float value)
	{
		Vertex3f temp(value, value, value);
		return Vertex3f(*this) -= temp;
	}
	
	Vertex3f& operator/(const Vertex3f &value)
	{
		return Vertex3f(*this) /= value;
	}

	Vertex3f& operator/(const float value)
	{
		Vertex3f temp(value, value, value);
		return Vertex3f(*this) /= temp;
	}

	Vertex3f& operator*(const Vertex3f &value)
	{
		return Vertex3f(*this) *= value;
	}

	Vertex3f& operator*(const float value)
	{
		Vertex3f temp(value, value, value);
		return Vertex3f(*this) *= temp;
	}

	float operator[](int index) const
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

	//BOOL OPERATORS
	bool Vertex3f::operator==(const Vertex3f &value) const
	{
		if(this->x == value.x && this->y == value.y && this->z == value.z)
		{
			return true;
		}
		return false;
	}

	bool Vertex3f::operator!=(const Vertex3f &value) const
	{
		return !(*this == value);
	}

	Vertex3f operator-() const
	{
		return Vertex3f(-x, -y, -z);
	}

	//FUNCTIONS
	float Vertex3f::Magnitude()
	{
		return sqrt(x * x + z * z + y * y);
	}

	float Vertex3f::Dot(const Vertex3f &value)
	{
		return x * value.x + y * value.y + z * value.z;
	}

	Vertex3f Vertex3f::Normalize()
	{
		float length = this->Magnitude();
		return Vertex3f(x/length, y/length, z/length);
	}


	Vertex3f Vertex3f::Cross(const Vertex3f &value) const 
	{	
		Vertex3f res;
		res.x = y * value.z - z * value.y;
		res.y = -x * value.z + z * value.x;
		res.z = x * value.y - y * value.x;
		return res;
	}

	//Friend operators
	friend Vertex3f Vertex3f::operator*(const float factor, const Vertex3f& value)
	{
		Vertex3f res;
		res.x = factor * value.x;
		res.y = factor * value.y;
		res.z = factor * value.z;
		return res;
	}


	float& Vertex3f::operator[](int i) 
	{
		float *p = &x; 
		return p[i]; 
	}
};


struct Volumei
{
	int w,h,l;

	//CONSTRUCTORS
	Volumei(int w1,int h1, int l1)
	{
		w = w1;
		h = h1;
		l = l1;
	}
	Volumei()
	{
		w = h = l = 0.0;
	}

	//DISPLAh LINE
	void Volumei::operator<<(const Volumei &value) const
	{
		std::cout << "Value XYZ: " << value.w << ", " << value.h << ", " << value.l << std::endl;
	}

	//OPERATORS
	Volumei Volumei::operator=(int value)
	{
		w = value;
		h = value;
		l = value;
		return *this;
	}

	Volumei& operator=(const Volumei &value)
	{
		if(this == &value)
		{
			return *this;
		}
		w = value.w;
		h =  value.h;
		l = value.l;
		return *this;
	}

	Volumei& operator+=(const Volumei &value)
	{
		if(this == &value)
		{
			return *this;
		}
		w += value.w;
		h += value.h;
		l += value.l;
		return *this;
	}

	Volumei& operator+=(const int value)
	{
		w += value;
		h += value;
		l += value;
		return *this;
	}


	Volumei& operator-=(const Volumei &value)
	{
		if(this == &value)
		{
			return *this;
		}
		w -= value.w;
		h -= value.h;
		l -= value.l;
		return *this;
	}

	
	Volumei& operator-=(const int value)
	{
		w -= value;
		h -= value;
		l -= value;
		return *this;
	}

	Volumei& operator*=(const Volumei &value)
	{
		if(this == &value)
		{
			return *this;
		}
		w *= value.w;
		h *= value.h;
		l *= value.l;
		return *this;
	}

	
	Volumei& operator*=(const int value)
	{
		w *= value;
		h *= value;
		l *= value;
		return *this;
	}
		
	Volumei& operator/=(const Volumei &value)
	{
		if(this == &value)
		{
			return *this;
		}
		w /= value.w;
		h /= value.h;
		l /= value.l;
		return *this;
	}

	Volumei& operator/=(const int value)
	{
		w /= value;
		h /= value;
		l /= value;
		return *this;
	}

	Volumei& operator+(const Volumei &value)
	{
		return Volumei(*this) += value;
	}

	Volumei& operator+(const int value)
	{
		Volumei temp(value, value, value);
		return Volumei(*this) += temp;
	}

	Volumei& operator-(const Volumei &value)
	{
		return Volumei(*this) -= value;
	}

	Volumei& operator-(const int value)
	{
		Volumei temp(value, value, value);
		return Volumei(*this) -= temp;
	}
	
	Volumei& operator/(const Volumei &value)
	{
		return Volumei(*this) /= value;
	}

	Volumei& operator/(const int value)
	{
		Volumei temp(value, value, value);
		return Volumei(*this) /= temp;
	}

	Volumei& operator*(const Volumei &value)
	{
		return Volumei(*this) *= value;
	}

	Volumei& operator*(const int value)
	{
		Volumei temp(value, value, value);
		return Volumei(*this) *= temp;
	}

	int operator[](int index) const
	{
		if(index == 0)
		{
			return w;
		}
		if(index == 1)
		{
			return h;
		}
		return l;
	}

	//BOOL OPERATORS
	bool Volumei::operator==(const Volumei &value) const
	{
		if(this->w == value.w && this->h == value.h && this->l == value.l)
		{
			return true;
		}
		return false;
	}

	bool Volumei::operator!=(const Volumei &value) const
	{
		return !(*this == value);
	}

	Volumei operator-() const
	{
		return Volumei(-w, -h, -l);
	}

	//FUNCTIONS
	int Volumei::Magnitude()
	{
		return (int)sqrt((float)(w * w + l * l + h * h));
	}

	int Volumei::Dot(const Volumei &value)
	{
		return w * value.w + h * value.h + l * value.l;
	}

	Volumei Volumei::Normalize()
	{
		int length = this->Magnitude();
		return Volumei(w/length, h/length, l/length);
	}


	Volumei Volumei::Cross(const Volumei &value) const 
	{	
		Volumei res;
		res.w = h * value.l - l * value.h;
		res.h = -w * value.l + l * value.w;
		res.l = w * value.h - h * value.w;
		return res;
	}

	//Friend operators
	friend Volumei Volumei::operator*(const int factor, const Volumei& value)
	{
		Volumei res;
		res.w = factor * value.w;
		res.h = factor * value.h;
		res.l = factor * value.l;
		return res;
	}


	int& Volumei::operator[](int i) 
	{
		int *p = &w; 
		return p[i]; 
	}
};


struct Volumef
{
	float w,h,l;

	//CONSTRUCTORS
	Volumef(float w1,float h1, float l1)
	{
		w = w1;
		h = h1;
		l = l1;
	}
	Volumef()
	{
		w = h = l = 0.0;
	}

	//DISPLAh LINE
	void Volumef::operator<<(const Volumef &value) const
	{
		std::cout << "Value XYZ: " << value.w << ", " << value.h << ", " << value.l << std::endl;
	}

	//OPERATORS
	Volumef Volumef::operator=(float value)
	{
		w = value;
		h = value;
		l = value;
		return *this;
	}

	Volumef& operator=(const Volumef &value)
	{
		if(this == &value)
		{
			return *this;
		}
		w = value.w;
		h =  value.h;
		l = value.l;
		return *this;
	}

	Volumef& operator+=(const Volumef &value)
	{
		if(this == &value)
		{
			return *this;
		}
		w += value.w;
		h += value.h;
		l += value.l;
		return *this;
	}

	Volumef& operator+=(const float value)
	{
		w += value;
		h += value;
		l += value;
		return *this;
	}


	Volumef& operator-=(const Volumef &value)
	{
		if(this == &value)
		{
			return *this;
		}
		w -= value.w;
		h -= value.h;
		l -= value.l;
		return *this;
	}

	
	Volumef& operator-=(const float value)
	{
		w -= value;
		h -= value;
		l -= value;
		return *this;
	}

	Volumef& operator*=(const Volumef &value)
	{
		if(this == &value)
		{
			return *this;
		}
		w *= value.w;
		h *= value.h;
		l *= value.l;
		return *this;
	}

	
	Volumef& operator*=(const float value)
	{
		w *= value;
		h *= value;
		l *= value;
		return *this;
	}
		
	Volumef& operator/=(const Volumef &value)
	{
		if(this == &value)
		{
			return *this;
		}
		w /= value.w;
		h /= value.h;
		l /= value.l;
		return *this;
	}

	Volumef& operator/=(const float value)
	{
		w /= value;
		h /= value;
		l /= value;
		return *this;
	}

	Volumef& operator+(const Volumef &value)
	{
		return Volumef(*this) += value;
	}

	Volumef& operator+(const float value)
	{
		Volumef temp(value, value, value);
		return Volumef(*this) += temp;
	}

	Volumef& operator-(const Volumef &value)
	{
		return Volumef(*this) -= value;
	}

	Volumef& operator-(const float value)
	{
		Volumef temp(value, value, value);
		return Volumef(*this) -= temp;
	}
	
	Volumef& operator/(const Volumef &value)
	{
		return Volumef(*this) /= value;
	}

	Volumef& operator/(const float value)
	{
		Volumef temp(value, value, value);
		return Volumef(*this) /= temp;
	}

	Volumef& operator*(const Volumef &value)
	{
		return Volumef(*this) *= value;
	}

	Volumef& operator*(const float value)
	{
		Volumef temp(value, value, value);
		return Volumef(*this) *= temp;
	}

	float operator[](int index) const
	{
		if(index == 0)
		{
			return w;
		}
		if(index == 1)
		{
			return h;
		}
		return l;
	}

	//BOOL OPERATORS
	bool Volumef::operator==(const Volumef &value) const
	{
		if(this->w == value.w && this->h == value.h && this->l == value.l)
		{
			return true;
		}
		return false;
	}

	bool Volumef::operator!=(const Volumef &value) const
	{
		return !(*this == value);
	}

	Volumef operator-() const
	{
		return Volumef(-w, -h, -l);
	}

	//FUNCTIONS
	float Volumef::Magnitude()
	{
		return sqrt(w * w + l * l + h * h);
	}

	float Volumef::Dot(const Volumef &value)
	{
		return w * value.w + h * value.h + l * value.l;
	}

	Volumef Volumef::Normalize()
	{
		float length = this->Magnitude();
		return Volumef(w/length, h/length, l/length);
	}


	Volumef Volumef::Cross(const Volumef &value) const 
	{	
		Volumef res;
		res.w = h * value.l - l * value.h;
		res.h = -w * value.l + l * value.w;
		res.l = w * value.h - h * value.w;
		return res;
	}

	//Friend operators
	friend Volumef Volumef::operator*(const float factor, const Volumef& value)
	{
		Volumef res;
		res.w = factor * value.w;
		res.h = factor * value.h;
		res.l = factor * value.l;
		return res;
	}


	float& Volumef::operator[](int i) 
	{
		float *p = &w; 
		return p[i]; 
	}
};


struct Vector2f
{
	float x,y;

	//CONSTRUCTORS
	Vector2f(float x1,float y1)
	{
		x = x1;
		y = y1;
	}
	Vector2f()
	{
		x = y = 0.0;
	}

	//DISPLAY LINE
	void Vector2f::operator<<(const Vector2f &value) const
	{
		std::cout << "Value XYZ: " << value.x << ", " << value.y << std::endl;
	}

	//OPERATORS
	Vector2f Vector2f::operator=(float value)
	{
		x = value;
		y = value;
		return *this;
	}

	Vector2f& operator=(const Vector2f &value)
	{
		if(this == &value)
		{
			return *this;
		}
		x = value.x;
		y =  value.y;
		return *this;
	}

	Vector2f& operator+=(const Vector2f &value)
	{
		if(this == &value)
		{
			return *this;
		}
		x += value.x;
		y += value.y;
		return *this;
	}

	Vector2f& operator+=(const float value)
	{
		x += value;
		y += value;
		return *this;
	}


	Vector2f& operator-=(const Vector2f &value)
	{
		if(this == &value)
		{
			return *this;
		}
		x -= value.x;
		y -= value.y;
		return *this;
	}

	
	Vector2f& operator-=(const float value)
	{
		x -= value;
		y -= value;
		return *this;
	}

	Vector2f& operator*=(const Vector2f &value)
	{
		if(this == &value)
		{
			return *this;
		}
		x *= value.x;
		y *= value.y;
		return *this;
	}

	
	Vector2f& operator*=(const float value)
	{
		x *= value;
		y *= value;
		return *this;
	}
		
	Vector2f& operator/=(const Vector2f &value)
	{
		if(this == &value)
		{
			return *this;
		}
		x /= value.x;
		y /= value.y;
		return *this;
	}

	Vector2f& operator/=(const float value)
	{
		x /= value;
		y /= value;
		return *this;
	}

	Vector2f& operator+(const Vector2f &value)
	{
		return Vector2f(*this) += value;
	}

	Vector2f& operator+(const float value)
	{
		Vector2f temp(value, value);
		return Vector2f(*this) += temp;
	}

	Vector2f& operator-(const Vector2f &value)
	{
		return Vector2f(*this) -= value;
	}

	Vector2f& operator-(const float value)
	{
		Vector2f temp(value, value);
		return Vector2f(*this) -= temp;
	}
	
	Vector2f& operator/(const Vector2f &value)
	{
		return Vector2f(*this) /= value;
	}

	Vector2f& operator/(const float value)
	{
		Vector2f temp(value, value);
		return Vector2f(*this) /= temp;
	}

	Vector2f& operator*(const Vector2f &value)
	{
		return Vector2f(*this) *= value;
	}

	Vector2f& operator*(const float value)
	{
		Vector2f temp(value, value);
		return Vector2f(*this) *= temp;
	}

	float operator[](float index) const
	{
		if(index == 0)
		{
			return x;
		}
		return y;
	}

	//BOOL OPERATORS
	bool Vector2f::operator==(const Vector2f &value) const
	{
		if(this->x == value.x && this->y == value.y)
		{
			return true;
		}
		return false;
	}

	bool Vector2f::operator!=(const Vector2f &value) const
	{
		return !(*this == value);
	}

	Vector2f operator-() const
	{
		return Vector2f(-x, -y);
	}

	//FUNCTIONS
	float Vector2f::Magnitude()
	{
		return sqrt(x * x + y * y);
	}

	float Vector2f::Dot(const Vector2f &value)
	{
		return x * value.x + y * value.y;
	}

	Vector2f Vector2f::Normalize()
	{
		float length = this->Magnitude();
		return Vector2f(x/length, y/length);
	}


	Vector2f Vector2f::Cross(const Vector2f &value) const 
	{	
		Vector2f res;
		res.x = x * value.y - y * value.x;
		res.y = y * value.x - x * value.y;
		return res;
	}

	//Friend operators
	friend Vector2f Vector2f::operator*(const float factor, const Vector2f& value)
	{
		Vector2f res;
		res.x = factor * value.x;
		res.y = factor * value.y;
		return res;
	}

};

struct Vector3i
{
	int x,y,z;

	//CONSTRUCTORS
	Vector3i(int x1,int y1, int z1)
	{
		x = x1;
		y = y1;
		z = z1;
	}
	Vector3i()
	{
		x = y = z = 0.0;
	}

	//DISPLAY LINE
	void Vector3i::operator<<(const Vector3i &value) const
	{
		std::cout << "Value XYZ: " << value.x << ", " << value.y << ", " << value.z << std::endl;
	}

	//OPERATORS
	Vector3i Vector3i::operator=(int value)
	{
		x = value;
		y = value;
		z = value;
		return *this;
	}

	Vector3i& operator=(const Vector3i &value)
	{
		if(this == &value)
		{
			return *this;
		}
		x = value.x;
		y =  value.y;
		z = value.z;
		return *this;
	}

	Vector3i& operator+=(const Vector3i &value)
	{
		if(this == &value)
		{
			return *this;
		}
		x += value.x;
		y += value.y;
		z += value.z;
		return *this;
	}

	Vector3i& operator+=(const int value)
	{
		x += value;
		y += value;
		z += value;
		return *this;
	}


	Vector3i& operator-=(const Vector3i &value)
	{
		if(this == &value)
		{
			return *this;
		}
		x -= value.x;
		y -= value.y;
		z -= value.z;
		return *this;
	}

	
	Vector3i& operator-=(const int value)
	{
		x -= value;
		y -= value;
		z -= value;
		return *this;
	}

	Vector3i& operator*=(const Vector3i &value)
	{
		if(this == &value)
		{
			return *this;
		}
		x *= value.x;
		y *= value.y;
		z *= value.z;
		return *this;
	}

	
	Vector3i& operator*=(const int value)
	{
		x *= value;
		y *= value;
		z *= value;
		return *this;
	}
		
	Vector3i& operator/=(const Vector3i &value)
	{
		if(this == &value)
		{
			return *this;
		}
		x /= value.x;
		y /= value.y;
		z /= value.z;
		return *this;
	}

	Vector3i& operator/=(const int value)
	{
		x /= value;
		y /= value;
		z /= value;
		return *this;
	}

	Vector3i& operator+(const Vector3i &value)
	{
		return Vector3i(*this) += value;
	}

	Vector3i& operator+(const int value)
	{
		Vector3i temp(value, value, value);
		return Vector3i(*this) += temp;
	}

	Vector3i& operator-(const Vector3i &value)
	{
		return Vector3i(*this) -= value;
	}

	Vector3i& operator-(const int value)
	{
		Vector3i temp(value, value, value);
		return Vector3i(*this) -= temp;
	}
	
	Vector3i& operator/(const Vector3i &value)
	{
		return Vector3i(*this) /= value;
	}

	Vector3i& operator/(const int value)
	{
		Vector3i temp(value, value, value);
		return Vector3i(*this) /= temp;
	}

	Vector3i& operator*(const Vector3i &value)
	{
		return Vector3i(*this) *= value;
	}

	Vector3i& operator*(const int value)
	{
		Vector3i temp(value, value, value);
		return Vector3i(*this) *= temp;
	}

	int operator[](int index) const
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

	//BOOL OPERATORS
	bool Vector3i::operator==(const Vector3i &value) const
	{
		if(this->x == value.x && this->y == value.y && this->z == value.z)
		{
			return true;
		}
		return false;
	}

	bool Vector3i::operator!=(const Vector3i &value) const
	{
		return !(*this == value);
	}

	Vector3i operator-() const
	{
		return Vector3i(-x, -y, -z);
	}

	//FUNCTIONS
	int Vector3i::Magnitude()
	{
		return (int)sqrt((float)(x * x + z * z + y * y));
	}

	int Vector3i::Dot(const Vector3i &value)
	{
		return x * value.x + y * value.y + z * value.z;
	}

	Vector3i Vector3i::Normalize()
	{
		int length = this->Magnitude();
		return Vector3i(x/length, y/length, z/length);
	}


	Vector3i Vector3i::Cross(const Vector3i &value) const 
	{	
		Vector3i res;
		res.x = y * value.z - z * value.y;
		res.y = -x * value.z + z * value.x;
		res.z = x * value.y - y * value.x;
		return res;
	}

	//Friend operators
	friend Vector3i Vector3i::operator*(const int factor, const Vector3i& value)
	{
		Vector3i res;
		res.x = factor * value.x;
		res.y = factor * value.y;
		res.z = factor * value.z;
		return res;
	}


	int& Vector3i::operator[](int i) 
	{
		int *p = &x; 
		return p[i]; 
	}
};


struct Vector3f
{
	float x,y,z;

	//CONSTRUCTORS
	Vector3f(float x1,float y1, float z1)
	{
		x = x1;
		y = y1;
		z = z1;
	}
	Vector3f()
	{
		x = y = z = 0.0;
	}

	//DISPLAY LINE
	void Vector3f::Cout()
	{
		std::cout << "Value XYZ: " << x << ", " << y << ", " << z << std::endl;
	}


	//OPERATORS
	Vector3f Vector3f::operator=(float value)
	{
		x = value;
		y = value;
		z = value;
		return *this;
	}

	Vector3f& operator=(const Vector3f &value)
	{
		if(this == &value)
		{
			return *this;
		}
		x = value.x;
		y =  value.y;
		z = value.z;
		return *this;
	}

	Vector3f& operator+=(const Vector3f &value)
	{
		if(this == &value)
		{
			return *this;
		}
		x += value.x;
		y += value.y;
		z += value.z;
		return *this;
	}

	Vector3f& operator+=(const float value)
	{
		x += value;
		y += value;
		z += value;
		return *this;
	}


	Vector3f& operator-=(const Vector3f &value)
	{
		if(this == &value)
		{
			return *this;
		}
		x -= value.x;
		y -= value.y;
		z -= value.z;
		return *this;
	}

	
	Vector3f& operator-=(const float value)
	{
		x -= value;
		y -= value;
		z -= value;
		return *this;
	}

	Vector3f& operator*=(const Vector3f &value)
	{
		if(this == &value)
		{
			return *this;
		}
		x *= value.x;
		y *= value.y;
		z *= value.z;
		return *this;
	}

	
	Vector3f& operator*=(const float value)
	{
		x *= value;
		y *= value;
		z *= value;
		return *this;
	}
		
	Vector3f& operator/=(const Vector3f &value)
	{
		if(this == &value)
		{
			return *this;
		}
		x /= value.x;
		y /= value.y;
		z /= value.z;
		return *this;
	}

	Vector3f& operator/=(const float value)
	{
		x /= value;
		y /= value;
		z /= value;
		return *this;
	}

	Vector3f& operator+(const Vector3f &value)
	{
		return Vector3f(*this) += value;
	}

	Vector3f& operator+(const float value)
	{
		Vector3f temp(value, value, value);
		return Vector3f(*this) += temp;
	}

	Vector3f& operator-(const Vector3f &value)
	{
		return Vector3f(*this) -= value;
	}

	Vector3f& operator-(const float value)
	{
		Vector3f temp(value, value, value);
		return Vector3f(*this) -= temp;
	}
	
	Vector3f& operator/(const Vector3f &value)
	{
		return Vector3f(*this) /= value;
	}

	Vector3f& operator/(const float value)
	{
		Vector3f temp(value, value, value);
		return Vector3f(*this) /= temp;
	}

	Vector3f& operator*(const Vector3f &value)
	{
		return Vector3f(*this) *= value;
	}

	Vector3f& operator*(const float value)
	{
		Vector3f temp(value, value, value);
		return Vector3f(*this) *= temp;
	}

	float operator[](int index) const
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

	//BOOL OPERATORS
	bool Vector3f::operator==(const Vector3f &value) const
	{
		if(this->x == value.x && this->y == value.y && this->z == value.z)
		{
			return true;
		}
		return false;
	}

	bool Vector3f::operator!=(const Vector3f &value) const
	{
		return !(*this == value);
	}

	Vector3f operator-() const
	{
		return Vector3f(-x, -y, -z);
	}

	//FUNCTIONS
	float Vector3f::Magnitude()
	{
		return sqrt(x * x + z * z + y * y);
	}

	float Vector3f::Dot(const Vector3f &value)
	{
		return x * value.x + y * value.y + z * value.z;
	}

	Vector3f Vector3f::Normalize()
	{
		float length = this->Magnitude();
		return Vector3f(x/length, y/length, z/length);
	}


	Vector3f Vector3f::Cross(const Vector3f &value) const 
	{	
		Vector3f res;
		res.x = y * value.z - z * value.y;
		res.y = -x * value.z + z * value.x;
		res.z = x * value.y - y * value.x;
		return res;
	}

	//Friend operators
	friend Vector3f Vector3f::operator*(const float factor, const Vector3f& value)
	{
		Vector3f res;
		res.x = factor * value.x;
		res.y = factor * value.y;
		res.z = factor * value.z;
		return res;
	}


	float& Vector3f::operator[](int i) 
	{
		float *p = &x; 
		return p[i]; 
	}
};


	//OLD VECTOR; NOT IN USE; Some non working operators and so on, messed up!
	/*struct Vector3f 
	{
		float x, y, z;
		Vector3f::Vector3f(float dx = 0, float dy = 0, float dz = 0)
		{
			this->x = dx;
			this->y = dy; 
			this->z= dz;
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
		void Vector3f::Cout()
		{
			std::cout << "X Y Z: " << x << ", " << y << ", " << z << std::endl;
		}
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
		
		Vector3f Vector3f::NormalizeNew() const 
		{
			float length = sqrt(x * x + y * y + z * z);
			return Vector3f(x / length, y / length, z / length);
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

		Vector3f Vector3f::operator*(float scale) const 
		{
			return Vector3f(v[0] * scale, v[1] * scale, v[2] * scale);
		}

		Vector3f Vector3f::operator/(float scale) const 
		{
			return Vector3f(x / scale, y / scale, z / scale);
		}

		Vector3f Vector3f::operator+(const Vector3f &other) const 
		{
			return Vector3f(v[0] + other.v[0], v[1] + other.v[1], v[2] + other.v[2]);
		}

		Vector3f Vector3f::operator-(const Vector3f &other) const 
		{
			return Vector3f(x - other.x, y - other.y, z - other.z);
		}

		Vector3f Vector3f::operator-() const
		{
			return Vector3f(-x, -y, -z);
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
	};*/

/*	struct F3Vector  //Float 3d-vect, normally used
	{
		float x,y,z;
		
		F3Vector operator+ (F3Vector v, F3Vector u)
		{
			F3Vector res;
			res.x = v.x+u.x;
			res.y = v.y+u.y;
			res.z = v.z+u.z;
			return res;
		}
	};
*/

	/*std::ostream &operator << (std::ostream& out, const  cgl::Vector3f& c)
	{
		out << "(" << ")";
		return out;
	}*/



}
#endif