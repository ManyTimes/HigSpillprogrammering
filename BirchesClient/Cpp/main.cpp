#include "../Header/main.h"

int main(int argc, char *argv[])
{
	//Set model does not work, yet!!! Library error, so player cannot be drawn!
//	cgl::Player pl;
//pl.SetModel("Data/TestModel3.3DS");

	cgl::CGLInitialize();
	Initialize();		//Initializes everything
	GameLoop();				//Starts the program/Server/game loop

	return 0;
}

