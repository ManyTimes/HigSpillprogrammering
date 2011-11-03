#include "../Header/boundingbox.h"

namespace cgl
{
	BoundingBox::BoundingBox()
	{
	}

	BoundingBox::BoundingBox( int x, int y, int z, int height, int width, int length )
	{
		boxHeight = height;
		boxWidth = width;
		boxLength = length;
		this->Update( x, y, z );
	}

	void BoundingBox::Update( int x, int y, int z)
	{
		/* Calculate min and max coordinates */
		min.x = x;
		min.y = y;
		min.z = z;
		max.x = x + boxWidth;
		max.y = y + boxHeight;	// y is up
		max.z = z + boxLength;
	}
	void BoundingBox::Update( Vertex3i position )
	{
		this->Update( position.x, position.y, position.z );
	}
	Vertex3i BoundingBox::GetMin()
	{
		return min;
	}
	Vertex3i BoundingBox::GetMax()
	{
		return max;
	}
	void BoundingBox::Corners2D( Vertex3i* corners )
	{
		/* Clockwise ABCD (A is in the top left corner) */
		(*corners) = min;
		corners++;
		(*corners).x = max.x;						(*corners).z = min.z;		// y is up
		corners++;
		(*corners) = max;
		corners++;
		(*corners).x = min.x;						(*corners).z = max.z;

		//Vertex3i corners[BOX_2D];	
		///* Clockwise ABCD (A is in the top left corner) */
		//corners[0] = min;
		//corners[1].x = max.x;						corners[1].z = min.z;		// y is up
		//corners[2] = max;
		//corners[3].x = min.x;						corners[3].z = max.z;
		//return corners;
	}

}