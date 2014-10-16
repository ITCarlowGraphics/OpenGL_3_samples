#version 330

layout (location = 0) in vec3 position; //first input attribute (index 0)

uniform float angle;
uniform vec3 translate;

void main()
{
	
	float x=position.x*cos(angle)+position.z*sin(angle) + translate.x;
	float y=position.y + translate.y;
	float z=position.x*-sin(angle)+position.z*cos(angle)  + translate.z;
	

    gl_Position = vec4(x,y,z, 1.0);
	
}
