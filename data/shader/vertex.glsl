#version 430

uniform sampler2D bling; 
uniform sampler2D tex2; 
	
out vec2 tex_coord;


vec4 vertices[4] = vec4[4](vec4(-1.0, -1.0, 0.0, 1.0), vec4(1.0, -1.0, 0.0, 1.0), vec4(-1.0, 1.0, 0.0, 1.0), vec4(1.0, 1.0, 0.0, 1.0));
vec2 texCoord[4] = vec2[4](vec2(0.0, 0.0), vec2(1.0, 0.0), vec2(0.0, 1.0), vec2(1.0, 1.0));

void main()
{

	tex_coord = texCoord[gl_VertexID];
    gl_Position = vertices[gl_VertexID];
}
