#ifndef _SIMPLECAMERA_H
#define _SIMPLECAMERA_H

#include "mathtool.h"
#include "include.h"
#include "math.h"
#include "mouse.h"

namespace cgl
{
	/*class DECLARE SimpleCamera
	{
	private:
		float PI_;
		float PI_times_180;
		float yrot, xrot, zrot;
		float yrotradian, xrotradian, zrotradian;
		cgl::Mouse* mouseObj;
		int lastx, lasty;
	public:
		float x,y,z;			//Camera position in our 3D land
		SimpleCamera::SimpleCamera()
		{		
			this->lastx = 0;                                                                   
			this->lasty = 0;
			this->PI_ = 3.141592654f;
			this->PI_times_180 = 180 * this->PI_;
			this->x = this->y = this->z = 0.0f;
			this->yrot = this->xrot = this->zrot = 0.0f;
			this->yrotradian = this->xrotradian = this->zrotradian = 0.0f;
		}

		//Initializing mouse object for camera to use as a FPS camera
		void SimpleCamera::InitializeFPS(cgl::Mouse* mouseObject)
		{
			this->mouseObj = mouseObject;
		}

		//Call this when mouse moves, to update position of camera by its mouse position
		void SimpleCamera::MouseMove()
		{
			int diffx = this->mouseObj->cursorx - lastx;
			int diffy = this->mouseObj->cursory - lasty;
			lastx = this->mouseObj->cursorx;
			lasty = this->mouseObj->cursory;
			this->xrot += (float)diffy;
			this->yrot += (float)diffx;
		}

		//Rotates the X-axis in either positive or negative angle
		void SimpleCamera::RotateX(int angle)
		{
			this->xrot += angle;
			if(this->xrot > 360)
			{
				xrot -= 360;
			}
			if(this->xrot < -360)
			{
				this->xrot += 360;
			}
			this->xrotradian = (this->xrot/this->PI_times_180);
			x += float(sin(xrotradian));
			y += float(sin(xrotradian));
		}

		//Strafe in either positive factor or a negative factor (left /right)
		void SimpleCamera::Strafe(float factor)
		{
			this->yrotradian = (this->yrot/this->PI_times_180);
			this->x = float(cos(this->yrotradian)) * factor;
			this->z = float(sin(this->yrotradian)) * factor;
		}

		//Call this to render camera at its current position
		void SimpleCamera::View()
		{
			glRotatef(-this->xrot, 1.0, 0.0, 0.0);
			glRotatef(this->yrot, 0.0, 1.0, 0.0);
			glTranslatef(-this->x, -this->y, -this->z);
		}
	};*/


	class DECLARE SimpleCamera
	{
	private:
		bool viewchanged;
		float xrot, yrot, zrot;
		cgl::Vector3f move;
		double temp;
	public:
		cgl::Vector3f* position;
		cgl::Vector3f* viewdirection;
		SimpleCamera::SimpleCamera()
		{
			this->position = new cgl::Vector3f(0.0,0.0, 0.0);
			this->viewdirection = new cgl::Vector3f(0.0,0.0,-1.0);
			this->viewchanged = false;
			this->xrot = this->yrot = this->zrot = 0.0;
			this->temp = 0.0;
		}

		//Projectile can then simply do the same, just "move forward" every "Draw()" , I REEK!

		void SimpleCamera::GetViewDirection()
		{
			cgl::Vector3f step1, step2;
			//Rotate Y-axis
			step1.x = cos((this->yrot + 90.0) * PIdiv180);
			step1.z = -sin((this->yrot + 90.0) * PIdiv180);
			//Rotate X-axis
			this->temp = cos(this->xrot * PIdiv180);
			step2.x = step1.x * this->temp;
			step2.z = step1.z * this->temp;
			step2.y = sin(this->xrot * PIdiv180);
			this->viewdirection->x = step2.x;
			this->viewdirection->y = step2.y;
			this->viewdirection->z = step2.z;
			this->viewchanged = false;
		}

		cgl::Vector3f SimpleCamera::GetPosition()
		{
			cgl::Vector3f res;
			res.x = this->position->x;
			res.y = this->position->y;
			res.z = this->position->z;
			return res;
		}
		cgl::Vector3f SimpleCamera::GetDirection()
		{
			cgl::Vector3f res;
			res.x = this->viewdirection->x;
			res.y = this->viewdirection->y;
			res.z = this->viewdirection->z;
			return res;
		}

		void SimpleCamera::Move(cgl::Vector3f direction)
		{
			this->position->x += direction.x;
			this->position->y += direction.y;
			this->position->z += direction.z;
		}

		void SimpleCamera::RotateY(float angle)
		{
			this->yrot += angle;
			this->viewchanged = true;
		}

		void SimpleCamera::RotateX(float angle)
		{
			this->xrot += angle;
			this->viewchanged = true;
		}
	
		void SimpleCamera::Render()
		{
			glRotatef(-this->xrot, 1.0, 0.0, 0.0);
			glRotatef(-this->yrot, 0.0, 1.0, 0.0);
			glRotatef(-this->zrot, 0.0, 0.0, 1.0);
			glTranslatef(-this->position->x, -this->position->y, -this->position->z);
		}

		void SimpleCamera::MoveForward(float distance)
		{
			if(this->viewchanged == true)
			{
				this->GetViewDirection();
			}
			this->move.x = this->viewdirection->x * -distance;
			this->move.y = this->viewdirection->y * -distance;
			this->move.z = this->viewdirection->z * -distance;
			this->position->x += this->move.x;
			this->position->y += this->move.y;
			this->position->z += this->move.z;
		}

		void SimpleCamera::Strafe(float distance)
		{
			if(this->viewchanged == true)
			{
				this->GetViewDirection();
			}
			this->move.x = -this->viewdirection->x * -distance;
			this->move.y = 0.0;
			this->move.z = this->viewdirection->z * -distance;
			this->position->x += this->move.x;
			this->position->y += this->move.y;
			this->position->z += this->move.z;
		}

		//Youtube video tutorial camera, movement, mouse, nice
		/*
		float x = 0.0,y = 0.0,z = 0.0;
		float camYaw = 0.0;
		float camPitch =0.0;
		void lockCamera()
		{
			if(camPitch > 90)
			{
				camPitch = 90;
			}
			else
			{
				if(camPitch < -90)
				{
					camPitch = -90;
				}
			}
			if(camYaw < 0.0)
			{
				camYaw += 360.0;
			}
			else
			{
				if(camYaw > 360.0)
				{
					camYaw -= 360.0;
				}
			}
		}

		//Angle is in celsius, need radians
		void moveCamera(float distance, float direction)
		{
			float radian = (camYaw + direction) * PIdiv180;
			x -= sin(radian) * distance;
			z -= cos(radian) * distance;
		}

		void moveCameraUp(float distance, float direction)
		{
			float radian = (camPitch + direction) * PIdiv180;
			y += sin(radian) * distance;
		}

		void Control(float movevelocity, float mousevelocity, bool mouseIn)
		{
			if(mouseIn)
			{
				int midx = 400;	//Half of screen sizes
				int midy = 300
				int tmpx, tmpy;
				tmpx = mouse->cursorx;
				tmpy = mouse->cursory;
				camYaw += mousevelocity * (midx-tmpx);
				camPitch += mousevelocity * (midy-tmpy);
				lockCamera();
				mouse->SetCursorPosition(midx, midy);	//Reset to middle
				if(keyboard->isKeyPressed("W") == true)
				{
					if(camPitch != 90 && camPitch != -90)
					{
						moveCamera(movevelocity, 0.0);
					}
					moveCameraUp(movevelocity, 0.0);
				}
				else
				{
					if(keyboard->isKeyPressed("S") == true)
					{
						if(camPitch != 90 && camPitch != -90)
						{
							moveCamera(movevelocity, 180.0);
						}
						moveCameraUp(movevelocity, 180.0);
					}
				}
				if(keyboard->isKeyPressed("A") == true)
				{
					moveCamera(movevelocity, 90.0);
				}
				else
				{
					if(keyboard->isKeyPressed("D") == true)
					{
						moveCamera(movevelocity, 270.0);
					}
				}
			}
			glRotatef(-camPitch, 1.0, 0.0, 0.0);
			glRotatef(-camYaw, 0.0, 1.0, 0.0);
		}


		void UpdateCamera()
		{
			glTranslatef(-x, -y, -z);
		}

		//Outside the class
		//p (pause) toggles on off the mouseIn (mouse in, if app is in focus)
		void Display()
		{
			Control(0.2, 0.2, mousein);
			UpdateCamera();
		}

		*/
	};

}

#endif