#include "shader.h"

#include <fstream>
#include <string.h>

#include <GL/glew.h>
#include <Gl/glut.h>


Shader::Shader()
{
	glewInit();//#define i glew.h
	if (glewIsSupported("GL_VERSION_2_0"))
		printf("Ready for OpenGL 2.0\n");
	else {
		printf("OpenGL 2.0 not supported\n");
		exit(1);
	}
}

Shader::~Shader()
{
	glDetachShader(program, vertex);
	glDeleteShader(vertex);

	glDetachShader(program, fragment);
	glDeleteShader(fragment);

	if(geometry != 0)
	{
		glDetachShader(program, geometry);
		glDeleteShader(geometry);
	}

	glDeleteProgram(program);
}

int Shader::printOglError(char *file, int line)
{
    //
    // Returns 1 if an OpenGL error occurred, 0 otherwise.
    //
    GLenum glErr;
    int retCode = 0;

    glErr = glGetError();
    while (glErr != GL_NO_ERROR)
    {
        printf("glError in file %s @ line %d: %s\n", file, line, gluErrorString(glErr));
        retCode = 1;
        glErr = glGetError();
   }
    return retCode;
}

void Shader::printShaderInfoLog(unsigned int obj)
{
    int infologLength = 0;
    int charsWritten  = 0;
    char *infoLog;

	glGetShaderiv(obj, GL_INFO_LOG_LENGTH, &infologLength);

    if (infologLength > 0)
    {
        infoLog = new char[infologLength];
        glGetShaderInfoLog(obj, infologLength, &charsWritten, infoLog);
		printf("%s\n",infoLog);
        delete infoLog;
   }
}

void Shader::printProgramInfoLog(unsigned int obj)
{
    int infologLength = 0;
    int charsWritten = 0;
    char *infoLog;

//	glGetShaderiv(obj, GL_INFO_LOG_LENGTH, &infologLength);
	glGetProgramiv(obj, GL_INFO_LOG_LENGTH, &infologLength);

    if (infologLength > 0)
    {
        infoLog = (char *) malloc(infologLength);
//        glGetShaderInfoLog(obj, infologLength, &charsWritten, infoLog);
        glGetProgramInfoLog(obj, infologLength, &charsWritten, infoLog);
		printf("%s\n", infoLog);
        free(infoLog);
   }
}

GLuint Shader::setShader(char *sp)
{
	unsigned int nameSize = strlen(sp) + 6;
	char *vert = new char[nameSize];
	strcpy_s(vert, nameSize, sp);
	strcat_s(vert, nameSize, ".vert");

	char *geom = new char[nameSize];
	strcpy_s(geom, nameSize, sp);
	strcat_s(geom, nameSize, ".geom");

	char *frag = new char[nameSize];
	strcpy_s(frag, nameSize, sp);
	strcat_s(frag, nameSize, ".frag");

	char *vs = NULL, *gs = NULL, *fs = NULL;

//Lese kildekode :
	vs = textFileRead(vert);
	gs = textFileRead(geom);
	fs = textFileRead(frag);
	if(vs == NULL || fs == NULL)
		return 0;

//#1 : opprette shader container. Retur : handle
	vertex = glCreateShader(GL_VERTEX_SHADER);
	fragment = glCreateShader(GL_FRAGMENT_SHADER);
	if(gs != 0)
		geometry = glCreateShader(GL_GEOMETRY_SHADER_ARB);
	else geometry = 0;
//Kan ha mange shadere, bare en main for hver type. 

	delete vert;
	delete frag;
	delete geom;

	const char *vv = vs;
	const char *ff = fs;
	const char *gg = gs;
//#2 : forberede kompilering
	glShaderSource(vertex, 1, &vv, NULL);
	glShaderSource(fragment, 1, &ff, NULL);
	if(gs != 0)
		glShaderSource(geometry, 1, &gg, NULL);

	delete vs;//definert med new i textFileRead(...)
	delete fs;//definert med new i textFileRead(...)
	delete gg;//definert med new i textFileRead(...)

//#3 : kompilering
	glCompileShader(vertex);
	glCompileShader(fragment);
	if(gs != 0)
		glCompileShader(geometry);

//Nå skal shaderprogrammet klargjøres for eksekvering
	program = glCreateProgram();//#1 (kan lage mange programmer som det kan byttes mellom)
	glAttachShader(program, vertex);//#2
	glAttachShader(program, fragment);//#3
	if(gs != 0)
	{
		glAttachShader(program, geometry);
		glProgramParameteriARB(program, GL_GEOMETRY_INPUT_TYPE_ARB, GL_TRIANGLES);
		glProgramParameteriARB(program, GL_GEOMETRY_OUTPUT_TYPE_ARB, GL_TRIANGLES);

		int temp;
		glGetIntegerv(GL_MAX_GEOMETRY_OUTPUT_VERTICES_ARB, &temp);//1024
		//necessary for drawing to appear
		glProgramParameteriARB(program, GL_GEOMETRY_VERTICES_OUT_ARB, temp);
	}

	glLinkProgram(program);//#4

	printShaderInfoLog(vertex);
	printShaderInfoLog(fragment);
	if(gs != 0)
		printShaderInfoLog(geometry);

	printProgramInfoLog(program);
	glUseProgram(program);//#5
	return program;
}

char *Shader::textFileRead(char *fn)
{
	std::fstream fp(fn, std::ios::in | std::ios::out | std::ios::binary);
	char *content = 0;
	int count = 0;
	if (fp.is_open()) {
		fp.seekg(0, std::ios::end);
		count = fp.tellg();
		content = new char[count + 1];
		fp.seekg(0, std::ios::beg);
		fp.read(content, count);
		content[count] = '\0';
		fp.close();
	}
	return content;
}

