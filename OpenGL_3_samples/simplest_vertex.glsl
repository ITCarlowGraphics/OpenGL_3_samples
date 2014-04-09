#version 150

in vec3 position; //first input attribute (index 0)

void main()
{
    gl_Position = vec4(position, 1.0);
}