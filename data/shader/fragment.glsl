#version 430 core

uniform sampler2D displaySource; 

in vec2 tex_coord; 

out vec4 frag_color;



void main()
{
	/*
    // Le code de test intermédiaire
    vec4 tmp  = vec4(0.0,tex_coord[0],tex_coord[1],1.0);
    frag_colour = vec4(1.0,0.0,0.0,1.0)+tmp;
    */
	// Le code à mettre en fin de compte
    frag_color = texture(displaySource,tex_coord)* 0.5;
}
