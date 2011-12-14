#ifndef _ENTITY_H
#define _ENTITY_H
#include "include.h"
#include "mathtool.h"
#include "boundingbox.h"

namespace cgl
{
	enum EULER {ROLL, YAW, PITCH};
	#define PI 3.14159265358979323846
	#define DEG2RAD(DEG) ((DEG)*((PI)/(180.0)))

	class DECLARE Entity 
	{
	private:
		int size;				//The collision size, number of smallest gridbox of space it takes (bounding box of this size, entity is positioned in the middle
		Vector3f angles;		// Euler angles
		Vector3f scale;			// Scale
		float matrix[16];		// Matrix used to combine all above values
		bool queueUpdateMatrix;	// Used to update the matrix when values are potentially changed by being referenced.
	protected:
		void Entity::UpdateMatrix(bool pos = true, bool angle = true, bool scale = true);
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
		void Entity::SetAngles(float roll, float yaw, float pitch);
		void Entity::SetAngles(float p[3]);
		void Entity::SetAngles(Vector3f p);
		void Entity::SetScale(float x, float y, float z);
		void Entity::SetScale(float p[3]);
		void Entity::SetScale(Vector3f p);
		void Entity::SetMatrix(float m[16]);
		//float& GetMatrixRef(){ return matrix[0]; }
		void Entity::Rotatef(float angle, float x, float y, float z);
		void Entity::Scalef(float x, float y, float z);
		void Entity::Translatef(float x, float y, float z);
		void Entity::CheckUpdate();
		Vector3f& Entity::GetPositionRef();
		Vector3f Entity::GetAngles();
		Vector3f& Entity::GetAnglesRef();
		Vector3f Entity::GetScale();
		Vector3f& Entity::GetScaleRef();
		float* Entity::GetMatrix();
	};
}	//End namespace

#endif	//End define
