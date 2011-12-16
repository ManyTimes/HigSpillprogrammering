#include "../Header/simplecamera.h"

namespace cgl
{
	//CONSTRUCTORS
	SimpleCamera::SimpleCamera(cgl::Keyboard* keyboardObject, cgl::Mouse* mouseObject, int viewportWidth, int viewportHeight)
	{
		this->movevelocity = this->mousevelocity = 0.2f;
		this->cameratype = 0;			//Free View, wasd and mouse to look around 
		this->movekeys[0] = 'W';
		this->movekeys[1] = 'A';
		this->movekeys[2] = 'S';
		this->movekeys[3] = 'D';
		this->viewportMidX = viewportWidth/2;
		this->viewportMidY = viewportHeight/2;
		this->temp = 0.0;
		this->mousept = mouseObject;
		this->keyboardpt = keyboardObject;
		PIdiv180 =  PI/180;
		position = cgl::Vector3f(0, 0, 0);
		camYaw = 0.0;
		camPitch = 0.0;
		this->lockViewAngleTopBottom = true;
		this->AllowMovement = true;
		this->cameratype = 0;
	}
	void SimpleCamera::Initialize(cgl::Keyboard* keyboardObject, cgl::Mouse* mouseObject, int viewportWidth, int viewportHeight)
	{
		this->cameratype = 0;
		this->movevelocity = this->mousevelocity = 0.2f;
		this->cameratype = 0;			//Free View, wasd and mouse to look around 
		this->movekeys[0] = 'W';
		this->movekeys[1] = 'A';
		this->movekeys[2] = 'S';
		this->movekeys[3] = 'D';
		this->viewportMidX = viewportWidth/2;
		this->viewportMidY = viewportHeight/2;
		this->temp = 0.0;
		this->mousept = mouseObject;
		this->keyboardpt = keyboardObject;
		PIdiv180 =  PI/180;
		position = cgl::Vector3f(0, 0, 0);
		camYaw = 0.0;
		camPitch = 0.0;
		this->lockViewAngleTopBottom = true;
		this->AllowMovement = true;
	}
	SimpleCamera::SimpleCamera()
	{
		this->cameratype = 0;
		cgl::Cout("SimpleCamera, use a pointer and initialize it with its constructor");
	}

	//INITALIZE CAMERA SETTINGS
	void SimpleCamera::Initialize(float movespeed, float mousevelocity)
	{
		this->mousevelocity = mousevelocity;
		this->movevelocity = movespeed;
	}
	void SimpleCamera::Initialize(float movespeed, float mousevelocity, char movementKeys[4], cgl::CAMERATYPE type)
	{
		this->mousevelocity = mousevelocity;
		this->movevelocity = movespeed;
		if(type != 0)		//Free View
		{
			cgl::Cout("Camera type is not set to FreeView. It is required to call the other overload function of Camera::initialize(), that takes an entity.");
		}
		this->cameratype = type;
		this->movekeys[0] =  movementKeys[0];
		this->movekeys[1] =  movementKeys[1];
		this->movekeys[2] =  movementKeys[2];
		this->movekeys[3] =  movementKeys[3];
	}
	void SimpleCamera::Initialize(float movespeed, float mousevelocity, char movementKeys[4], cgl::CAMERATYPE type, cgl::Entity* objectToFollow)
	{
		this->mousevelocity = mousevelocity;
		this->movevelocity = movespeed;
		if(type == 0)		//Free View
		{
			cgl::Cout("Camera type is set to FreeView. It is suggested to call the other overload function of Camera::initialize(), that does not take an entity.");
		}
		else				//FPS or Third Person
		{
			cgl::Cout("This camera type is not implemented, choose FreeView, 0");
		}
		this->cameratype = type;
		this->movekeys[0] =  movementKeys[0];
		this->movekeys[1] =  movementKeys[1];
		this->movekeys[2] =  movementKeys[2];
		this->movekeys[3] =  movementKeys[3];
		this->attachedObject = objectToFollow;
	}
	
	//FUNCTIONS
	void SimpleCamera::LockCamera()
	{
		if(camPitch>90)
		{
			camPitch=90;
		}
		else
		{
			if(camPitch<-90)
			{
				camPitch=-90;
			}
		}
		if(camYaw<0.0)
		{
			camYaw+=360.0;
		}
		else
		{
			if(camYaw>360.0)
			{
				camYaw-=360;
			}
		}
	}


	void SimpleCamera::MoveCamera(float distance, float direction)
	{
		temp=(camYaw+direction)*PIdiv180;	//convert the degrees into radians
		this->position.x-=sin(temp)*distance;	//calculate the new coorinate, if you don't understand, draw a right triangle with the datas, you have
		this->position.z-=cos(temp)*distance;	//and try to calculate the new coorinate with trigonometric functions, that should help
	}

	void SimpleCamera::MoveCameraUp(float distance, float direction)
	{
		//the the same, only this time we calculate the y coorinate
		temp=(camPitch+direction)*PIdiv180;
		this->position.y+=sin(temp)*distance;
	}

	void SimpleCamera::MoveForward(float distance)
	{
		MoveCamera(distance, 0.0);				//Forward
	}

	void SimpleCamera::MoveBackwards(float distance)
	{
		MoveCamera(distance, 180.0);				//Backwards, opposite angle
	}

	void SimpleCamera::MoveStrafeLeft(float distance)
	{
		MoveCamera(distance, 90.0);
	}

	void SimpleCamera::MoveStrafeRight(float distance)
	{
		MoveCamera(distance, 270);
	}

	//void SimpleCamera::MoveStrafe(float distance)

	void SimpleCamera::Move()
	{
		if(this->cameratype == 0)	//Free View
		{
			camYaw += mousevelocity * (viewportMidX-this->mousept->cursorx);
			camPitch += mousevelocity * (viewportMidY-this->mousept->cursory);
			if(this->lockViewAngleTopBottom == true)
			{
				LockCamera();
			}
			this->mousept->SetCursorPosition(this->viewportMidX, this->viewportMidY);	

			if(this->AllowMovement == true)
			{
				if(keyboardpt->isKeyPressed(this->movekeys[0]) == true)
				{
					if(camPitch != 90 && camPitch != -90)
					{
						MoveCamera(movevelocity, 0.0);
					}
					MoveCameraUp(movevelocity, 0.0);
				}
				else
				{
					if(keyboardpt->isKeyPressed(this->movekeys[2]) == true)
					{
						if(camPitch != 90 && camPitch != -90)
						{
							MoveCamera(movevelocity,180.0);
						}
						MoveCameraUp(movevelocity,180.0);
					}
				}
				if(keyboardpt->isKeyPressed(this->movekeys[1]) == true)
				{
					MoveCamera(movevelocity,90);
				}
				else
				{
					if(keyboardpt->isKeyPressed(this->movekeys[3]) == true)
					{
						MoveCamera(movevelocity,270);
					}
				}
			}
			glRotatef(-camPitch,1.0,0.0,0.0);	//rotate the camera (more precisly move everything in the opposit direction)
			glRotatef(-camYaw,0.0,1.0,0.0);
		}
	}


	void SimpleCamera::Update()
	{
		this->Move();
		glTranslatef(-this->position.x, -this->position.y, -this->position.z);
	}

	void SimpleCamera::Update(bool disableControlOfCursor)
	{
		if(disableControlOfCursor == true)		//Cursor is used to look around in the view
		{										//through hiding the cursor
			this->Update();
		}
		else
		{
			glTranslatef(-this->position.x, -this->position.y, -this->position.z);
		}
	}
	cgl::Vector3f SimpleCamera::GetViewDirection()
	{
		cgl::Vector3f step1, step2;
		//Rotate Y-axis
		step1.x = cos((this->camYaw + 90.0) * PIdiv180);
		step1.z = -sin((this->camYaw + 90.0) * PIdiv180);
		//Rotate X-axis
		this->temp = cos(this->camPitch * PIdiv180);
		step2.x = step1.x * this->temp;
		step2.z = step1.z * this->temp;
		step2.y = sin(this->camPitch * PIdiv180);
		return step2;
	}


}