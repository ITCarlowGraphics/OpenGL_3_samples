// SimpleColouredPrimitives_VBO.cpp : Defines the entry point for the console application.
//

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include "stdafx.h"

#pragma comment(lib,"sfml-graphics-d.lib")
#pragma comment(lib,"sfml-audio-d.lib")
#pragma comment(lib,"sfml-system-d.lib")
#pragma comment(lib,"sfml-window-d.lib")
#pragma comment(lib,"sfml-network-d.lib")
#pragma comment(lib,"opengl32.lib")
#pragma comment(lib,"glu32.lib")
#define  GLEW_STATIC 
#pragma comment(lib,"glew32s.lib")
#include <GL/glew.h>
#include <SFML/Graphics.hpp>



void fatalError(const char* s){
		perror(s);
		system("pause");
		exit(-1);
}

void initialiseOpenGL(){
	
	//initialize GLEW so we can access the modern OpenGL (1.4+) features
	GLenum err=glewInit();
	if(GLEW_OK!=err){
		fatalError((const char *)glewGetErrorString(err));
		
	}

    // set up defaults for OpengGL
    glClearDepth(1.f);//far depth for HSR
    glClearColor(0.1f, 0.4f, 0.1f, 1.f); //initial background color
	glEnable(GL_DEPTH_TEST); //turn on depth testing, Enable Z-buffer read and write

}

///////////////////////////////////////////////////////////
/// Entry point of application
////////////////////////////////////////////////////////////
int main()
{
	float width=800,height=600;
	
	//Create the main window and an OpenGL4.0 rendering context (compatibilty flag set)
	sf::RenderWindow window(sf::VideoMode(width, height, 32), "SFML OpenGL Demo");
	sf::ContextSettings cs=window.getSettings();
	printf("Created an OpenGL %d.%d context [version 3.3 or greater is required for these samples]\n",cs.majorVersion,cs.minorVersion);

	
	initialiseOpenGL(); //initialise various OpenGl Stuff (same for every program)


	//create a VBO for positions AND colours of object_1, an array of x,y,z position of 3 vertices, followed by rgb of each vertex
	const GLfloat vertexPositions1[] = {
		0.5, 0.5, 0,
		0.5, -0.5, 0,
		-0.5, -0.5, 0,
		
		1.0f,0.0f,0.0f, //red
		0.0f,1.0f,0.0f, //green
		1.0f,1.0f,0.0f, //yellow
	};

	GLuint positionsBufferObject1; //integer variable to store the VBO handle
	glGenBuffers(1, &positionsBufferObject1); //generate a new VBO, store the handle in the handle variable
    glBindBuffer(GL_ARRAY_BUFFER, positionsBufferObject1); //make positionsBufferObject the 'current' VBO for next few commands

    glBufferData(GL_ARRAY_BUFFER, 3*6*sizeof(GLfloat), vertexPositions1, GL_STATIC_DRAW);// push the vextex data into the VBO in video memory




	//set up shader
	sf::Shader shader; //create a shader object
	if(!shader.loadFromFile("..//shaders//move_vertex.glsl","..//shaders//coloured_fragment.glsl")){
		fatalError("Problem loading glsl files");
	}//load shader code from these text files
	sf::Shader::bind(&shader);//
	glEnableVertexAttribArray(0); //open up the 0th attribute to receive data, in this case this is the 'position' attribute in the shader
	glEnableVertexAttribArray(1); //open up the 1th attribute to receive data, in this case this is the 'colour' attribute in the shader

	sf::Vector2f posVec(0,0);

	// this is our game loop
	while (window.isOpen())
    {
        // Process events
        sf::Event event;
		
        while (window.pollEvent(event)) //process all events
        {
			
            // Close window : exit
            if (event.type == sf::Event::Closed)
                window.close();

            // Escape key : exit
            if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Escape))
                window.close();

            // Resize event : adjust viewport
            if (event.type == sf::Event::Resized){
                glViewport(0, 0, event.size.width,event.size.height); //tell opengl the window size has changed
				
			}
				
			/*
		    if ((event.type == sf::Event::KeyPressed) && (event.Key.Code == sf::Key::A)){
				//do something
			}
			*/
		}


        //start rendering our scene
		
		//update the position
		posVec.x+=0.0001;
		posVec.y-=0.0001;

		
		shader.setParameter("move",posVec); //send the new position to the shader (in the shader this variable is called "move")

        //Clear color and depth buffer
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


		glBindBuffer(GL_ARRAY_BUFFER, positionsBufferObject1); //make positionsBufferObject the 'current' VBO for next  command
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0); // tell openGL that vertex 'position' attributes are in current  VBO
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void*) (3*3*sizeof(GLfloat))); // tell openGL that vertex 'colour' attributes are in current  VBO
		
		glDrawArrays(GL_TRIANGLES, 0, 3);	// draw  object (in positionsBufferObject1) (use 3-vertices)





        // Finally, display rendered frame in window (swap buffers)
        window.display();
	}// end of game loop

    return EXIT_SUCCESS;
}


