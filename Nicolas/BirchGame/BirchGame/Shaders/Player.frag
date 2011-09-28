uniform mat4 ModelMatrix;
uniform mat4 ViewMatrix;
uniform vec4 LightPosition;
uniform vec4 CameraPosition;

varying float diffuse;

void main(void)
{
	gl_FragColor = vec4(1.0, 1.0, 1.0, 1.0) * diffuse * 0.4 + vec4(0.6, 0.6, 0.6, 1.0);
}