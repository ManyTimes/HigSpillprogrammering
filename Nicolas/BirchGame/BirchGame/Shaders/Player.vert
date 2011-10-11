uniform mat4 ModelMatrix;
uniform mat4 ViewMatrix;
uniform mat4 t_ModelMatrix;	// Transposed
uniform mat4 t_ViewMatrix;	// Transposed
uniform vec4 LightPosition;
uniform vec4 CameraPosition;

varying float diffuse;

in int gl_VertexID;
void main(void)
{
	vec4 ecPosition = ModelMatrix * gl_Vertex;
	vec3 lightDir = normalize(vec3(LightPosition - ecPosition));
	vec3 normal = normalize(ModelMatrix * vec4(gl_Normal,0.0)).xyz; // vec3(t_ViewMatrix * t_ModelMatrix * vec4(gl_Normal,0)); // <-- Seems to be wrong using gl_NormalMatrix for now.

	diffuse = max(dot(lightDir, normal), 0.0);
	
	gl_Position = gl_ProjectionMatrix * ViewMatrix * ModelMatrix * gl_Vertex;//ftransform();//
}