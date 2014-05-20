#version 330

smooth in vec4 fragColour;

out vec4 outColour;

void main()
{
    outColour = fragColour;
	//outColour=vec4(1,1,0,1);
}