#version 330

layout (location = 0) in vec3 position; //first input attribute (index 0)

uniform float angle;
uniform vec3 translate;
uniform float viewplane;

void main()
{
	vec3 pos;
	pos.x=position.x*cos(angle)+position.z*sin(angle);
	pos.y=position.y;
	pos.z=position.x*-sin(angle)+position.z*cos(angle);
	
	pos+=translate;


	//apply perspective projection

	vec3 projected=pos;
	projected*=(viewplane/pos.z);

    gl_Position = vec4(projected, 1);
	
}
