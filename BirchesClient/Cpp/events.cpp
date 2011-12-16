#include "../Header/events.h"

void Events()
{
	KeyboardClicked();
	MouseClicked();
}

void KeyboardClicked()
{
	if(gamestate == 0)					//Hotkeys in the "mainmenu"
	{
		if(keyboard->isKeyPressed("ESC") == true)
		{
			play = false;				//Exit the game loop and program
		}
		if(keyboard->isKeyPressed("S") == true || keyboard->isKeyPressed("ENTER") == true)		//Start game
		{
			DISABLEMOUSECONTROL = true;
			ConnectToServer();
			gamestate = 1;
		}	
		if(keyboard->isKeyPressed("E") == true)
		{
			play = false;				//Exiting the game loop and program
		}
		if(keyboard->isKeyPressed("ALT") == true && keyboard->isKeyPressed("F4") == true)
		{
			play = false;				//Exiting the program
		}
	}
	else
	{
		if(gamestate == 1)				//We are playing, hotkeys for moving (WASD space enter)
		{
			if(keyboard->isKeyPressed("Q") == true)
			{
				for(int a = 0; a < 4; a++)
				{
					std::cout << "Player: " << a << " ID, " << player[a].ID << " X Y Z :" << unit[a].position.x << ", " << unit[a].position.y << ", " << unit[a].position.z << std::endl;
					std::cout << "Your ID: " << thisPlayer << std::endl;
				}
			}
			if(keyboard->isKeyPressed("F10") == true)
			{
				gamestate = 2;			//Viewing menu while playing
			}
			if(keyboard->isKeyPressed("W") == true)
			{
				SendDataForward();
				//This was for 3DS models... Right now; using MD2 (99-style)
				//cgl::Vector3f& pos = unit[0].GetPositionRef();
				
			}
			if(keyboard->isKeyPressed("D") == true)
			{
				SendDataRight();
				//cgl::Vector3f& pos = unit[0].GetPositionRef();
				//pos.x += 0.9;
			}
			if(keyboard->isKeyPressed("A") == true)
			{
				SendDataLeft();
				//cgl::Vector3f& pos = unit[0].GetPositionRef();
				//pos.x -= 0.9;
			}
			if(keyboard->isKeyPressed("S") == true)
			{
				SendDataBackward();
				//cgl::Vector3f& pos = unit[0].GetPositionRef();
				//pos.z += 0.9;
			}
			if(keyboard->isKeyPressed("SPACE") == true)
			{
				//cgl::Vector3f& pos = unit[0].GetPositionRef();
				SendDataShoot();
				//projectilepl1->Shoot(pos.x, pos.z, 1.0, 1);
			}
		}
		else
		{//We are in game, but the "Menu" (quit/continue) is showing
			if(keyboard->isKeyPressed("C") ==true)
			{
				gamestate  = 1;			//Back to the game, menu is not drawn
			}
			else
			{							//Quit Game, back to main menu
				if(keyboard->isKeyPressed("Q") == true)
				{
					DISABLEMOUSECONTROL = false;
					ISCONNECTED = false;
					DisconnectFromServer();	
					opengl->SetWindowTitle(GAMENAME);
					thisPlayer = -1;
					client->Exit();
					gamestate = 0;
					SERVERRESPONSE = false;	

				}
			}
		}
	}
}

void MouseClicked()
{
	if(gamestate == 0)					//Main Menu
	{
		if(btnExit->isPressed() == true)
		{	
			play = false;				//Exit the game loop and program
		}
		if(btnStart->isPressed() == true)
		{
			DISABLEMOUSECONTROL = true;
			ConnectToServer();
			gamestate = 1;
		}
	}
	else
	{
		if(gamestate == 2)
		{
			if(btnQuitGame->isPressed() == true)
			{	
				DisconnectFromServer();	//Say goodbye to the server
				opengl->SetWindowTitle(GAMENAME);
				ISCONNECTED = false;
				client->Exit();			//Exit server
				gamestate = 0;			//Back to main menu
				thisPlayer = -1;
				DISABLEMOUSECONTROL = false;
				SERVERRESPONSE = false;	//Need new response from server
			}
			if(btnCancel->isPressed() == true)
			{
				gamestate = 1;			//Back to the game
			}
		}
	}
	//There is no gamestate on the server.
	/*switch(gamestate)
	{
	case 0:							//We are in the main menu
		break;
	case 1:
		break;						//We are in the game, playing, shooting, moving
	case 2:
		break;						//We are in a menu, Exit/Continue playing
	}*/
}