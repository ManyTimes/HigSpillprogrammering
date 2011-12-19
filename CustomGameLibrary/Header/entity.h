#ifndef _ENTITY_H
#define _ENTITY_H
#include "include.h"
#include "mathtool.h"
#include "boundingbox.h"
#include "matrix.h"

namespace cgl
{
	enum EULER {PITCH, YAW, ROLL};
	#define PI 3.1415926535897
	#define DEG2RAD(DEG) ((DEG)*((PI)/(180.0)))

	class DECLARE Entity 
	{
	private:
		int size;				//The collision size, number of smallest gridbox of space it takes (bounding box of this size, entity is positioned in the middle
		Vector3f angles;		// Euler angles
		Vector3f scales;		// Scale
		Matrix matrix;		// Matrix used to combine all above values
		bool queueUpdateMatrix;	// Used to update the matrix when values are potentially changed by being referenced.
	protected:
		void Entity::UpdateMatrix();
	public:

		int ID;
		Vertex3i positioni;
		Vertex3i oldPositioni;
		Volumef volume;
		BoundingBox boundingBox;
		Vector3f position;		// world x y z coordinates
		Vector3f viewangle;
		//********CONSTRUCTOR **********/
		Entity::Entity();
		//********DESTRUCTOR **********/
		Entity::~Entity();
		//********FUNCTIONS **********/
		int Entity::GetSize();
		void Entity::SetSize(int collisionSize);
		void Entity::SetPosition(float x, float y, float z) ;
		void Entity::SetPosition(float p[3]);
		void Entity::SetPosition(Vector3f p);
		void Entity::AddPosition(Vector3f v);
		void Entity::SetAngles(float pitch, float yaw, float roll);
		void Entity::SetAngles(float p[3]);
		void Entity::SetAngles(Vector3f p);
		void Entity::SetScale(float x, float y, float z);
		void Entity::SetScale(float p[3]);
		void Entity::SetScale(Vector3f p);
		void Entity::SetMatrix(float m[16]);
		void Entity::SetMatrix(Matrix m);
		//float& GetMatrixRef(){ return matrix[0]; }
		void Entity::Rotatef(float angle, float x, float y, float z);
		void Entity::Scalef(float x, float y, float z);
		void Entity::Translatef(float x, float y, float z);
		void Entity::CheckUpdate();
		Vector3f Entity::GetPosition();
		Vector3f& Entity::GetPositionRef();
		Vector3f Entity::GetAngles();
		Vector3f& Entity::GetAnglesRef();
		Vector3f Entity::GetScale();
		Vector3f& Entity::GetScaleRef();
		//float* Entity::GetMatrix();
		Matrix* Entity::GetMatrix();
	};
}	//End namespace

#endif	//End define
