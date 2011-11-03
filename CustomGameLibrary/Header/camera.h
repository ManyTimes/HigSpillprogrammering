#ifndef _CAMERA_H
#define _CAMERA_H

#include "include.h"
#include "mathtool.h"
#include "includegl.h";


namespace cgl
{
	class DECLARE Camera 
	{
	private:
		Vector3f eye, look;
		Vector3f up;
		Vector3f u, v, n;
		double viewAngle, aspect, nearDist, farDist;
		void SetModelViewMatrix();
	public:
		int screenWidth;
		int screenHeight;
		Camera::Camera(Vector3f startLocation, Vector3f horizontalLookAt, int screenHeight, int screenWidth, float nearDistance, float farDistance);
		void Camera::Set(Vector3f Eye, Vector3f Look, Vector3f Up);
		void Camera::Get(Vector3f & Eye, Vector3f& Look, Vector3f& Up)
		{
			Eye = eye; Look = look; Up = up;
		}

		void Camera::GetPerspective(float & vinkel, float & aspRat, float & her, float & der)
		{
			vinkel = (float)viewAngle; aspRat = (float)aspect; her = (float)nearDist; der = (float)farDist;
		}

		Vector3f Camera::getV()	
		{
			return v;
		}

		Vector3f Camera::getU()	
		{
			return u;
		}

		void Camera::SetEye(const Vector3f & Eye);

		//Point3 getEye(Camera & e) {return e.eye;}
		Vector3f Camera::GetEye() 
		{ 
			return eye; 
		}
		void Camera::Roll(float angle);
		void Camera::Pitch(float angle);
		void Camera::Yaw(float angle);
		void Camera::Yaw_axis(float angle, Vector3f axis);
		void Camera::Slide(float delU, float delV, float delN, bool unlocked);
		void Camera::SetShape(float vAng, float asp, float nearD, float farD);
		void Camera::Rotate(const Vector3f & axis, float angle);
		void Camera::Rotate(int axis, float angle);
	};

}	//End namespace
#endif