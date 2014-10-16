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
	font.loadFromFile("C:\\Windows\\Fonts\\GARA.TTF");

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
             
    
        } 

		pos+=vel;
		sf::Transform T;
		T.translate(pos);

		rotation+=rotationVel;
		sf::Transform R;
		R.rotate(rotation);

		sf::Transform M=R*T;

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