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
		eye = Eye;
		look = Look;
		up = Up;
		n = eye - look;
		u = up.Cross(n);
		n = n.Normalize();
		u = u.Normalize();
		v = n.Cross(u);
		SetModelViewMatrix();
	}

	void Camera::SetEye(const Vector3f& Eye)
	{
		eye = Eye;
		n = eye - look;
		u = up.Cross(n);
		n = n.Normalize();
		u = u.Normalize();
		v = n.Cross(u);
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
		u = u.Normalize();
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

	void Camera::SetupThirdPersonCamera(Entity *followTarget, float distance, Vector3f offset, bool aligntarget)
	{
		thirdPerson.target = followTarget;
		thirdPerson.distance = distance;
		thirdPerson.offset = offset;
		thirdPerson.alignTarget = aligntarget;
	}
	
	void Camera::SetThirdPersonTarget(Entity *followTarget)
	{
		thirdPerson.target = followTarget;
	}

	void Camera::SetThirdPersonDistance(float distance)
	{
		thirdPerson.distance = distance;
	}

	void Camera::SetThirdPersonOffset(Vector3f offset)
	{
		thirdPerson.offset = offset;
	}

	void Camera::SetThirdPersonAlign(bool aligntarget)
	{
		thirdPerson.alignTarget = aligntarget;
	}

	void Camera::ThirdPersonCameraUpdate()
	{
		Vector3f result;
		Vector3f position = thirdPerson.target->GetPosition();
		Vector3f offset = thirdPerson.offset;

		result.z = thirdPerson.distance * thirdPerson.target->GetScale().x;

		result = thirdPerson.matrix * result;
		offset = *thirdPerson.target->GetMatrix() * offset;

		position += offset;
		result += position;
		Set(result, position, thirdPerson.matrix.GetUpVector());

		if(thirdPerson.alignTarget)
		{
			Vector3f angles = thirdPerson.target->GetAngles();
			angles[YAW] = thirdPerson.angles[YAW];
			thirdPerson.target->SetAngles(angles);
		}
	}

	void Camera::UpdateThirdPersonMatrix()
	{
		Vector3f r_angles;
		r_angles.x = DEG2RAD(thirdPerson.angles.x);
		r_angles.y = DEG2RAD(thirdPerson.angles.y);
		r_angles.z = DEG2RAD(thirdPerson.angles.z);

		float sa = sin(r_angles.z);
		float ca = cos(r_angles.z);
		float sb = sin(r_angles.x);
		float cb = cos(r_angles.x);
		float sh = sin(r_angles.y);
		float ch = cos(r_angles.y);

		thirdPerson.matrix[0] = ch*ca;
		thirdPerson.matrix[1] = sa;
		thirdPerson.matrix[2] = -sh*ca;

		thirdPerson.matrix[4] = -ch*sa*cb + sh*sb;
		thirdPerson.matrix[5] = ca*cb;
		thirdPerson.matrix[6] = sh*sa*cb + ch*sb;

		thirdPerson.matrix[8] = ch*sa*sb + sh*cb;
		thirdPerson.matrix[9] = -ca*sb;
		thirdPerson.matrix[10] = -sh*sa*sb + ch*cb;

		thirdPerson.matrix[3] = 0;
		thirdPerson.matrix[7] = 0;
		thirdPerson.matrix[11] = 0;
	}

	void Camera::ThirdPersonRotatePitch(float angle)
	{
		thirdPerson.angles[PITCH] += angle;

		if(thirdPerson.angles[PITCH] > 90.0f && thirdPerson.angles[PITCH] < 270.0f)
			thirdPerson.angles[PITCH] -= angle;

		if(thirdPerson.angles[PITCH] > 360.0f)
			thirdPerson.angles[PITCH] -= 360.0f;
		else if(thirdPerson.angles[PITCH] < 0.0f)
			thirdPerson.angles[PITCH] += 360.0f;

		UpdateThirdPersonMatrix();
	}

	void Camera::ThirdPersonRotateYaw(float angle)
	{
		thirdPerson.angles[YAW] += angle;

		if(thirdPerson.angles[YAW] > 360.0f)
			thirdPerson.angles[YAW] -= 360.0f;
		else if(thirdPerson.angles[YAW] < 0.0f)
			thirdPerson.angles[YAW] += 360.0f;

		UpdateThirdPersonMatrix();
	}

	void Camera::ThirdPersonRotateRoll(float angle)
	{
		thirdPerson.angles[ROLL] += angle;

		if(thirdPerson.angles[ROLL] > 360.0f)
			thirdPerson.angles[ROLL] -= 360.0f;
		else if(thirdPerson.angles[ROLL] < 0.0f)
			thirdPerson.angles[ROLL] += 360.0f;

		UpdateThirdPersonMatrix();
	}

}