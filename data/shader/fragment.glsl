#version 410 core

uniform sampler2D displaySource; 

in vec2 tex_coord; 

out vec4 frag_color;

void main()
{
	// Le code à mettre en fin de compte
	vec2 real_tex = vec2((tex_coord.x+1.0)/2.0, (tex_coord.y+1.0)/2.0);
    frag_color = texture(displaySource,real_tex);
}
