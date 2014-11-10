//////////////////////////////////////////////////////////// 
// Headers 
//////////////////////////////////////////////////////////// 
#include "stdafx.h" 
#ifdef _DEBUG 
#pragma comment(lib,"sfml-graphics-d.lib") 
#pragma comment(lib,"sfml-audio-d.lib") 
#pragma comment(lib,"sfml-system-d.lib") 
#pragma comment(lib,"sfml-window-d.lib") 
#pragma comment(lib,"sfml-network-d.lib") 
#else 
#pragma comment(lib,"sfml-graphics.lib") 
#pragma comment(lib,"sfml-audio.lib") 
#pragma comment(lib,"sfml-system.lib") 
#pragma comment(lib,"sfml-window.lib") 
#pragma comment(lib,"sfml-network.lib") 
#endif 
#pragma comment(lib,"opengl32.lib") 
#pragma comment(lib,"glu32.lib") 
 
#include "SFML/Graphics.hpp" 
#include "SFML/OpenGL.hpp" 
#include <iostream> 

//FMOD includes
#pragma comment(lib,"fmodex_vc.lib")
#include "fmod.hpp"
#include "fmod_errors.h"


  
////////////////////////////////////////////////////////////
///Entrypoint of application 
//////////////////////////////////////////////////////////// 

int main() 
{ 
    // Create the main window 
    sf::RenderWindow window(sf::VideoMode(800, 600, 32), "SFML First Program"); 
	window.setFramerateLimit(60);
   
	//load a font
	sf::Font font;
	font.loadFromFile("C:\\Windows\\Fonts\\Arial.TTF");

	//create a formatted text string
    sf::Text text;
    text.setFont(font);
    text.setString("Hello World");
	text.setStyle(sf::Text::Underlined| sf::Text::Italic | sf::Text::Bold);
    text.setPosition(20,40);
    text.setCharacterSize(40);

	//create a circle
	//sf::CircleShape circle(50);
	//circle.setPosition(300,200);
	
	const int size=5;

	sf::VertexArray lines(sf::LinesStrip, size); 

	sf::Vector2f points[size];
	points[0]=sf::Vector2f(50,0);
	points[1]=sf::Vector2f(0,-50);
	points[2]=sf::Vector2f(-50,0);
	points[3]=sf::Vector2f(0,50);
	points[4]=points[0];

	sf::Vector2f pos(0,0);
	
	sf::Vector2f vel(1.0,0.5);

	float rotation=0.0;
	float rotationVel=1.0;

	
	//setup FMOD
	FMOD::System *FMODsys; //the FMOD sytem
	FMOD_RESULT result;
	result = FMOD::System_Create(&FMODsys); 	// Create the main system object.
	if (result != FMOD_OK)
	{
		std::cout << "FMOD error! " << result << FMOD_ErrorString(result);
		
	}
 
	result = FMODsys->init(100, FMOD_INIT_NORMAL, 0);   // Initialize FMOD.
     
	if (result != FMOD_OK)
	{
		std::cout << "FMOD error! " << result << FMOD_ErrorString(result);
		
	}

	FMOD::Sound *sound;
result = FMODsys->createSound(
    "C:\\SDKS\\FMOD Programmers API Windows\\examples\\media\\wave.mp3",
    FMOD_DEFAULT,
    0,
    &sound);
if (result != FMOD_OK)
{
    std::cout << "FMOD error! (%d) %s\n" << result;
   
}
FMOD::Channel *channel;
FMODsys->playSound(FMOD_CHANNEL_FREE, sound, false, &channel);
   
       
    // Start game loop 
    while (window.isOpen()) 
    { 
        // Process events 
        sf::Event Event; 
        while (window.pollEvent(Event)) 
        { 
            // Close window : exit 
            if (Event.type == sf::Event::Closed) 
                window.close(); 
   
            // Escape key : exit 
            if ((Event.type == sf::Event::KeyPressed) && (Event.key.code == sf::Keyboard::Escape)) 
                window.close();  
			

			
			if ((Event.type == sf::Event::KeyPressed) && (Event.key.code == sf::Keyboard::Up)) {
                rotationVel*=0.95;
				FMOD::Channel *channel;
				FMODsys->playSound(
					FMOD_CHANNEL_FREE, //finda free channel
					sound,          	// sound to play
					true,      	//start paused
					0);         	//channel reference
			}
             
    
        } 

		FMODsys->update();
		sf::Transform C;
		C.translate(400,300);

		//pos+=vel;
		sf::Transform T;
		T.translate(pos);

		rotation+=rotationVel;
		sf::Transform R;
		R.rotate(rotation);

		sf::Transform M=C*R;

		//update lines
		for(int i=0;i<size;i++){
			lines[i].position=M.transformPoint(points[i]);
		}
         
		//prepare frame
        window.clear();

		//draw frame items
        window.draw(text);

		window.draw(lines);
		
       
        // Finally, display rendered frame on screen 
        window.display(); 
    } //loop back for next frame
   
    return EXIT_SUCCESS; 
}