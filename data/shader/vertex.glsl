#version 410
 
layout (std140) uniform Matrices {
    mat4 projModelViewMatrix;
    mat3 normalMatrix;
};
 
in vec3 position;
in vec3 normal;
in vec2 texCoord;
 
out VertexData {
    vec2 texCoord;
    vec3 normal;
} VertexOut;
 
void main()
{
    VertexOut.texCoord = texCoord;
    VertexOut.normal = normalize(normalMatrix * normal);    
    gl_Position = projModelViewMatrix * vec4(position, 1.0);
}