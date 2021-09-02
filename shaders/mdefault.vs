#version 300 es 

uniform mat4 modelMatrix; 
uniform mat4 projectionMatrix;  
layout (location = 0) in vec3 vposition;  
out mediump vec3 fcolor; 

void main() 
{ 
    fcolor = vec3(1.0, 0.0, 0.0); 
    gl_Position = vec4(vposition.x, vposition.y, vposition.z, 1.0); //projectionMatrix * modelViewMatrix * vposition; 
}
