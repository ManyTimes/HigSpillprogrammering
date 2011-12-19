#ifndef _CAMERA_H
#define _CAMERA_H

#include "entity.h"
#include "include.h"
#include "mathtool.h"
#include "includegl.h"
#include "mouse.h"


namespace cgl
{
	struct ThirdPerson
	{
		Entity		*target;		// Target to follow
		float		distance;		// Distance from the target
		Vector3f	offset;			// Offset for camera
		Vector3f	angles;			// Euler angles PITCH, YAW, ROLL
		bool		alignTarget;	// Forces the target to align with the camera.
		Matrix		matrix;			// The matrix holding the third person camera angles.
	};

	class DECLARE Camera 
	{
	private:
		Vector3f eye, look;
		Vector3f up;
		Vector3f u, v, n;			//Up, normal, v...
		double viewAngle, aspect, nearDist, farDist;
		ThirdPerson thirdPerson;	// Third person settings.
		cgl::Mouse* mousept;
		
		void SetModelViewMatrix();
	public:
		int screenWidth;
		int screenHeight;
		Camera::Camera(Vector3f startLocation, Vector3f horizontalLookAt, int screenHeight, int screenWidth, float nearDistance, float farDistance, Mouse *mouse);
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

		// Third person
		void Camera::SetupThirdPersonCamera(Entity *followTarget, float distance, Vector3f offset, bool aligntarget);
		void Camera::SetThirdPersonTarget(Entity *followTarget);	// Target to follow
		void Camera::SetThirdPersonDistance(float distance);		// Distance from target
		void Camera::SetThirdPersonOffset(Vector3f offset);			// Offset, to align up at the head of your character for example.
		void Camera::SetThirdPersonAlign(bool aligntarget);			// Force the target to face the same way as the camera. (Only yaw)
		void Camera::ThirdPersonCameraUpdate();						// This is the function to call each frame to align the camera.
		void Camera::UpdateThirdPersonMatrix();						// This gets called when the third person matrix has to be updated from the new angles.
		void Camera::ThirdPersonRotatePitch(float angle);			// Rotate the pitch.
		void Camera::ThirdPersonRotateYaw(float angle);				// Rotate the yaw.
		void Camera::ThirdPersonRotateRoll(float angle);
		void Camera::Move();										// Keeping consistency with simplecamera, will handle mouse movements.
		Matrix* Camera::GetTPMatrix();
	};

}	//End namespace
#endif