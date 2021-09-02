#version 300 es

uniform mediump vec3 incolor;
//"in mediump vec3 incolor;\n"
in mediump vec3 fcolor;
out mediump vec4 FragColor;

void main() 
{
    FragColor = vec4(incolor * fcolor, 1.0);
}