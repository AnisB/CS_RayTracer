#version 410 core

uniform sampler2D displaySource; 

in vec2 tex_coord; 

out vec4 frag_color;



void main()
{
	// Le code à mettre en fin de compte
    frag_color = texture(displaySource,tex_coord);
}
