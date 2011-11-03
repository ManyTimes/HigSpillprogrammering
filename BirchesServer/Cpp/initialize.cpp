#include "../Header/initialize.h"

void Initialize()
{
	ReadConfigurationFile();		//Reads data from textfile "config.txt"
	InitializeRender();				//Creates the window, etc.
	InitializeSql();				//Establishes a connection
	InitializeServer();				//Starts listening on port
}


//Reading a file should be within the library actually... :)
//And can just read it multiple times, each time for each line, or read whole into an
//string array, and return "linenumber"... Then after use, call "Clear(); or Close());"...
void ReadConfigurationFile()
{
	ifstream configfile;
	configfile.open("ConfigurationServer.txt");
	std::string readline;
	int linenumber = 0;
	while(!configfile.eof() && linenumber < 13)
	{
		getline(configfile,readline);
		if(linenumber == 2)
		{
			PORTNUMBER = ReturnConfigurationValue(readline);
		}
		if(linenumber == 3)
		{
			SERVERNAME = ReturnConfigurationValue(readline);
		}
		if(linenumber == 4)
		{
			MAXIMUMPLAYERS = cgl::s2i(ReturnConfigurationValue(readline));
		}
		if(linenumber == 8)
		{
			SQLSERVERNAME = ReturnConfigurationValue(readline);
		}
		if(linenumber == 9)
		{
			SQLDATABASENAME = ReturnConfigurationValue(readline);
		}
		if(linenumber == 10)
		{
			SQLUSER = ReturnConfigurationValue(readline);
		}
		if(linenumber == 11)
		{
			SQLPASSWORD = ReturnConfigurationValue(readline);
		}
		if(linenumber == 12)
		{
			SQLTIMEOUTSECONDS = cgl::s2i(ReturnConfigurationValue(readline));
			if(SQLTIMEOUTSECONDS < 1)
			{
				SQLTIMEOUTSECONDS = 1;
			}
		}
		linenumber ++;
		std::cout << " LINE : " << linenumber << " : " << readline << std::endl;
	}
	configfile.close();
}

//Returns the value from the "Value Column" within the ConfigurationServer.txt where a line was read
string ReturnConfigurationValue(string readline)
{
	string temp;
	for(int i = 0; i < readline.length(); i++)
	{
		if(i > 15)
		{
			temp += readline[i];
		}
	}
	return temp;
}

void InitializeRender()
{
	//Main Window
	opengl = new cgl::OpenGL(800,600, 0,0,0,0,24,0, false, false);
	opengl->Initialize("Server: " + SERVERNAME, false, false, true, true, true);
	//Viewport
	glViewport(0, 0, SCREENWIDTH, SCREENHEIGHT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(40.0, (double)SCREENWIDTH / (double)SCREENHEIGHT, 1.0, 200.0);
	//Objects Init
	mouse = cgl::Mouse::GetInstance(800,600);
	keyboard = cgl::Keyboard::GetInstance();

	imgbtnExitClicked = new cgl::Image2D();
	imgbtnExitClicked->LoadBMP("Data/btnExitClicked.bmp");
	imgbtnExit = new cgl::Image2D();
	imgbtnExit->LoadBMP("Data/btnExit.bmp");
	btnExit = new cgl::Button(mouse, SCREENWIDTH,SCREENHEIGHT, SCREENWIDTH,SCREENHEIGHT, 0,0, 700,0);	//Bottom right
	btnExit->leftclick = true;
	btnExit->SetSize(100,100);
	btnExit->SetTexture(imgbtnExit->ID, imgbtnExitClicked->ID);

	text = new cgl::Text(SCREENWIDTH,SCREENHEIGHT);
	text->RGB[0] = 0.0f;
	text->RGB[1] = 0.5f;
	text->RGB[2] = 0.9f;		//Blue
}

void InitializeServer()
{
	//Server only holds terrain and grid, to do some calculations for collision, etc...
	terrain = new cgl::Terrain("Data/heightmap.bmp", 20);
	grid = new cgl::Grid(terrain, cgl::GridSize::SEVERAL);	//SMALL MEDIUM LARGE*/
	server = new cgl::NetworkServer(cgl::s2i(PORTNUMBER), MAXIMUMPLAYERS);
	player = new cgl::Player[MAXIMUMPLAYERS];
	for(int i = 0; i < MAXIMUMPLAYERS; i++)
	{
		player[i].action = 0;
		player[i].deaths = 0;
		player[i].kills = 0;
		player[i].hitpoints = 0;
		player[i].playername = "<Empty Slot>";
		player[i].SetPosition(cgl::GetRandomFloat(-5.0f, 5.0f), 1.0f, cgl::GetRandomFloat(-5.0, 5.0f));
		std::cout << " X Y " << player[i].position.x << ", " << player[i].position[1] << std::endl;
	}
}

void InitializeSql()
{
	sqlcon = new cgl::SqlConnection(SQLSERVERNAME, SQLDATABASENAME, SQLUSER, SQLPASSWORD, 1);
	sqlcmd = new cgl::SqlCommand(sqlcon);
}

