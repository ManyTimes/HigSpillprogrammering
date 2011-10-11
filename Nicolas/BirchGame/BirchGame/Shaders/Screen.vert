#version 120
const vec2 ScreenCoordinates[4] =
	vec2[](
        vec2( -1.0, -1.0),
        vec2( -1.0,  1.0),
        vec2(  1.0,  1.0),
        vec2(  1.0, -1.0)
    );
    
const vec2 ScreenTexCoordinates[4] =
    vec2[](
        vec2(0.0, 0.0),
        vec2(0.0, 1.0),
        vec2(1.0, 1.0),
        vec2(1.0, 0.0)
    );
    
in int gl_VertexID;
varying vec2 tex_coord;
void main(void)
{
	tex_coord = ScreenTexCoordinates[gl_VertexID];
	gl_Position = vec4(ScreenCoordinates[gl_VertexID], 0.0, 1.0);
}