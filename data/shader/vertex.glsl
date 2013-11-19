#version 400
 
in vec3 Vertex_Pos;
in vec2 Vertex_TexCoord;

out vec2 tex_coord; 
void main()
{
	tex_coord = Vertex_TexCoord;
    gl_Position = vec4(Vertex_Pos, 1.0);
}