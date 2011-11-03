#include "../Header/grid.h"

namespace cgl
{
	GridNode::GridNode(cgl::Entity* newEntityObject, GridNode* nextNode)
	{
		this->entity = newEntityObject;
		this->nextNode = nextNode;
	}

	GridBox::GridBox()
	{
	}


	void GridBox::Initialize(int indexX, int indexZ)	//Units within a GridBox, which again is within the Grid
	{													//Initilizes with null and both equals tail
		this->tail = new GridNode(NULL, this->tail);	//Sets both of them to tail
		this->head = new GridNode(NULL, this->tail);
		this->indexX = indexX;
		this->indexZ = indexZ;
	}

	GridBox::~GridBox()
	{
		delete this->head;
		delete this->tail;
	}

	bool GridBox::isEmpty()
	{
		if(this->head->nextNode == this->tail)
		{
			return true;
		}
		return false;
	}

	bool GridBox::Exists(int entityID)					//Is the entity with this ID within this particular Unit list (within this GridBox
	{
		GridNode* tempNode = this->head->nextNode;
		while(tempNode != this->tail)					//Tail is the last node, which is empty
		{
			if(tempNode->entity->ID == entityID)
			{
				return true;
			}
		}
		return false;
	}

	void GridBox::Add(cgl::Entity* newEntityObject)
	{													//Adds a new entity to the "entity list", adds at the top, pushing the others "down"
		this->head->nextNode = new GridNode(newEntityObject, this->head->nextNode);	
	}

	bool GridBox::Remove(int entityID)
	{
		GridNode* previousNode;
		GridNode* thisNode = this->head->nextNode;		//First node
		while(thisNode != tail)							//Not at the end
		{											
			if(thisNode->entity->ID == entityID)		//We are within the node that should be removed
			{									
				if(previousNode)						//PreviousNode has been set, not the top node, so we need to change the pointers above "thisNode" to point to nextNode
				{					
					previousNode->nextNode = thisNode->nextNode;//Previous node does not point to the node we are in any more, so we can delete it.
				}
				delete thisNode;
				return true;
			}
			previousNode = thisNode;					//Store the previous node, when moving down the list
			thisNode = thisNode->nextNode;
		}
		return false;
	}

	cgl::Entity* GridBox::Get(cgl::Vertex3i position)
	{
		GridNode* tempNode;
		tempNode = head->nextNode;
		while( tempNode != this->tail )					//Checking on the x-z axis, plane
		{
			if( tempNode->entity->position.x == position.x && 
					tempNode->entity->position.z == position.z )
			{
				return tempNode->entity;
			}
			tempNode = tempNode->nextNode;
		}
		return NULL;
	}

	bool GridBox::Collision(Vertex3i position)
	{
		GridNode* tempNode = this->head->nextNode;
		while(tempNode != tail)
		{
			if(true)
			{
				return true;
			}
			tempNode = tempNode->nextNode;
		}
		return false;
	}

	Grid::Grid(cgl::Terrain* terrainObject, GridSize value)
	{
		this->totalEntities = 0;
		int amount = 8;
		if(value == SEVERAL)
		{
			amount = 16;
		}
		if(value == LOTS)
		{
			amount = 32;
		}
		this->length = terrainObject->GetLength();
		this->width = terrainObject->GetWidth();
		this->gridboxAmount = amount;
		this->gridbox = new GridBox*[this->gridboxAmount];		//Creates gridboxes X-vise
		for(int i = 0; i < this->gridboxAmount; i++)			//Creates gridboxes Y-vise for each X-vise gridbox, forming a square of boxes
		{		
			this->gridbox[i] = new GridBox[this->gridboxAmount];
		}
		for(int i = 0; i < this->gridboxAmount; i++)
		{
			for(int ii = 0; ii < this->gridboxAmount; ii++)
			{
				this->gridbox[i][ii].Initialize(i,ii);
			}
		}
	}

	Grid::~Grid()
	{
		for(int i = 0; i < this->gridboxAmount; i++)
		{
			delete this->gridbox[i];
		}
		delete this->gridbox;
	}

	int Grid::FindWidth( int coordinateX)
	{
		return ( ( (float)coordinateX / this->width ) * this->gridboxAmount );
	}
	int Grid::FindHeight( int coordinateY )
	{
		return ( ( (float)coordinateY / this->length ) * this->gridboxAmount );
	}

	//Adds to at least one gridbox, might be several depending on the bounding box size, size of the entity.
	void Grid::AllocateEntity(Entity* entityObject)
	{
		cgl::Vertex3i box2D[4];		//ABCD coordinates
		entityObject->boundingBox.Corners2D(box2D);
		int x, z;
		for(int i = 0; i < 4; i++)
		{
			x = this->FindWidth(box2D[i].x);
			z = this->FindWidth(box2D[i].z);
			if(!this->gridbox[x][z].Exists(entityObject->ID))
			{
				gridbox[x][z].Add(entityObject);
			}
		}
	}

	//Adds an entity to the grid, and places it into the right gridbox
	void Grid::AddEntity(cgl::Entity* entityObject)
	{
		int x = ((entityObject->position.x / this->width)* this->gridboxAmount);
		int z = ((entityObject->position.z / this->length)* this->gridboxAmount);
		this->gridbox[x][z].Add(entityObject);
		this->totalEntities++;
	}

	//Removes an entity from the grid, if the entity is not within the grid, it does nothing
	//Removes onl if an entity has been added through function "add entity", not through "AllocateEntity"
	void Grid::RemoveEntity(cgl::Entity* entityToRemove)
	{
		int x = ((entityToRemove->position.x / this->width)* this->gridboxAmount);
		int z = ((entityToRemove->position.z / this->length)* this->gridboxAmount);
		if(x < this->gridboxAmount && z < this->gridboxAmount && x > -1 && z > -1)
		{
			if(this->gridbox[x][z].Remove(entityToRemove->ID) == true)
			{
				this->totalEntities--;
			}
		}
	}

	//Returns the gridbox object an entity is within, if not in any gridbox it returns NULL
	GridBox* Grid::FindGridBox(cgl::Entity* entityObject)
	{
		int x = (entityObject->position.x/this->width) * this->gridboxAmount;
		int z = (entityObject->position.z/this->length) * this->gridboxAmount;
		GridBox* tempBox = &this->gridbox[x][z];
		if(tempBox->Exists(entityObject->ID) == true)
		{
			return tempBox;
		}
		return NULL;
	}

	//Returns the gridbox object that contains the position, if no such box exists, returns NULL
	GridBox* Grid::FindGridBox(float entityPositionX, float entityPositionZ)
	{
		int x = (entityPositionX/this->width) * this->gridboxAmount;
		int z = (entityPositionZ/this->length) * this->gridboxAmount;
		if(x < this->gridboxAmount && z < this->gridboxAmount)		//The position needs to be within a real gridbox
		{
			return &this->gridbox[x][z];
		}
		return NULL;
	}

	//Gets the total amount of gridboxes within the grid (X * Z vise)
	int Grid::GetTotalGridBoxes()
	{
		return (this->gridboxAmount * this->gridboxAmount);
	}

	//Optimize by removing the "thisNode", can simply just use gridbox[i][ii]...
	//But it is shorter to write, cleaner, readability...Quite Neat!
	void Grid::Update()
	{
		GridNode* thisNode;
		int x, z;
		x = z = 0;
		for(int i = 0; i < this->gridboxAmount; i++)
		{
			for(int ii = 0; ii < this->gridboxAmount; ii++)
			{
				thisNode = this->gridbox[i][ii].head;							//Not reached the tail, move along, checking its position
				while(thisNode != this->gridbox[i][ii].tail)
				{
					x = (thisNode->entity->position.x / this->width) * this->gridboxAmount;
					z = (thisNode->entity->position.z / this->length) * this->gridboxAmount;
					if(this->gridbox[i][ii].indexX != x)						//X is not correct, unit has moved
					{
						this->gridbox[x][z].Add(thisNode->entity);				//Add to new GridBox
						this->gridbox[i][ii].Remove(thisNode->entity->ID);		//Remove from old gridbox
					}
					else
					{
						if(this->gridbox[i][ii].indexZ != z)					//Z is not correct, unit has moved
						{
							this->gridbox[x][z].Add(thisNode->entity);			//Add to new GridBox
							this->gridbox[i][ii].Remove(thisNode->entity->ID);	//Remove from old gridbox
						}
					}
				}
			}
		}
	}
}

