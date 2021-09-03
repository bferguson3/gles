#version 120

//uniform mat4 modelMatrix; 
//uniform mat4 projectionMatrix;  
//layout (location = 0) 
//varying vec3 vposition;  
//vec3 fcolor; 

void main() 
{ 
    gl_Position = gl_Vertex;
    //fcolor = vec3(1.0, 0.0, 0.0); 
    //gl_Position = vec4(vposition.x, vposition.y, vposition.z, 1.0); //projectionMatrix * modelViewMatrix * vposition; 
    //gl_Position = vec4(1.0, 1.0, -5.0, 1.0);
}
