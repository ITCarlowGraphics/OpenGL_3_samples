#version 330

layout (location = 0) in vec3 position; //first input attribute (index 0)
layout (location = 1) in vec3 colour; //second input attribute (index 1)


uniform vec2 move;

smooth out vec4 fragColour;

void main()
{
	fragColour=vec4(colour,1.0);

	vec4 pos=vec4(position, 1.0);

	pos.x+=move.x;
	pos.y+=move.y;

    gl_Position = pos;
	
}
