#include "../Header/camera.h"

namespace cgl
{
	Camera::Camera(Vector3f startLocationXYZ, Vector3f horizontalLookAtXYZ, int resolutionHeight, int resolutionWidth, float nearDistance, float farDistance)
	{
		Vector3f verticalLook(0,1,0);
		this->screenHeight = resolutionHeight;
		this->screenWidth = resolutionWidth;
		this->SetShape(50.0f, this->screenWidth/this->screenHeight,nearDistance, farDistance);
		this->Set(startLocationXYZ, horizontalLookAtXYZ, verticalLook);
	}

	void Camera::SetModelViewMatrix()
	{
		float m[16];
		Vector3f eVec(eye.x, eye.y, eye.z);			//Vektorversjon av eye
		m[0] = u.x; 
		m[4] = u.y;
		m[8] = u.z;
		m[12] = -eVec.Dot(u);
		m[1] = v.x;
		m[5] = v.y;
		m[9] = v.z;
		m[13] = -eVec.Dot(v);
		m[2] = n.x; 
		m[6] = n.y;
		m[10] = n.z;
		m[14] = -eVec.Dot(n);
		m[3] = 0; 
		m[7] = 0;
		m[11] = 0;
		m[15] = 1.0;
		glMatrixMode(GL_MODELVIEW);
		glLoadMatrixf(m);							//Load OpenGLs modelview-matrix	
	}

	void Camera::Set(Vector3f Eye, Vector3f Look, Vector3f Up)
	{
		eye.Set(Eye);
		look.Set(Look);
		up.Set(Up);
		n.Set(eye.x - look.x, eye.y - look.y, eye.z - look.z);
		u.Set(up.Cross(n));
		n.Normalize();
		u.Normalize();
		v.Set(n.Cross(u));
		SetModelViewMatrix();
	}

	void Camera::SetEye(const Vector3f& Eye)
	{
		eye = Eye;
		eye.Set(Eye);
		n.Set(eye.x - look.x, eye.y - look.y, eye.z - look.z);
		u.Set(up.Cross(n));
		n.Normalize();
		u.Normalize();
		v.Set(n.Cross(u));
		SetModelViewMatrix();
	}

	void Perspective(GLdouble fovy, GLdouble aspect, GLdouble zNear, GLdouble zFar)
	{
	   GLdouble xmin, xmax, ymin, ymax;

	   ymax = zNear * tan(fovy * PI / 360.0);
	   ymin = -ymax;
	   xmin = ymin * aspect;
	   xmax = ymax * aspect;


	   glFrustum(xmin, xmax, ymin, ymax, zNear, zFar);
	}


	void Camera::SetShape(float viewingAngle, float aspect, float nearDistance, float farDistance)
	{
		this->viewAngle = viewingAngle;
		this->aspect = aspect;
		this->nearDist = nearDistance;
		this->farDist = farDistance;
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		Perspective(this->viewAngle, this->aspect, this->nearDist, this->farDist);
	}

	void Camera::Slide(float delU, float delV, float delN, bool unlocked)
	{
		eye.x += delU * u.x + (delV * v.x * unlocked) + delN * n.x;
		eye.y += delU * u.y + (delV * v.y) + delN * n.y;
		eye.z += delU * u.z + (delV * v.z * unlocked) + delN * n.z;
		SetModelViewMatrix();
	}

	//Forward, backwards
	void Camera::Roll(float angle)
	{
		angle *= (float)PI / 180;
		Vector3f t = u;
		u = cos(angle) * t + sin(angle) * v;
		v = -sin(angle) * t + cos(angle) * v;
		SetModelViewMatrix();
	}

	//Up or down
	void Camera::Pitch(float angle)
	{
		angle *= (float)PI / 180;
		Vector3f t = v;
		v = cos(angle) * t + sin(angle) * n;
		n = -sin(angle) * t + cos(angle) * n;
		SetModelViewMatrix();
	}

	//Left or right
	void Camera::Yaw(float angle)
	{
		angle *= (float)PI / 180;
		Vector3f t = n;
		n = cos(angle) * t + sin(angle) * u;
		u = -sin(angle) * t + cos(angle) * u;
		SetModelViewMatrix();
	}

	void Camera::Yaw_axis(float angle, Vector3f axis)
	{
		angle *= (float)PI / 180;
		Vector3f t = n;
		n = cos(angle) * t + sin(angle) * u;
		u = axis.Cross(n);
		u.Normalize();
		v = n.Cross(u);
		//u = -sin(angle) * t + cos(angle) * u;
		SetModelViewMatrix();
	}

	void Camera::Rotate(int axis, float angle)
	{
		//moving fram til look
		float delN = sqrt((eye.x - look.x) * (eye.x - look.x) +
				(eye.y - look.y) * (eye.y - look.y) +
				(eye.z - look.z) * (eye.z - look.z));
		Slide(0, 0, -delN, true);
		if (axis == 0)
		{
			Yaw(-angle);
		}
		else
		{
			Pitch(-angle);
		}
		Slide(0, 0, delN, true);
	}
}