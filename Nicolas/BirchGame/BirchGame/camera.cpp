#include <Gl/glfw.h>

#include "camera.h"

Camera::Camera()
{

}

void Camera::setModelViewMatrix()
{
	//float m[16];
	Vector3 eVec(eye.x, eye.y, eye.z);//Vektorversjon av eye
	matrix[0] = u.x; 
	matrix[4] = u.y;
	matrix[8] = u.z;
	matrix[12] = -eVec.dot(u);
	matrix[1] = v.x;
	matrix[5] = v.y;
	matrix[9] = v.z;
	matrix[13] = -eVec.dot(v);
	matrix[2] = n.x; 
	matrix[6] = n.y;
	matrix[10] = n.z;
	matrix[14] = -eVec.dot(n);
	matrix[3] = 0; 
	matrix[7] = 0;
	matrix[11] = 0;
	matrix[15] = 1.0;
	glMatrixMode(GL_MODELVIEW);
	glLoadMatrixf(matrix);//Load OpenGLs modelview-matrise
}

void Camera::set(Point3 Eye, Point3 Look, Vector3 Up)
{
	eye.set(Eye);
	look.set(Look);
	up.set(Up);
	n.set(eye.x - look.x, eye.y - look.y, eye.z - look.z);
	u.set(up.cross(n));
	n.normalize();
	u.normalize();
	v.set(n.cross(u));
	setModelViewMatrix();
}

void Camera::setEye(const Point3 & Eye)
{
	eye.set(Eye);
	n.set(eye.x - look.x, eye.y - look.y, eye.z - look.z);
	u.set(up.cross(n));
	n.normalize();
	u.normalize();
	v.set(n.cross(u));
	setModelViewMatrix();
}

void Perspective(GLdouble fovy, GLdouble aspect, GLdouble zNear, GLdouble zFar)
{
   GLdouble xmin, xmax, ymin, ymax;

   ymax = zNear * tan(fovy * pi / 360.0);
   ymin = -ymax;
   xmin = ymin * aspect;
   xmax = ymax * aspect;


   glFrustum(xmin, xmax, ymin, ymax, zNear, zFar);
}


void Camera::setShape(float vAng, float asp, float nearD, float farD)
{
	viewAngle = vAng;
	aspect = asp;
	nearDist = nearD;
	farDist = farD;
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	Perspective(viewAngle, aspect, nearDist, farDist);
}

void Camera::slide(float delU, float delV, float delN, bool unlocked)
{
	eye.x += delU * u.x + (delV * v.x * unlocked) + delN * n.x;
	eye.y += delU * u.y + (delV * v.y) + delN * n.y;
	eye.z += delU * u.z + (delV * v.z * unlocked) + delN * n.z;
	setModelViewMatrix();
}

void Camera::roll(float angle)
{
	angle *= (float)pi / 180;
	Vector3 t = u;
	u = cos(angle) * t + sin(angle) * v;
	v = -sin(angle) * t + cos(angle) * v;
	setModelViewMatrix();
}

void Camera::pitch(float angle)
{
	angle *= (float)pi / 180;
	Vector3 t = v;
	v = cos(angle) * t + sin(angle) * n;
	n = -sin(angle) * t + cos(angle) * n;
	setModelViewMatrix();
}

void Camera::yaw(float angle)
{
	angle *= (float)pi / 180;
	Vector3 t = n;
	n = cos(angle) * t + sin(angle) * u;
	u = -sin(angle) * t + cos(angle) * u;
	setModelViewMatrix();
}

void Camera::yaw_axis(float angle, Vector3 axis)
{
	angle *= (float)pi / 180;
	Vector3 t = n;
	n = cos(angle) * t + sin(angle) * u;
	u = axis.cross(n);
	u.normalize();
	v = n.cross(u);
	//u = -sin(angle) * t + cos(angle) * u;
	setModelViewMatrix();
}

void Camera::rotate(int axis, float angle)
{
	//moving fram til look
	float delN = sqrt((eye.x - look.x) * (eye.x - look.x) +
			(eye.y - look.y) * (eye.y - look.y) +
			(eye.z - look.z) * (eye.z - look.z));
	slide(0, 0, -delN, true);
	if (axis == 0)
		yaw(-angle);
	else
		pitch(-angle);
	slide(0, 0, delN, true);
}