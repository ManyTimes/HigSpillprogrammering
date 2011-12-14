#include "../Header/gameloop.h"

void GameLoop()
{
	int programtime = 1;				//Gametime is the loop, splits up "work" into seperate "frames"
	while(play)
	{
		switch(programtime)
		{
		case 1:							//Do network stuff, send, receive
			Network();
			break;
		case 2:							//Takes input, keyboard/mouse
			Events();
			break;
		case 3:							//Render stuff, call <object>->Draw();
			Render();
			break;
		case 4:							//Do calculations, collision, grid Update...etc
			Update();
			break;
		}
		programtime++;
		if(programtime > 4)
		{
			programtime = 1;
		}
		cgl::Sleep(SLEEPTIME);
	}
	opengl->Exit();
}

