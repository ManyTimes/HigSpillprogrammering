#include "entity_base.h"
#include <iostream>
#include "math.h"

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
#define PI 3.14159265358979323846
#define DEG2RAD(DEG) ((DEG)*((PI)/(180.0)))
void Entity_base::UpdateMatrix(bool pos, bool angle, bool scale)
{
	// Convert to radians for cos and sin functions
	if(angle)
	{
		Entity3f r_angles;
		r_angles.x = DEG2RAD(angles.x);
		r_angles.y = DEG2RAD(angles.y);
		r_angles.z = DEG2RAD(angles.z);

	//	matrix[0] = Right->x;
	//	matrix[1] = Right->y;
	//	matrix[2] = Right->z;
		matrix[0] = cos(r_angles.y) * cos(r_angles.z);
		matrix[1] = -cos(r_angles.y) * sin(r_angles.z);
		matrix[2] = sin(r_angles.y);
	//	matrix[4] = Up->x;
	//	matrix[5] = Up->y;
	//	matrix[6] = Up->z;
		matrix[4] = cos(r_angles.x) * sin(r_angles.z) + sin(r_angles.x) * sin(r_angles.y) * cos(r_angles.z);
		matrix[5] = cos(r_angles.x) * cos(r_angles.z) - sin(r_angles.x) * sin(r_angles.y) * cos(r_angles.z);
		matrix[6] = -sin(r_angles.x) * cos(r_angles.y);
	//	matrix[8] = Look->x; 
	//	matrix[9] = Look->y;
	//	matrix[10] = Look->z;
		matrix[8] = sin(r_angles.x) * sin(r_angles.z) - cos(r_angles.x) * sin(r_angles.y) * cos(r_angles.z);
		matrix[9] = sin(r_angles.x) * cos(r_angles.z) + cos(r_angles.x) * sin(r_angles.y) * sin(r_angles.z);
		matrix[10] = cos(r_angles.x) * cos(r_angles.y);
	}

	if(pos)
	{
		matrix[12] = position.x;//-Pos->dot(*Right);
		matrix[13] = position.y;//-Pos->dot(*Up);
		matrix[14] = position.z;//-Pos->dot(*Look);
	}

	if(scale)
	{
	}
	
//	matrix[3] = 0;//Pos->x; 
//	matrix[7] = 0;//Pos->y;
//	matrix[11] = 0;//Pos->z;
//	matrix[15] = 1.0;
}

void Entity_base::CheckUpdate()
{ 
	if(queueUpdateMatrix)
	{ 
		UpdateMatrix(); 
		queueUpdateMatrix = false; 
	} 
}

void Entity_base::Rotatef(float angle, float x, float y, float z)
{
	std::cout << "Entity_base::Rotatef used without being created yet.\n";
}
void Entity_base::Scalef(float x, float y, float z)
{
	std::cout << "Entity_base::Scalef used without being created yet.\n";
}
void Entity_base::Translatef(float x, float y, float z)
{
	std::cout << "Entity_base::Translatef used without being created yet.\n";
}