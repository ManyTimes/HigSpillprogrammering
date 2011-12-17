#include "../Header/main.h"


struct Vector3test 
{
	float x, y, z;
	
	//OPERATORS
	Vector3test Vector3test::operator*=(float scale) const
	{
				std::cout << " T" << std::endl;
		Vector3test temp(0,0,0);
		temp.x =  x * scale;
		temp.y =  y * scale;
		temp.z =  z * scale;
		return temp;
	}
	Vector3test Vector3test::operator/=(float scale) const
	{
		std::cout << " S " << std::endl;
		Vector3test temp(0,0,0);
		temp.x =  x / scale;
		temp.y =  y / scale;
		temp.z =  z / scale;
		return temp;
	}
	Vector3test operator +(const Vector3test & v) const
	{
			std::cout << " R " << std::endl;
		Vector3test res;
		res.x = x + v.x;
		res.y = y + v.y;
		res.z = z + v.z;
		return res;
	}

	Vector3test operator *(const Vector3test & v) const
	{
				std::cout << " Q " << std::endl;
		Vector3test res;
		res.x = x * v.x;
		res.y = y * v.y;
		res.z = z * v.z;
		return res;
	}


	Vector3test operator-(const Vector3test & v) const
	{
		std::cout << " P " << std::endl;
		Vector3test res;
		res.x = x - v.x;
		res.y = y - v.y;
		res.z = z - v.z;
		return res;
	}



	Vector3test Vector3test::operator/(float scale) const 
	{
		std::cout << " O " << std::endl;
		return Vector3test(x / scale, y / scale, z / scale);
	}

	Vector3test(float x1,float y1, float z1)
	{
		x = x1;
		y = y1;
		z = z1;
	}
	Vector3test()
	{
		std::cout << " ff33s";
		x = y = z = 0.0;
	}

	//DISPLAY LINE
	void Vector3test::Cout()
	{
		std::cout << "Value XYZ: " << x << ", " << y << ", " << z << std::endl;
	}


	//OPERATORS
	Vector3test Vector3test::operator=(float value)
	{
		std::cout << "L" << std::endl;
		x = value;
		y = value;
		z = value;
		return *this;
	}

	Vector3test& operator=(const Vector3test &value)
	{
				std::cout << "J " << std::endl;
				std::cout<< "VALUE: " << this->z <<  " " << value.z <<" end";
		this->x = value.x;
		this->y = value.y;
		this->z = value.z;
		std::cout<< "VALUE: " << this->z <<  " " << value.z <<" end";
		return *this;
	}

	Vector3test& operator+=(const Vector3test &value)
	{
		std::cout << " K " << std::endl;
		this->x += value.x;
		this->y += value.y;
		this->z += value.z;
		return *this;			//*this
	}

	Vector3test& operator+=(const float value)
	{
				std::cout << "ii " << std::endl;
		x += value;
		y += value;
		z += value;
		return *this;
	}


	Vector3test& operator-=(const Vector3test &value)
	{
		std::cout << " H " << std::endl;
		x -= value.x;
		y -= value.y;
		z -= value.z;
		return *this;
	}

	Vector3test& operator-=(const float value)
	{
				std::cout << "G " << std::endl;
		x -= value;
		y -= value;
		z -= value;
		return *this;
	}

	Vector3test& operator*=(const Vector3test &value)
	{
		std::cout << " F " << std::endl;
		x *= value.x;
		y *= value.y;
		z *= value.z;
		this->Cout();
		return *this;
	}	
	Vector3test& operator*=(const float value)
	{
		std::cout << " E " << std::endl;
		x *= value;
		y *= value;
		z *= value;
		return *this;
	}
	Vector3test& operator/=(const Vector3test &value)
	{
		std::cout << " D " << std::endl;
		x /= value.x;
		y /= value.y;
		z /= value.z;
		return *this;
	}

	Vector3test& operator/=(const float value)
	{
		std::cout << " C " << std::endl;
		x /= value;
		y /= value;
		z /= value;
		return *this;
	}

	/*Vector3test& operator+(const Vector3test &value)
	{
		std::cout << " B " << std::endl;
		std::cout << " yXZ " << x << y << " " << z << std::endl;
		this->x = x + value.x;
		this->y += value.y;
		this->z += value.z;
		std::cout << " yXZ " << x << y << " " << z << std::endl;
		return *this;
	}*/

	Vector3test& operator+(const float value)
	{
		std::cout << " A " << std::endl;
		return Vector3test(0,0, 0);
	}

	Vector3test& operator-(const Vector3test &value)
	{
		std::cout << " 18 " << std::endl;
		return Vector3test(*this) -= value;
	}

	Vector3test& operator-(const float value)
	{
		std::cout << " 17 " << std::endl;
		Vector3test temp(value, value, value);
		return Vector3test(*this) -= temp;
	}
	Vector3test& operator/(const Vector3test &value)
	{
				std::cout << " 16 " << std::endl;
		return Vector3test(*this) /= value;
	}

	Vector3test& operator/(const float value)
	{
			std::cout << " 14 " << std::endl;
		Vector3test temp(value, value, value);
		return Vector3test(*this) /= temp;
	}

	Vector3test& operator*(const Vector3test &value)
	{
		std::cout << " 13 " << std::endl;
		return Vector3test(*this) *= value;
	}

	Vector3test& operator*(const float value)
	{
				std::cout << " 12 " << std::endl;
		Vector3test temp(value, value, value);
		temp.Cout();
		return Vector3test(*this) *= temp;
	}

	float operator[](int index) const
	{
				std::cout << " 11 " << std::endl;
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
	bool Vector3test::operator==(const Vector3test &value) const
	{
		std::cout << " 0 " << std::endl;
		if(this->x == value.x && this->y == value.y && this->z == value.z)
		{
			return true;
		}
		return false;
	}

	bool Vector3test::operator!=(const Vector3test &value) const
	{
		std::cout << " 9 " << std::endl;
		return !(*this == value);
	}

	Vector3test operator-() const
	{
		std::cout << " 8 " << std::endl;
		return Vector3test(-x, -y, -z);
	}

	//FUNCTIONS
	float Vector3test::Magnitude()
	{
		return sqrt(x * x + z * z + y * y);
	}

	float Vector3test::Dot(const Vector3test &value)
	{
		return x * value.x + y * value.y + z * value.z;
	}

	Vector3test Vector3test::Normalize()
	{
		float length = this->Magnitude();
		return Vector3test(x/length, y/length, z/length);
	}


	Vector3test Vector3test::Cross(const Vector3test &value) const 
	{	
		Vector3test res;
		res.x = y * value.z - z * value.y;
		res.y = -x * value.z + z * value.x;
		res.z = x * value.y - y * value.x;
		return res;
	}

	//Friend operators
	friend Vector3test operator*(const float factor, const Vector3test& value)
	{
			std::cout << " 6 " << std::endl;
		Vector3test res;
		res.x = factor * value.x;
		res.y = factor * value.y;
		res.z = factor * value.z;
		return res;
	}


	float& Vector3test::operator[](int i) 
	{
				std::cout << " 5 " << std::endl;
		float *p = &x; 
		return p[i]; 
	}

	Vector3test operator*(const Vector3test value)
	{
				std::cout << "4 " << std::endl;
		Vector3test temp;
		temp.x = x * value.x;
		temp.y = y * value.y;
		temp.z = z * value.z;
		return temp;
	}


	//NEW ONES
	Vector3test operator*(float factor) const 
	{
				std::cout << " 3 " << std::endl;
		return Vector3test(z * factor, y * factor, z * factor);
	}

	Vector3test operator=(const Vector3test & v) const
	{
		if(this == &v)
		{
			return *this;
		}
				std::cout << " 2" << std::endl;
		Vector3test res;
		res.x = v.x;
		res.y = v.y;
		res.z = v.z;
		return res;
	}

	Vector3test operator+(Vector3test va)const
	{
		std::cout << " 1 " << std::endl;
		return Vector3test(0,1,1);
	}

};

struct Vec
{
	float x,y,z;
	//CONSTRUCTORS
	Vec(float x1, float x2, float x3)
	{
		x = x1; y = x2; z = x3;
	}
		
	//OPERATORS TAKES VEC
	Vec& operator=(const Vec& v)
	{
		x = v.x;
		y = v.y;
		z = v.z;
		return *this;
	}

	Vec& operator += (const Vec& v)
	{
		x += v.x;
		y += v.y;
		z += v.z;
		return *this;
	}


	Vec& operator *= (const Vec& v)
	{
		x *= v.x;
		y *= v.y;
		z *= v.z;
		return *this;
	}

	Vec& operator /= (const Vec& v)
	{
		x /= v.x;
		y /= v.y;
		z /= v.z;
		return *this;
	}

	Vec& operator -= (const Vec& v)
	{
		x -= v.x;
		y -= v.y;
		z -= v.z;
		return *this;
	}

	Vec& operator + (const Vec& v)
	{
		x += v.x;
		y += v.y;
		z += v.z;
		return *this;
	}
	
	Vec& operator * (const Vec& v)
	{
		x += v.x;
		y += v.y;
		z += v.z;
		return *this;
	}

	Vec& operator / (const Vec& v)
	{
		x /= v.x;
		y /= v.y;
		z /= v.z;
		return *this;
	}

	Vec& operator - (const Vec& v)
	{
		x -= v.x;
		y -= v.y;
		z -= v.z;
		return *this;
	}

	//OPERATORS TAKES FLOAT/INT

	Vec& operator += (const float v)
	{
		x += v;
		y += v;
		z += v;
		return *this;
	}

	Vec& operator + (const float v)
	{
		x += v;
		y += v;
		z += v;
		return *this;
	}

	Vec& operator *= (const float v)
	{
		x *= v;
		y *= v;
		z *= v;
		return *this;
	}

	Vec& operator * (const float v)
	{
		x *= v;
		y *= v;
		z *= v;
		return *this;
	}

	Vec& operator /= (const float v)
	{
		x /= v;
		y /= v;
		z /= v;
		return *this;
	}

	Vec& operator / (const float v)
	{
		x /= v;
		y /= v;
		z /= v;
		return *this;
	}

	Vec& operator -= (const float v)
	{
		x -= v;
		y -= v;
		z -= v;
		return *this;
	}

	Vec& operator - (const float v)
	{
		x -= v;
		y -= v;
		z -= v;
		return *this;
	}

	void Cout()
	{
		std::cout << x << y << z << std::endl;
	}

	friend Vec operator*(const float scale, const Vec &v)
	{
		Vec vec(v.x, v.x, v.z);
		vec *= scale;
		return vec;
	}

	friend Vec operator*(const Vec& v, const float scale)
	{
		Vec vec(v.x, v.x, v.z);
		vec *= scale;
		return vec;
	}

	/*friend Vec operator*( const Vec &v, const scale)
	{
		return v;
	}*/

	/*friend Vec operator+(float scale, const Vec &v)
	{
		return v + scale;
	}*/
};


int main(int argc, char *argv[])
{
	cgl::Vector3f t1(1,2,3);
	cgl::Vector3f t2(5,6,10);
	

	t1 = t1 * 2;
	t1.Cout();
	t1 = t2;
	t1.Cout();
	t2 = t1 * (1-0.3596);
	t2.Cout();
	t1 = t2 * 0.2525;
	t1.Cout();
	t1 = t1 + t2;
	t1.Cout();
	t2 += t1;
	t1.Cout();
	t1 = t1 * 1-0.35 + t2 * 0.35;
	t1.Cout();

/*
	Vec v(1,2,3);
	Vec v2(3,4,5);

	v += v;
	v.Cout();
	v = v2 +5 -16 -12 *2 + 2 *v2 +2;
	v.Cout();

*/




	//Vector3test pos(1,1,1);
	//pos.Cout();
//	pos = (pos *(1 - 0.3495)) + (pos * 0.3495);
	/*pos = pos * (1- 0.3495);
	pos = pos * 0.3459;
	pos.Cout();
	std::cout << std::endl << std::endl;
	Vector3test t1(5,5,5);
	Vector3test t2(3,3,3);*/
	//t1 = t1+ t1;
	//t1.Cout();
	std::cout << "FLOAT TO S: " << cgl::f2s(15.05f) << std::endl;
	std::cout << "FLOAT TO C: " << cgl::f2c(15.05f) << std::endl;
	Initialize();		//Initializes everything
	Program();			//Starts the program/Server/game loop

	return 0;
}
