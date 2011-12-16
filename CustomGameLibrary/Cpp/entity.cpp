#include "../Header/entity.h"
namespace cgl
{
	/*********CONSTRUCTOR ******************/
	Entity::Entity()
	{
		this->ID = -1;
		scales.x = scales.y = scales.z = 1.0f;
		/*matrix[0] = 1.0f;								// Replaced with Matrix class, loads identity matrix automatically.
		matrix[1] = matrix[2] = matrix[3] = 0.0f;
		matrix[5] = 1.0f;
		matrix[4] = matrix[6] = matrix[7] = 0.0f;
		matrix[10] = 1.0f;
		matrix[8] = matrix[9] = matrix[11] = 0.0f;
		matrix[15] = 1.0f;
		matrix[12] = matrix[13] = matrix[14] = 0.0f;*/
	}
	Entity::~Entity()
	{
	}

	/*********FUNCTIONS******************/
	void Entity::UpdateMatrix(bool pos, bool angle, bool scale)
	{
		// Convert to radians for cos and sin functions
		if(angle)
		{
			Vector3f r_angles;
			r_angles.x = DEG2RAD(angles.x);
			r_angles.y = DEG2RAD(angles.y);
			r_angles.z = DEG2RAD(angles.z);

			float sa = sin(r_angles.z);
			float ca = cos(r_angles.z);
			float sb = sin(r_angles.x);
			float cb = cos(r_angles.x);
			float sh = sin(r_angles.y);
			float ch = cos(r_angles.y);

			matrix[0] = ch*ca;
			matrix[1] = sa;
			matrix[2] = -sh*ca;

			matrix[4] = -ch*sa*cb + sh*sb;
			matrix[5] = ca*cb;
			matrix[6] = sh*sa*cb + ch*sb;

			matrix[8] = ch*sa*sb + sh*cb;
			matrix[9] = -ca*sb;
			matrix[10] = -sh*sa*sb + ch*cb;

			matrix[3] = 0;
			matrix[7] = 0;
			matrix[11] = 0;
		}

		if(pos)
		{
			matrix[12] = position.x;//-Pos->dot(*Right);
			matrix[13] = position.y;//-Pos->dot(*Up);
			matrix[14] = position.z;//-Pos->dot(*Look);
		}

		if(angle || scale)
		{
			Matrix m_scale;
			m_scale[0] = m_scale[5] = m_scale[10] = scales.x;
			this->SetMatrix((m_scale * *this->GetMatrix()));
		}
		
	//	matrix[3] = 0;//Pos->x; 
	//	matrix[7] = 0;//Pos->y;
	//	matrix[11] = 0;//Pos->z;
	//	matrix[15] = 1.0;
	}

	void Entity::CheckUpdate()
	{ 
		if(queueUpdateMatrix)
		{ 
			UpdateMatrix(); 
			queueUpdateMatrix = false; 
		} 
	}

	/*void Entity::Draw()
	{
		// Draw all models, might have multiple all together.
		// For now, just one model.
		model->Draw(GetMatrix());		// Pass on the entities position, angles and scale.
	}*/

	/*void Entity::Draw(float m[16])
	{
		float m2[16];

		std::cout << "Player::Draw(float m[16]) not implemented";
	//	m2 = matrix*m; // Combine the matrices
	//	model->Draw(m2);
		//model->Draw(GetMatrix());
	}*/

	void Entity::SetSize(int collisionSize)
	{
		this->size = collisionSize;
	}

	void Entity::Rotatef(float angle, float x, float y, float z)
	{
		std::cout << "Entity::Rotatef used without being created yet.\n";
	}
	void Entity::Scalef(float x, float y, float z)
	{
		std::cout << "Entity::Scalef used without being created yet.\n";
	}
	void Entity::Translatef(float x, float y, float z)
	{
		std::cout << "Entity::Translatef used without being created yet.\n";
	}

	void Entity::SetPosition(float x, float y, float z)
	{ 
		position.x = x;
		position.y = y; 
		position.z = z; 
		UpdateMatrix(true,false,false); 
	}

	void Entity::SetPosition(float p[3]) 
	{ 
		position.x = p[0]; 
		position.y = p[1]; 
		position.z = p[2]; 
		UpdateMatrix(true,false,false); 
	}

	void Entity::SetPosition(Vector3f p) 
	{ 
		position.x = p.x; 
		position.y = p.y; 
		position.z = p.z; 
		UpdateMatrix(true,false,false); 
	}

	void Entity::SetAngles(float roll, float yaw, float pitch) 
	{ 
		angles.x = roll; 
		angles.y = yaw; 
		angles.z = pitch;
		UpdateMatrix(false,true,false); 
	}

	void Entity::SetAngles(float p[3]) 
	{ 
		angles.x = p[0]; 
		angles.y = p[1]; 
		angles.z = p[2]; 
		UpdateMatrix(false,true,false); 
	}

	void Entity::SetAngles(Vector3f p) 
	{ 
		angles.x = p.x; 
		angles.y = p.y; 
		angles.z = p.z; 
		UpdateMatrix(false,true,false); 
	}
	void Entity::SetScale(float x, float y, float z) 
	{ 
		scales.x = x; 
		scales.y = y; 
		scales.z = z; 
		UpdateMatrix(false,false,true); 
	}

	void Entity::SetScale(float p[3]) 
	{ 
		scales.x = p[0]; 
		scales.y = p[1];
		scales.z = p[2];
		UpdateMatrix(false,false,true); 
	}

	void Entity::SetScale(Vector3f p) 
	{ 
		scales.x = p.x; 
		scales.y = p.y; 
		scales.z = p.z; 
		UpdateMatrix(false,false,true); 
	}

	void Entity::SetMatrix(float m[16]) 
	{ 
		matrix.SetMatrixf(m);
	}

	void Entity::SetMatrix(Matrix m) 
	{ 
		matrix.SetMatrixf(m.GetMatrixf());
	}

	Vector3f Entity::GetPosition()
	{
		return position;
	}

	Vector3f& Entity::GetPositionRef()
	{ 
		queueUpdateMatrix = true; 
		return position; 
	}

	Vector3f Entity::GetAngles() 
	{ 
		return angles;
	}

	Vector3f& Entity::GetAnglesRef()
	{ 
		queueUpdateMatrix = true; 
		return angles;
	}
	Vector3f Entity::GetScale()
	{ 
		return scales; 
	}

	Vector3f& Entity::GetScaleRef()
	{ 
		queueUpdateMatrix = true; 
		return scales; 
	}

	int Entity::GetSize()
	{
		return this->size;
	}

	//float* Entity::GetMatrix()
	//{
	//	return matrix;
	//}

	Matrix* Entity::GetMatrix()
	{
		return &matrix;
	}
}