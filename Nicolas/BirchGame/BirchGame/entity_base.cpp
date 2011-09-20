#include "entity_base.h"

Entity_base::Entity_base()
{
	matrix[0] = 1.0f;
	matrix[1] = matrix[2] = matrix[3] = 0.0f;
	matrix[5] = 1.0f;
	matrix[4] = matrix[6] = matrix[7] = 0.0f;
	matrix[10] = 1.0f;
	matrix[8] = matrix[9] = matrix[11] = 0.0f;
	matrix[15] = 1.0f;
	matrix[12] = matrix[13] = matrix[14] = 0.0f;
}

void Entity_base::UpdateMatrix()
{
//	matrix[0] = Right->x; 
//	matrix[1] = Right->y;
//	matrix[2] = Right->z;
	matrix[12] = position.x;//-Pos->dot(*Right);
//	matrix[4] = Up->x;
//	matrix[5] = Up->y;
//	matrix[6] = Up->z;
	matrix[13] = position.y;//-Pos->dot(*Up);
//	matrix[8] = Look->x; 
//	matrix[9] = Look->y;
//	matrix[10] = Look->z;
	matrix[14] = position.z;//-Pos->dot(*Look);
//	matrix[3] = 0;//Pos->x; 
//	matrix[7] = 0;//Pos->y;
//	matrix[11] = 0;//Pos->z;
//	matrix[15] = 1.0;
}