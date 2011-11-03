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
			if(keyboard->isKeyPressed("F10") == true)
			{
				gamestate = 2;			//Viewing menu while playing
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
					DisconnectFromServer();	
					
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
				client->Exit();			//Exit server
				gamestate = 0;			//Back to main menu
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