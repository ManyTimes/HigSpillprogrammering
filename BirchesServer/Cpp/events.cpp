#include "../Header/events.h"

void KeyboardClicked()
{
	
}

void MouseClicked()
{
	if(btnExit->isPressed() == true)
	{	
		play = false;
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