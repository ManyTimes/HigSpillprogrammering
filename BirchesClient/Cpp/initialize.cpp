#include "../Header/initialize.h"

void Initialize()
{
	ReadConfigurationFile();		//Reads data from textfile "config.txt"
	InitializeGame();				//Creates the window, etc.
	InitializeRender();
}

void ReadConfigurationFile()
{
	ifstream configfile;
	configfile.open("Configuration.txt");
	std::string readline;
	int linenumber = 0;
	while(!configfile.eof() && linenumber < 5)
	{
		std::getline(configfile,readline);
		if(linenumber == 2)
		{
			JOINADDRESS = ReturnConfigurationValue(readline);
		}
		if(linenumber == 3)
		{
			JOINPORTNUMBER = ReturnConfigurationValue(readline);
		}
		if(linenumber == 4)
		{
			PLAYERNAME = ReturnConfigurationValue(readline);
		}
		linenumber ++;
		std::cout << " LINE : " << linenumber << " : " << readline << std::endl;
	}
	configfile.close();
}

std::string ReturnConfigurationValue(string readline)
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
	opengl = new cgl::OpenGL(SCREENWIDTH,SCREENHEIGHT, 0,0,0,0,24,0, false, false);
	opengl->Initialize(GAMENAME, false, false, true, true, true);

	camera = new cgl::Camera(cgl::Vector3f(0.0, 1.0, -100.0), cgl::Vector3f(0.0, 0.0, 0.0), 500,800, 0.01, 100.0);
	//Objects Init
	mouse = cgl::Mouse::GetInstance(SCREENWIDTH, SCREENHEIGHT);
	keyboard = cgl::Keyboard::GetInstance();

	
	//Load Images for the buttons
	imgbtnQuitGameClicked = new cgl::Image2D();
	imgbtnQuitGameClicked->LoadBMP("Data/btnQuitGameClicked.bmp");
	imgbtnExitClicked = new cgl::Image2D();
	imgbtnExitClicked->LoadBMP("Data/btnExitClicked.bmp");
	imgbtnCancelClicked = new cgl::Image2D();
	imgbtnCancelClicked->LoadBMP("Data/btnExitClicked.bmp");
	imgbtnStartClicked = new cgl::Image2D();
	imgbtnStartClicked->LoadBMP("Data/btnExitClicked.bmp");
	imgbtnExit = new cgl::Image2D();
	imgbtnExit->LoadBMP("Data/btnExit.bmp");
	imgbtnCancel = new cgl::Image2D();
	imgbtnCancel->LoadBMP("Data/btnCancel.bmp");
	imgbtnStart = new cgl::Image2D();
	imgbtnStart->LoadBMP("Data/btnStart.bmp");
	imgMenu = new cgl::Image2D();
	imgMenu->LoadBMP("Data/imgMenu.bmp");
	imgMenu->width =32;
	imgMenu->height = 24;
	imgBackground = new cgl::Image2D();
	std::string imgbackground = "Data/imgBackground" + cgl::i2s(cgl::GetRandomInt(1,3)) + ".bmp";
	imgBackground->LoadBMP((char*)imgbackground.c_str());
	imgbtnQuitGame = new cgl::Image2D();
	imgbtnQuitGame->LoadBMP("Data/btnQuitGame.bmp");
	//Init Buttons
	btnExit = new cgl::Button(mouse, SCREENWIDTH,SCREENHEIGHT, SCREENWIDTH,SCREENHEIGHT, 0,0, 400, 300);	//Bottom right
	btnExit->leftclick = true;
	btnExit->SetSize(100,100);
	btnExit->SetTexture(imgbtnExit->ID, imgbtnExitClicked->ID);
	
	btnStart = new cgl::Button(mouse, SCREENWIDTH, SCREENHEIGHT, SCREENWIDTH, SCREENHEIGHT, 0,0,  100, 300);
	btnStart->leftclick = true;
	btnStart->SetSize(100, 100);
	btnStart->SetTexture(imgbtnStart->ID, imgbtnStartClicked->ID);
	
	btnCancel = new cgl::Button(mouse, SCREENWIDTH, SCREENHEIGHT, SCREENWIDTH, SCREENHEIGHT, 0,0, 300, 200);
	btnCancel->leftclick = true;
	btnCancel->SetSize(100, 100);
	btnCancel->SetTexture(imgbtnCancel->ID, imgbtnCancelClicked->ID);

	btnQuitGame = new cgl::Button(mouse, SCREENWIDTH, SCREENHEIGHT, SCREENWIDTH, SCREENHEIGHT, 0,0, 400,100);
	btnQuitGame->leftclick = true;
	btnQuitGame->SetSize(100,100);
	btnQuitGame->SetTexture(imgbtnQuitGame->ID, imgbtnQuitGameClicked->ID);


	textFeedback = new cgl::Text(SCREENWIDTH, SCREENHEIGHT);
	textFeedback->RGB[0] = 0.9f;
	textFeedback->RGB[1] = 0.2f;
	textFeedback->RGB[2] = 0.0f;
	text = new cgl::Text(SCREENWIDTH,SCREENHEIGHT);
	text->RGB[0] = 0.0f;
	text->RGB[1] = 0.5f;
	text->RGB[2] = 0.9f;		//Blue-ish color on text drawn

	gamestate = 0 ;				//Drawing main menu first

	//Init 3D stuff like weather, models for a player... Game relevant objects
	float RGB[3];
	RGB[0] = RGB[1] = RGB[2] = 0.9f;
	weather = new cgl::Weather(RGB, 150, 5);
	weatherTexture = new cgl::Image2D();
	weatherTexture->LoadBMP("Data/Snow.bmp");
	weather->SetTextures(weatherTexture->ID, weatherTexture->ID);

	//INIT 3D terrain
	GLfloat rgbFog[] = { 0.15f, 0.15f, 0.15f, 0.0f };
	opengl->Fog(true, rgbFog, 5.0f, 40.0f);

	mod3d.Load("Data/TestModel3.3ds");
	//mod3d

}

void InitializeGame()
{
	//Loading of an MD2 model file, works, at least no errors, but I cannot get it to be drawn... Reading fails, every vertice/position seems to be "0".
	//test = MD2Model::load("Data/rock.md2");

	//cgl::Image2D* img = new cgl::Image2D();
	//img->LoadBMP("Data/rock.bmp");
	//rock = new cgl::ModelMD2("Data/rock.md2", img->ID, MD2Normals, 10);
	//rock->SetAnimation("run");
	//Server only holds terrain and grid, to do some calculations for collision, etc...
	terrain = new cgl::Terrain("Data/heightmap.bmp", 10);						//Would have been nice to download the image, heightmap.bmp from the server actually!
																					//It is actually kind of easy, just sending over "img->dataBMP"... bit by bit... :)
	grid = new cgl::Grid(terrain, cgl::GridSize::SEVERAL);						//FEW SEVERAL LOTS
	music = new cgl::Sound("birchtheme.wav", true, true);
	soundAttack = new cgl::Sound("birchtheme.wav", true, false);
	soundHit = new cgl::Sound("birchtheme.wav", true, false);
	client = new cgl::NetworkClient(JOINADDRESS, cgl::s2i(JOINPORTNUMBER));
	SERVERNAME = client->host;

	//cgl::Image2D* unitTexture = new cgl::Image2D();
	//unitTexture->LoadBMP("Data/snake.bmp");
	//delete unitTexture

//	modd2 = new cgl::ModelMD2("Data/snake.md2", unitTexture->ID, 0.125f);
	float rgb[3]  = { 0.7f, 0.0f, 0.0f };
	projectilepl1 = new cgl::Projectile(rgb, 15.0, 15, 10, 1.0, 2.0);

}

