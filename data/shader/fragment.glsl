#version 400

uniform sampler2D displaySource; 
out vec4 frag_colour;

in vec2 tex_coord; 

void main()
{
	// Le code à mettre en fin de compte
    //frag_colour = texture(displaySource,tex_coord);

    // Le code de test intermédiaire
    vec4 tmp  = vec4(0.0,tex_coord[0],tex_coord[1],1.0);
    frag_colour = vec4(1.0,0.0,0.0,1.0)+tmp;

}