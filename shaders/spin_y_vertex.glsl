#version 330

layout (location = 0) in vec3 position; //first input attribute (index 0)

uniform float angle;

void main()
{
	
	float x=position.x*cos(angle)+position.z*sin(angle);
	float y=position.y;
	float z=position.x*-sin(angle)+position.z*cos(angle);
	

    gl_Position = vec4(x,y,z, 1.0);
	
}
