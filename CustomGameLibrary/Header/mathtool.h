#ifndef _MATH_H
#define _MATH_H

#include <math.h>

namespace cgl
{


	const double PI = 4.0 * atan(1.0);
	const float PIdiv180 = PI/180;



	struct Vertex3i 
	{
		int x, y, z;
		Vertex3i::Vertex3i(int dx = 0, int dy = 0, int dz = 0)
		{
			x = dx; 
			y = dy; 
			z = dz;
		}

		//OPERATORS
		friend Vertex3i Vertex3i::operator*(const int c, const Vertex3i & v)
		{
			Vertex3i res;
			res.x = c * v.x;
			res.y = c * v.y;
			res.z = c * v.z;
			return res;
		}
		Vertex3i Vertex3i::operator*(const int c) const
		{
			Vertex3i res;
			res.x = c * x;
			res.y = c * y;
			res.z = c * z;
			return res;
		}
		const Vertex3i &Vertex3i::operator*=(int scale) 
		{
			x *= scale;
			y *= scale;
			z *= scale;
			return *this;
		}
		const Vertex3i &Vertex3i::operator/=(int scale) 
		{
			x /= scale;
			y /= scale;
			z /= scale;
			return *this;
		}
		const Vertex3i &Vertex3i::operator+=(const Vertex3i &other)
		{
			x += other.x;
			y += other.y;
			z += other.z;
			return *this;
		}
		const Vertex3i &Vertex3i::operator-=(const Vertex3i &other) 
		{
			x -= other.x;
			y -= other.y;
			z -= other.z;
			return *this;
		}
		Vertex3i operator+(const Vertex3i & v) const
		{
			Vertex3i res;
			res.x = x + v.x;
			res.y = y + v.y;
			res.z = z + v.z;
			return res;
		}

		Vertex3i operator-(const Vertex3i & v) const
		{
			Vertex3i res;
			res.x = x - v.x;
			res.y = y - v.y;
			res.z = z - v.z;
			return res;
		}

		Vertex3i operator=(const Vertex3i & v) const
		{
			Vertex3i res;
			res.x = v.x;
			res.y = v.y;
			res.z = v.z;
			return res;
		}
		//METHODS
		void Vertex3i::Set(int dx, int dy, int dz)
		{
			x = dx; y = dy; z = dz;
		}
		void Vertex3i::Set(Vertex3i& v)
		{
			x = v.x; y = v.y; z = v.z;
		}
		void Vertex3i::Set(const Vertex3i & v)
		{
			x = v.x; y = v.y; z = v.z;
		}
		void Vertex3i::Normalize() 
		{
			int nInv = 1.0f / sqrt((float)(x * x + y * y + z * z)); 
			x *= nInv; 
			y *= nInv; 
			z *= nInv;
		}
		
		Vertex3i Vertex3i::NormalizeNew() const 
		{
			int length = sqrt((float)(x * x + y * y + z * z));
			return Vertex3i(x / length, y / length, z / length);
		}

		Vertex3i Vertex3i::Normalize(int zero) const 
		{
			int length = sqrt((float)(x * x + y * y + z * z));
			return Vertex3i(x / length, y /length, z / length);
		}
		Vertex3i Vertex3i::Cross(const Vertex3i & v) const 
		{	
			Vertex3i res;
			res.x = y * v.z - z * v.y;
			res.y = -x * v.z + z * v.x;
			res.z = x * v.y - y * v.x;
			return res;
		}
		Vertex3i Vertex3i::ColorCode() const
		{
			Vertex3i temp(*this);
			temp.Normalize();
			temp = temp * 0.5 + Vertex3i(0.5, 0.5, 0.5);
			return temp;
		}
		int Vertex3i::Dot(const Vertex3i & v) const
		{
			return x * v.x + y * v.y + z * v.z;
		}

		int& Vertex3i::operator[](int i) 
		{
			int *p = &x; 
			return p[i]; 
		}

		int Vertex3i::magnitude() const 
		{
			return sqrt((float)(x * x + z * z + y * y));
		}

		//EXTRA

		int Vertex3i::operator[](int index) const 
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

		/*Vector3f Vector3f::operator*(int scale) const 
		{
			return Vector3f(v[0] * scale, v[1] * scale, v[2] * scale);
		}*/

		Vertex3i Vertex3i::operator/(int scale) const 
		{
			return Vertex3i(x / scale, y / scale, z / scale);
		}

		/*Vector3f Vector3f::operator+(const Vector3f &other) const 
		{
			return Vector3f(v[0] + other.v[0], v[1] + other.v[1], v[2] + other.v[2]);
		}*/

		/*Vector3f Vector3f::operator-(const Vector3f &other) const 
		{
			return Vector3f(x - other.x, y - other.y, z - other.z);
		}*/

		Vertex3i Vertex3i::operator-() const
		{
			return Vertex3i(-x, -y, -z);
		}

		/*	const Vector3f &Vector3f::operator*=(int scale) 
		{
			x *= scale;
			y *= scale;
			z *= scale;
			return *this;
		}*/

		/*const Vector3f &Vector3f::operator/=(int scale) 
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



	struct Vertex3f 
	{
		float x, y, z;
		Vertex3f::Vertex3f(float dx = 0, float dy = 0, float dz = 0)
		{
			this->x = dx; 
			this->y = dy; 
			this->z = dz;
		}

		//OPERATORS
		friend Vertex3f Vertex3f::operator*(const float c, const Vertex3f & v)
		{
			Vertex3f res;
			res.x = c * v.x;
			res.y = c * v.y;
			res.z = c * v.z;
			return res;
		}
		Vertex3f Vertex3f::operator*(const float c) const
		{
			Vertex3f res;
			res.x = c * x;
			res.y = c * y;
			res.z = c * z;
			return res;
		}
		const Vertex3f &Vertex3f::operator*=(float scale) 
		{
			x *= scale;
			y *= scale;
			z *= scale;
			return *this;
		}
		const Vertex3f &Vertex3f::operator/=(float scale) 
		{
			x /= scale;
			y /= scale;
			z /= scale;
			return *this;
		}
		const Vertex3f &Vertex3f::operator+=(const Vertex3f &other)
		{
			x += other.x;
			y += other.y;
			z += other.z;
			return *this;
		}
		const Vertex3f &Vertex3f::operator-=(const Vertex3f &other) 
		{
			x -= other.x;
			y -= other.y;
			z -= other.z;
			return *this;
		}
		Vertex3f operator+(const Vertex3f & v) const
		{
			Vertex3f res;
			res.x = x + v.x;
			res.y = y + v.y;
			res.z = z + v.z;
			return res;
		}

		Vertex3f operator-(const Vertex3f & v) const
		{
			Vertex3f res;
			res.x = x - v.x;
			res.y = y - v.y;
			res.z = z - v.z;
			return res;
		}

		Vertex3f operator=(const Vertex3f & v) const
		{
			Vertex3f res;
			res.x = v.x;
			res.y = v.y;
			res.z = v.z;
			return res;
		}
		//METHODS
		void Vertex3f::Set(float dx, float dy, float dz)
		{
			x = dx; y = dy; z = dz;
		}
		void Vertex3f::Set(Vertex3f& v)
		{
			x = v.x; y = v.y; z = v.z;
		}
		void Vertex3f::Set(const Vertex3f & v)
		{
			x = v.x; y = v.y; z = v.z;
		}
		void Vertex3f::Normalize() 
		{
			float nInv = 1.0f / sqrt(x * x + y * y + z * z); 
			x *= nInv; 
			y *= nInv; 
			z *= nInv;
		}
		
		Vertex3f Vertex3f::NormalizeNew() const 
		{
			float length = sqrt(x * x + y * y + z * z);
			return Vertex3f(x / length, y / length, z / length);
		}

		Vertex3f Vertex3f::Normalize(int zero) const 
		{
			float length = sqrt(x * x + y * y + z * z);
			return Vertex3f(x / length, y /length, z / length);
		}
		Vertex3f Vertex3f::Cross(const Vertex3f & v) const 
		{	
			Vertex3f res;
			res.x = y * v.z - z * v.y;
			res.y = -x * v.z + z * v.x;
			res.z = x * v.y - y * v.x;
			return res;
		}
		Vertex3f Vertex3f::ColorCode() const
		{
			Vertex3f temp(*this);
			temp.Normalize();
			temp = temp * 0.5 + Vertex3f(0.5, 0.5, 0.5);
			return temp;
		}
		float Vertex3f::Dot(const Vertex3f & v) const
		{
			return x * v.x + y * v.y + z * v.z;
		}

		float& Vertex3f::operator[](int i) 
		{
			float *p = &x; 
			return p[i]; 
		}

		float Vertex3f::magnitude() const 
		{
			return sqrt(x * x + z * z + y * y);
		}

		//EXTRA

		float Vertex3f::operator[](int index) const 
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

		Vertex3f Vertex3f::operator/(float scale) const 
		{
			return Vertex3f(x / scale, y / scale, z / scale);
		}

		/*Vector3f Vector3f::operator+(const Vector3f &other) const 
		{
			return Vector3f(v[0] + other.v[0], v[1] + other.v[1], v[2] + other.v[2]);
		}*/

		/*Vector3f Vector3f::operator-(const Vector3f &other) const 
		{
			return Vector3f(x - other.x, y - other.y, z - other.z);
		}*/

		Vertex3f Vertex3f::operator-() const
		{
			return Vertex3f(-x, -y, -z);
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


	struct Volumei 
	{
		int l, w, h;
		Volumei::Volumei(int dl= 0, int dw = 0, int dh = 0)
		{
			l = dl; 
			w = dw; 
			h = dh;
		}

		//OPERATORS
		friend Volumei Volumei::operator*(const int scale, const Volumei & v)
		{
			Volumei res;
			res.l = scale * v.l;
			res.w = scale * v.w;
			res.h = scale * v.h;
			return res;
		}
		Volumei Volumei::operator*(const int scale) const
		{
			Volumei res;
			res.l = scale * l;
			res.w = scale * w;
			res.h = scale * h;
			return res;
		}
		const Volumei &Volumei::operator*=(int scale) 
		{
			l *= scale;
			w *= scale;
			h *= scale;
			return *this;
		}
		const Volumei &Volumei::operator/=(int scale) 
		{
			l /= scale;
			w /= scale;
			h /= scale;
			return *this;
		}
		const Volumei &Volumei::operator+=(const Volumei &other)
		{
			l += other.l;
			w += other.w;
			h += other.h;
			return *this;
		}
		const Volumei &Volumei::operator-=(const Volumei &other) 
		{
			l -= other.l;
			w -= other.w;
			h -= other.h;
			return *this;
		}
		Volumei operator+(const Volumei & v) const
		{
			Volumei res;
			res.l = l + v.l;
			res.w = w + v.w;
			res.h = h + v.h;
			return res;
		}

		Volumei operator-(const Volumei & v) const
		{
			Volumei res;
			res.l = l - v.l;
			res.w = w - v.w;
			res.h = h - v.h;
			return res;
		}

		Volumei operator=(const Volumei & v) const
		{
			Volumei res;
			res.h = v.l;
			res.w = v.w;
			res.l = v.h;
			return res;
		}
		//METHODS
		void Volumei::Set(int dl, int dw, int dh)
		{
			l = dl; w = dw; h = dh;
		}
		void Volumei::Set(Volumei& v)
		{
			l = v.l; w = v.w; h = v.h;
		}
		void Volumei::Set(const Volumei & v)
		{
			l = v.l; w = v.w; h = v.h;
		}

	};
	struct Volumef 
	{
		float l, w, h;
		Volumef::Volumef(float dl= 0, float dw = 0, float dh = 0)
		{
			l = dl; 
			w = dw; 
			h = dh;
		}

		//OPERATORS
		friend Volumef Volumef::operator*(const int scale, const Volumef & v)
		{
			Volumef res;
			res.l = scale * v.l;
			res.w = scale * v.w;
			res.h = scale * v.h;
			return res;
		}
		Volumef Volumef::operator*(const float scale) const
		{
			Volumef res;
			res.l = scale * l;
			res.w = scale * w;
			res.h = scale * h;
			return res;
		}
		const Volumef &Volumef::operator*=(float scale) 
		{
			l *= scale;
			w *= scale;
			h *= scale;
			return *this;
		}
		const Volumef &Volumef::operator/=(float scale) 
		{
			l /= scale;
			w /= scale;
			h /= scale;
			return *this;
		}
		const Volumef &Volumef::operator+=(const Volumef &other)
		{
			l += other.l;
			w += other.w;
			h += other.h;
			return *this;
		}
		const Volumef &Volumef::operator-=(const Volumef &other) 
		{
			l -= other.l;
			w -= other.w;
			h -= other.h;
			return *this;
		}
		Volumef operator+(const Volumef & v) const
		{
			Volumef res;
			res.l = l + v.l;
			res.w = w + v.w;
			res.h = h + v.h;
			return res;
		}

		Volumef operator-(const Volumef & v) const
		{
			Volumef res;
			res.l = l - v.l;
			res.w = w - v.w;
			res.h = h - v.h;
			return res;
		}

		Volumef operator=(const Volumef & v) const
		{
			Volumef res;
			res.h = v.l;
			res.w = v.w;
			res.l = v.h;
			return res;
		}
		//METHODS
		void Volumef::Set(float dl, float dw, float dh)
		{
			l = dl; w = dw; h = dh;
		}
		void Volumef::Set(Volumef& v)
		{
			l = v.l; w = v.w; h = v.h;
		}
		void Volumef::Set(const Volumef & v)
		{
			l = v.l; w = v.w; h = v.h;
		}

	};

	struct Vector2i
	{
		int x, y;
		Vector2i::Vector2i(int deltax = 0, int deltay = 0)
		{
			x = deltax;
			y = deltay;
		}
		//OPERATORS
		friend Vector2i Vector2i::operator*(const int scale, const Vector2i & v)
		{
			Vector2i res;
			res.x = scale * v.x;
			res.y = scale * v.y;
			return res;
		}
		Vector2i Vector2i::operator*(const int scale) const
		{
			Vector2i res;
			res.x = scale * x;
			res.y = scale * y;
			return res;
		}
		const Vector2i &Vector2i::operator*=(int scale) 
		{
			x *= scale;
			y *= scale;
			return *this;
		}
		const Vector2i &Vector2i::operator/=(int scale) 
		{
			x /= scale;
			y /= scale;
			return *this;
		}
		const Vector2i &Vector2i::operator+=(const Vector2i &other)
		{
			x += other.x;
			y += other.y;
			return *this;
		}
		const Vector2i &Vector2i::operator-=(const Vector2i &other) 
		{
			x -= other.x;
			y -= other.y;
			return *this;
		}

		void Vector2i::Set(int dx, int dy)
		{
			x = dx; 
			y = dy;
		}
		void Vector2i::Set(Vector2i& v)
		{
			x = v.x; 
			y = v.y;
		}
		
		float Vector2i::operator[](int index) const 
		{
			if(index == 0)
			{
				return x;
			}
			return y;
		}
	};



	struct Vector2f
	{
		float x, y;
		Vector2f::Vector2f(float deltax = 0, float deltay = 0)
		{
			x = deltax;
			y = deltay;
		}
		//OPERATORS
		friend Vector2f Vector2f::operator*(const float c, const Vector2f & v)
		{
			Vector2f res;
			res.x = c * v.x;
			res.y = c * v.y;
			return res;
		}
		Vector2f Vector2f::operator*(const float scale) const
		{
			Vector2f res;
			res.x = scale * x;
			res.y = scale * y;
			return res;
		}
		const Vector2f &Vector2f::operator*=(float scale) 
		{
			x *= scale;
			y *= scale;
			return *this;
		}
		const Vector2f &Vector2f::operator/=(float scale) 
		{
			x /= scale;
			y /= scale;
			return *this;
		}
		const Vector2f &Vector2f::operator+=(const Vector2f &other)
		{
			x += other.x;
			y += other.y;
			return *this;
		}
		const Vector2f &Vector2f::operator-=(const Vector2f &other) 
		{
			x -= other.x;
			y -= other.y;
			return *this;
		}

		void Vector2f::Set(float dx, float dy)
		{
			x = dx; y = dy;
		}
		void Vector2f::Set(Vector2f& v)
		{
			x = v.x; y = v.y;
		}
		
		float Vector2f::operator[](int index) const 
		{
			if(index == 0)
			{
				return x;
			}
			return y;
		}

		Vector2f operator=(const Vector2f & v) const
		{
			Vector2f res;
			res.x = v.x;
			res.y = v.y;
			return res;
		}
	};

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