uniform sampler2D Screen_Texture;

varying vec2 tex_coord;
void main(void)
{
		gl_FragColor = texture2D(Screen_Texture,tex_coord);
}