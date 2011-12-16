#include "../Header/main.h"

int main(int argc, char *argv[])
{
	std::cout << "FLOAT TO S: " << cgl::f2s(15.05f) << std::endl;
	std::cout << "FLOAT TO C: " << cgl::f2c(15.05f) << std::endl;
	Initialize();		//Initializes everything
	Program();			//Starts the program/Server/game loop

	return 0;
}


