#include "../Header/main.h"
int main(int argc, char *argv[])
{

	cgl::CGLInitialize();
	Initialize();		//Initializes everything
	GameLoop();				//Starts the program/Server/game loop

	//Set model does not work, yet!!! Library error, so player cannot be drawn!
	// Fixed - Nic, if anyone is gonna test it has to be done after Initialize()
	//cgl::Player pl;
	//pl.SetModel("Data/TestModel3.3DS");

	
	return 0;
}

