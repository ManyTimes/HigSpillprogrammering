#include "../Header/opengl.h"
namespace cgl
{
	//************CONSTRUCTORS************
	//Initializes OpenGL functions, window size and calls openGL standard initialize functions
	OpenGL::OpenGL()
	{
		this->height = 600;
		this->width = 800;
		if(glfwInit() == 0)
		{
			cgl::Error("Could not initialize GLFWInit()");
		}
		if(glfwOpenWindow((int)this->width,(int)this->height,0,0,0,0,0,0,GLFW_WINDOW) != 1)
		{
			cgl::Error("Could not open GLFW Window");       
		}
		GLenum initReturn;
		if((initReturn = glewInit()) != GLEW_OK)
		{
			std::cout << glewGetErrorString(initReturn)<< std::endl;
			exit(1);
		}
		glfwSetWindowPos(0,0);
		glfwSetWindowTitle("Custom Game Library");
		std::cout << "CGL MESSAGE: OpenGL Created successfully, initglfw has been called." << std::endl;
	}

	OpenGL::OpenGL(int width,int height, int redbits, int greenbits, int bluebits, int alphabits, int depthbits, int stencilbits, bool windowresize, bool fullscreen)
	{
		this->width = width;
		this->height = height;
		if(glfwInit() != 1)
		{
			cgl::Error("Could not initialize GLFWINIT()");
		}
		if(windowresize == true)
		{
			glfwOpenWindowHint(GLFW_WINDOW_NO_RESIZE, 1);
		}
		else
		{
			//Call GLFW callback function of resizing, built in function.
		}
		if(this->height == 0 && this->width == 0)
		{
			this->height = 600;
			this->width = 800;
			if(glfwOpenWindow(this->width, this->height, redbits, greenbits, bluebits, alphabits, depthbits, stencilbits, GLFW_FULLSCREEN) != 1)
			{
				cgl::Error("Could not open GLFW Window");
			}
		}
		else
		{
			if(fullscreen == true)
			{
				if(glfwOpenWindow(this->width, this->height, redbits, greenbits, bluebits, alphabits, depthbits, stencilbits, GLFW_FULLSCREEN) != 1)
				{
					cgl::Error("Could not open window");
				}
			}
			else
			{
				if(this->width < 1)
				{
					this->width = 800;
				}
				if(this->height < 1)
				{
					this->height = 600;
				}
				if(glfwOpenWindow(this->width, this->height, redbits, greenbits, bluebits, alphabits, depthbits, stencilbits, GLFW_WINDOW) != 1)
				{
					cgl::Error("Could not open GLFW Window");
				}
			}
		}
		//glfwEnable(GLFW_AUTO_POLL_EVENTS);
		GLenum initReturn;
		if((initReturn = glewInit()) != GLEW_OK)
		{
			std::cout << glewGetErrorString(initReturn);
			cgl::Error("Could not initialize glew");
		}
		glfwSetWindowPos(0,0);
		glfwSetWindowTitle("Custom Game Library");
		std::cout << "CGL MESSAGE: OpenGL Created successfully, initglfw has been called." << std::endl; 

		//Additional Init Settings
		//glViewport(0,0, this->width, this->height);
	}

	//************FUNCTIONS************
	void OpenGL::Initialize(std::string windowTitle, bool enableLighting, bool enableCullFace, bool enableDepthTest, bool enable2D, bool enableLineSmoothing)
	{
		glfwSetWindowTitle(windowTitle.c_str());
		GLenum initReturn;
		if((initReturn = glewInit()) != GLEW_OK)
		{
			std::cout << glewGetErrorString(initReturn) <<  std::endl << "Could not initialize glew" << std::endl;
			exit(1);
		}
	/*	glMatrixMode(GL_PROJECTION);
		glLoadIdentity();

		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();*/

		if(enableDepthTest == true)
		{
			glEnable(GL_DEPTH_TEST);	// Gives depth testing
		}
		if(enableCullFace == true)
		{
			glEnable(GL_CULL_FACE);		// Don't draw the backside
		}
		if(enableLighting == true)
		{
			glEnable(GL_LIGHTING);		// Enables fixed pipeline lighting
		}
		glEnable(GL_LIGHT0);			// Enables light0
		if(enable2D == true)
		{
			glEnable(GL_TEXTURE_2D);	// Enables use of 2D textures
		}
		glEnable(GL_NORMALIZE);			// Normals automaticially normalized
		if(enableLineSmoothing == true)
		{
			glEnable(GL_LINE_SMOOTH);
		}

	/*	GLfloat mat_specular[] = { .5, 0.5, 0.5, 1.0 };
		GLfloat mat_shininess[] = { 25.0 };
		glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
		glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
		glColorMaterial ( GL_FRONT_AND_BACK, GL_EMISSION ) ;
		glEnable ( GL_COLOR_MATERIAL ) ;
		glFrontFace(GL_CW);				// Winding of elements*/

		/*GLenum initReturn;
		if((initReturn = glewInit()) != GLEW_OK)
		{
			std::cout << glewGetErrorString(initReturn)<< std::endl;
			exit(1);
		}*/
		//glfwSetWindowTitle(windowTitle.c_str());

		//glEnable(GL_TEXTURE_2D);									// Enable Texture Mapping ( NEW )
		//glShadeModel(GL_SMOOTH);									// Enable Smooth Shading
		glClearColor(1.0f, 1.0f, 1.0f, 0.5f);						// White Background
		glClearDepth(1.0f);											// Depth Buffer Setup
		glEnable(GL_DEPTH_TEST);									// Enables Depth Testing
		glDepthFunc(GL_LEQUAL);										// The Type Of Depth Testing To Do
		glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);			// Really Nice Perspective Calculations
	}

	void OpenGL::CreateViewport2D(int viewWidth, int viewHeight, int startPositionX, int startPositionY, float zNear, float zFar)
	{
		glViewport(startPositionX, startPositionY, viewWidth, viewHeight);
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glOrtho(startPositionX, viewWidth, startPositionY, viewHeight, zNear, zFar);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		glEnable(GL_TEXTURE_2D);
		glEnable(GL_DEPTH_TEST);
		glDepthMask(GL_TRUE);
	}

	void OpenGL::CreateViewport3D(int viewWidth, int viewHeight, int startPositionX, int startPositionY, float zNear, float zFar)
	{
		glViewport(startPositionX, startPositionY, viewWidth, viewHeight);
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluPerspective( 45.0, 1.0f, 0.1f, 500.0 );
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
	}

	void OpenGL::CreateViewPort(bool dimension_3D, int viewWidth, int viewHeight, int startPositionX, int startPositionY, float zNear, float zFar)
	{
		glViewport(startPositionX, startPositionY, viewWidth, viewHeight);
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		if(dimension_3D == true)
		{
			gluPerspective( 45.0, 1.0f, 0.1f, 500.0 );
		}
		else
		{
			glOrtho(startPositionX, viewWidth, startPositionY, viewHeight, zNear, zFar);
		}
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();

		/*GLUquadricObj *quadric;	
		if(dimension_3D == true)
		{	
			quadric=gluNewQuadric();											// Create A Pointer To The Quadric Object
			gluQuadricNormals(quadric, GLU_SMOOTH);								// Create Smooth Normals 
			gluQuadricTexture(quadric, GL_TRUE);	

			glTranslatef(0.0f,0.0f,-14.0f);								// Move 14 Units Into The Screen

			glRotatef(1,1.0f,0.0f,0.0f);								// Rotate By xrot On The X-Axis
			glRotatef(1,0.0f,1.0f,0.0f);								// Rotate By yrot On The Y-Axis
			glRotatef(1,0.0f,0.0f,1.0f);								// Rotate By zrot On The Z-Axis

			glEnable(GL_LIGHTING);										// Enable Lighting
			gluSphere(quadric,4.0f,32,32);								// Draw A Sphere
			glDisable(GL_LIGHTING);			
		}*/
	}

	
	void OpenGL::DrawImage(GLuint textureID, float posX, float posY, int imageWidth, int imageHeight)
	{
		glBindTexture(GL_TEXTURE_2D, textureID);
		 glBegin(GL_QUADS);
		  glTexCoord2f(0.0f,1.0f); glVertex3i(  posX, posY + imageHeight,-100);
		  glTexCoord2f(0.0f,0.0f); glVertex3i(  posX, posY,-100);
		  glTexCoord2f(1.0f,0.0f); glVertex3i(posX + imageWidth, posY,-100);
		  glTexCoord2f(1.0f,1.0f); glVertex3i(posX + imageWidth, posY+imageHeight,-100);
		 glEnd();
	}

	void OpenGL::SetWindowTitle(std::string title)
	{
		glfwSetWindowTitle(title.c_str());
	}

	void OpenGL::Callback(GLCALLBACK functionType, void (*function)(int, int))
	{
		if(functionType == WINDOWCLOSE)
		{
			cgl::Error("Call the overloaded OpenGL::Callback function that takes a 'int function(void)'.");
		}
		if(functionType == KEYBOARD)
		{
			glfwSetKeyCallback(function);
		}
		if(functionType == MOUSEBUTTON)
		{
			glfwSetMouseButtonCallback(function);
		}
	}


	void OpenGL::EnableVerticalSync(bool value)
	{
		if(value == true)
		{
			glfwSwapInterval(1);
		}
		else
		{
			glfwSwapInterval(0);
		}
	}

	void OpenGL::EnableFog(bool value)
	{
		if(value == true)
		{
			glfwEnable(GL_FOG);
		}
		else
		{
			glfwDisable(GL_FOG);
		}
	}

	void OpenGL::Callback(GLCALLBACK functionType, int (*function)(void))
	{
		if(functionType == WINDOWCLOSE)
		{
			glfwSetWindowCloseCallback(function);
		}
		else
		{
			cgl::Error("Call the overloaded OpenGL::Callback function that takes 'void function(int, int)'.");
		}
	}


	void OpenGL::Enable(int token)
	{
		glfwEnable(token);
	}
	void OpenGL::Disable(int token)
	{
		glfwDisable(token);
	}
	void OpenGL::Exit()
	{
		glFlush();
		glfwTerminate();
		glfwCloseWindow();
	}
	void OpenGL::StartDraw()
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);			// Clear The Screen And The Depth Buffer
		glLoadIdentity();											// Reset The Modelview Matrix
	}
	void OpenGL::Translatef(float x, float y, float z)
	{
		glTranslatef(x, y, z);
	}
	void OpenGL::EndDraw()
	{
		glfwSwapBuffers();
	}
}