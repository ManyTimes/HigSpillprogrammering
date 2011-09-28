#ifndef _COMMON_H
#define _COMMON_H
#include "camera.h"

// Enums
enum KEYS{
	KEY_FORWARD,
	KEY_BACK,
	KEY_RIGHT,
	KEY_LEFT,
	KEY_UP,
	KEY_DOWN,
	KEY_PLUS,
	KEY_MINUS,
	KEY_MAX
};


// main.cpp
extern bool Running;
extern Camera camera;

// glfw_callbacks.cpp
extern bool keys[KEY_MAX];				// Keys

// world.cpp
#define MAX_LIGHTS 1

#endif