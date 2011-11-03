#ifndef _BOUNDINGBOX_H
#define _BOUNDINGBOX_H

#include "function.h"
#include "mathtool.h"

namespace cgl
{

class BoundingBox
{
private:
	int boxHeight;
	int boxWidth;
	int boxLength;
	Vertex3i min;
	Vertex3i max;
public:	
	BoundingBox::BoundingBox();
	BoundingBox::BoundingBox( int x, int y, int z, int height, int width, int length );
	void BoundingBox::Update( int x, int y, int z );
	void BoundingBox::Update( Vertex3i position );
	Vertex3i BoundingBox::GetMin();
	Vertex3i BoundingBox::GetMax();
	void BoundingBox::Corners2D( Vertex3i* corners );
	//Vertex3i* corners3D();
};
}
#endif