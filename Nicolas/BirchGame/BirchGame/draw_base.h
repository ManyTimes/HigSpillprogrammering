#ifndef _DRAW_BASE_H
#define _DRAW_BASE_H
#include <iostream>

class Draw_base{

public:
	virtual void Draw() { std::cout << "No Draw implemented\n"; }
};

#endif