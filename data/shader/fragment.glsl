#version 430 

uniform sampler2D bling; 
uniform sampler2D tex2;

in vec2 tex_coord; 

out vec4 frag_color;

void main()
{
	// Le code à mettre en fin de compte
    frag_color = texture(bling,tex_coord);
}
