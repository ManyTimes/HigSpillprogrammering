#ifndef _PROJECTILEARC_H
#define _PROJECTILEARC_H
#include "entity.h"
#include "model.h"

namespace cgl
{
	enum projectileType { ARC }; // ARC / GRAVITY

	class DECLARE ProjectileArc : public Entity
	{
	private:
		projectileType moveType;
		cgl::Vector3f velocity;
		cgl::Model* model;

	public:
		ProjectileArc::ProjectileArc(Vector3f start, Vector3f speed, projectileType type);
		ProjectileArc::ProjectileArc();
		ProjectileArc::~ProjectileArc();
		void ProjectileArc::Initialize(Vector3f start, Vector3f speed, projectileType type);
		void ProjectileArc::Move(float gravity);
		void ProjectileArc::SetModel(Model *model);
		void ProjectileArc::Draw();
	};
}
#endif