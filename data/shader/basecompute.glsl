#version 430

uniform sampler2D displaySource; 

layout(rgba8) uniform image2D renderCanvas;

layout (local_size_x = 16, local_size_y = 16) in;

int ct = 10;

void main() 
{
     ivec2 storePos = ivec2(gl_GlobalInvocationID.xy);
     imageStore(renderCanvas, storePos, vec4(0.3, 0.4, 1.0, 1.0));
 }

