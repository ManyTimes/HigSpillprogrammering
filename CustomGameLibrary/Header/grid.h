#ifndef _GRID_H
#define _GRID_H

#include "include.h"
#include <stdio.h>
#include "terrain.h"
#include "entity.h"

namespace cgl
{
	enum GridSize { FEW, SEVERAL, LOTS };

	struct GridNode
	{
	public:
		cgl::Entity* entity;			//This node's entity
		GridNode* nextNode;				//Pointing to the next node, if more exists, else points to NULL
		GridNode::GridNode(cgl::Entity* newEntityObject, GridNode* nextNode);
		GridNode::~GridNode(){};		//Empty as of v.1
	};

	class DECLARE GridBox						//A gridbox is a single square within a Grid. Its size depends on the Grid-constructor
	{
	private:
		//These are not in use, since we calculate only on the index X and Z
		cgl::Vector3f min;				//Minimum in the gridbox, uses only x-z, quadratic
		cgl::Vector3f max;				//Maximum in the gridbox, forming a square
		//Uses non of the two above, uses a boundingbox object instead
	public:
		int indexX;						//Index number within the Grid.
		int indexZ;
		GridNode* head;					//Top of chain
		GridNode* tail;					//The end of the chain
		GridBox::GridBox();
		GridBox::~GridBox();
		void GridBox::Initialize(int indexX, int indexZ);
		bool GridBox::isEmpty();
		bool GridBox::Exists(int entityID);
		void GridBox::Add(cgl::Entity* newEntity);
		bool GridBox::Remove(int entityID);
		bool GridBox::Collision(Vertex3i position);
		cgl::Entity* GridBox::Get(cgl::Vertex3i position);
	};


	class DECLARE Grid
	{
		int length;
		int width;
		int gridboxAmount;				//Together these forms a square, diving a grid into gridboxes with equal width and length
		GridBox** gridbox;
	public:
		int totalEntities;
		Grid::Grid(cgl::Terrain* terrainObject, GridSize value);
		Grid::~Grid();
		void Grid::AllocateEntity(Entity* entityObject);
		void Grid::AddEntity(cgl::Entity* entityObject);
		void Grid::RemoveEntity(cgl::Entity* entityToRemove);
		int Grid::FindWidth( int coordinateX);
		int Grid::FindHeight( int coordinateY);
		void Grid::Update();			//Call update, and the grid automatically places and sorts out which entity goes into which grid box
		int Grid::GetTotalGridBoxes();
		GridBox* Grid::FindGridBox(cgl::Entity* entityObject);
		GridBox* Grid::FindGridBox(float entityPositionX, float entityPositionZ);
	//	GridBox* Grid::FindGridBox(cgl::Entity* entityObject);
										//Should at least be called a few times per second
	};

}
#endif