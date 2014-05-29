#version 330

layout (location = 0) in vec3 position; //first input attribute (index 0)

uniform float angle;

void main()
{
	
	float x=position.x*cos(angle)+position.y*-sin(angle);
	float y=position.x*sin(angle)+position.y*cos(angle);

	

    gl_Position = vec4(x,y,position.z, 1.0);
	
}
