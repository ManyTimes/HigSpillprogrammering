#ifndef CAMERA_H
#define CAMERA_H

#include "MathTools.h"

class Camera {
private :
	Point3 eye, look;
	Vector3 up;
	Vector3 u, v, n;
	double viewAngle, aspect, nearDist, farDist;
	void setModelViewMatrix();
	float matrix[16];
public :
	Camera();
	void set(Point3 Eye, Point3 Look, Vector3 Up);
	void get( Point3 & Eye, Point3 & Look, Vector3 & Up)
		{Eye = eye; Look = look; Up = up;}
	void hentPerspektiv(float & vinkel, float & aspRat, float & her, float & der)
	{vinkel = (float)viewAngle; aspRat = (float)aspect; her = (float)nearDist; der = (float)farDist;}
	Vector3 getV()	{return v;}
	Vector3 getU()	{return u;}
	void setEye(const Point3 & Eye);
	//Point3 getEye(Camera & e) {return e.eye;}
	Point3 getEye() { return eye; }
	float *getEyef() { return &eye[0]; }
	void roll(float angle);
	void pitch(float angle);
	void yaw(float angle);
	void yaw_axis(float angle, Vector3 axis);
	void slide(float delU, float delV, float delN, bool unlocked);
	void setShape(float vAng, float asp, float nearD, float farD);
	void rotate(const Vector3 & axis, float angle);
	void rotate(int axis, float angle);
	float *GetMatrix() { return matrix; }
};


#endif