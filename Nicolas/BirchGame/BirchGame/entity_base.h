#ifndef _ENTITY_BASE_H
#define _ENTITY_BASE_H
#include <string.h>

struct Entity3f {
	float x,y,z;
	float &operator[](int i) { float *p = &x; return p[i]; }
};

class Entity_base {
	Entity3f position;		// world x y z coordinates
	Entity3f angles;		// Euler angles
	Entity3f scale;			// scale
	float matrix[16];		// Matrix used to combine all above values

	void UpdateMatrix();

public:
	Entity_base();
	// Position
	Entity3f GetPosition() { return position; }
	void SetPosition(float x, float y, float z) { position.x = x; position.y = y; position.z = z; UpdateMatrix();}
	void SetPosition(float p[3]) { position.x = p[0]; position.y = p[1]; position.z = p[2]; UpdateMatrix();}
	void SetPosition(Entity3f p) { position.x = p.x; position.y = p.y; position.z = p.z; UpdateMatrix();}
	Entity3f& GetPositionRef(){ return position; }
	// Angles
	Entity3f GetAngles() { return angles; }
	void SetAngles(float yaw, float pitch, float roll) { angles.x = yaw; angles.y = pitch; angles.z = roll; }
	void SetAngles(float p[3]) { angles.x = p[0]; angles.y = p[1]; angles.z = p[2]; }
	void SetAngles(Entity3f p) { angles.x = p.x; angles.y = p.y; angles.z = p.z; }
	Entity3f& GetAnglesRef(){ return angles; }
	// Scale
	Entity3f GetScale() { return scale; }
	void SetScale(float x, float y, float z) { scale.x = x; scale.y = y; scale.z = z; }
	void SetScale(float p[3]) { scale.x = p[0]; scale.y = p[1]; scale.z = p[2]; }
	void SetScale(Entity3f p) { scale.x = p.x; scale.y = p.y; scale.z = p.z; }
	Entity3f& GetScaleRef(){ return scale; }
	// Matrix
	float *GetMatrix() { return matrix; }
	void SetMatrix(float m[16]) { memcpy(matrix, m, sizeof(float)*16);}
	//float& GetMatrixRef(){ return matrix[0]; }

};
#endif