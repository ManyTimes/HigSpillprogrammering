#ifndef _ENTITY_BASE_H
#define _ENTITY_BASE_H
#include <string.h>

enum EULER {ROLL, YAW, PITCH};

struct Entity3f {
	float x,y,z;
	float &operator[](int i) { float *p = &x; return p[i]; }
};

class Entity_base {
	Entity3f position;		// world x y z coordinates
	Entity3f angles;		// Euler angles
	Entity3f scale;			// scale
	bool queueUpdateMatrix;	// Used to update the matrix when values are potentially changed by being referenced.

protected:
	void UpdateMatrix(bool pos = true, bool angle = true, bool scale = true);
	float matrix[16];		// Matrix used to combine position angles and scale

public:
	Entity_base();
	// Position
	Entity3f GetPosition() { return position; }
	void SetPosition(float x, float y, float z) { position.x = x; position.y = y; position.z = z; UpdateMatrix(true,false,false); }
	void SetPosition(float p[3]) { position.x = p[0]; position.y = p[1]; position.z = p[2]; UpdateMatrix(true,false,false); }
	void SetPosition(Entity3f p) { position.x = p.x; position.y = p.y; position.z = p.z; UpdateMatrix(true,false,false); }
	Entity3f& GetPositionRef(){ queueUpdateMatrix = true; return position; }
	// Angles
	Entity3f GetAngles() { return angles; }
	void SetAngles(float roll, float yaw, float pitch) { angles.x = roll; angles.y = yaw; angles.z = pitch; UpdateMatrix(false,true,false); }
	void SetAngles(float p[3]) { angles.x = p[0]; angles.y = p[1]; angles.z = p[2]; UpdateMatrix(false,true,false); }
	void SetAngles(Entity3f p) { angles.x = p.x; angles.y = p.y; angles.z = p.z; UpdateMatrix(false,true,false); }
	Entity3f& GetAnglesRef(){ queueUpdateMatrix = true; return angles;}
	// Scale
	Entity3f GetScale() { return scale; }
	void SetScale(float x, float y, float z) { scale.x = x; scale.y = y; scale.z = z; UpdateMatrix(false,false,true); }
	void SetScale(float p[3]) { scale.x = p[0]; scale.y = p[1]; scale.z = p[2]; UpdateMatrix(false,false,true); }
	void SetScale(Entity3f p) { scale.x = p.x; scale.y = p.y; scale.z = p.z; UpdateMatrix(false,false,true); }
	Entity3f& GetScaleRef(){ queueUpdateMatrix = true; return scale; }
	// Matrix
	float *GetMatrix() { return matrix; }
	void SetMatrix(float m[16]) { memcpy(matrix, m, sizeof(float)*16);}
	//float& GetMatrixRef(){ return matrix[0]; }

	void Rotatef(float angle, float x, float y, float z);
	void Scalef(float x, float y, float z);
	void Translatef(float x, float y, float z);

	void CheckUpdate();

};
#endif