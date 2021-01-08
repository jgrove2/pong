#include <SFML/Graphics.hpp>
#include <iostream>
#include <math.h>
#include <string>
#include <stdlib.h>


class Player
{
	public:
		float locx;
		float locy;
		int width = 25;
		int height = 120;
		int score = 0;

		Player(float x, float y) {
			locx = x;
			locy = y;
		}

		void moveUp(){
			if(locy-2 >= 0){
				locy -= 4;
			}
		}
	
		void moveDown(){
			if(locy + height + 2 < 800){
				locy += 4;
			}
		}
		void addScore(){
			score+=1;
			std::cout << score << "p1" << std::endl;
		}
};

class Ball
{
	public:
		float locx = 600;
		float locy = 400;
		float angle = 45;
		float speed = 3.5;
		float radius = 25.f;
		int window_width = 1200;
		int window_height = 800;
		int p1score = 0;
		int p2score = 0;

		void move(int width, int height)
		{
			locx += (speed * cos(M_PI * angle/180));
			locy += (speed * sin(M_PI * angle/180));
			window_height = height;
			window_width = width;
		}
		bool playerCollision(Player p)
		{
			float locs[4][2] = {{locx, locy}, {locx, locy + radius}, {locx + radius, locy}, {locx + radius, locy + radius}};

			for(int i = 0; i < 4; i ++){
				if(p.locx <= locs[i][0] && p.locx + p.width >= locs[i][0] && p.locy <= locs[i][1] && p.locy + p.height >= locs[i][1]){
					return true;
				}
			}
			return false;
		}
		void checkCollision(Player otherOne, Player otherTwo)
		{
			if(locy <= 0){
				angle -= 270;
				//locx += radius * 2;
			}
			else if(locy + radius >= window_height){
				angle -= 270;
				//locx += radius * 2;
			}
			else if(locx <= 0){
				angle -= 270;
				locx = 600;
				locy = 400;
				speed = 2;
				p2score += 1;
				angle = 225 - rand() % 90;
				//locx += radius * 2;
			}
			else if(locx + radius >= window_width){
				locx = 600;
				locy = 300 + rand() % 200;
				p1score += 1;
				speed = 2;
				angle = -45 + rand() % 90;
				//locx += radius * 2;
			}
			
			else if(playerCollision(otherOne)){
				angle -= 180;
				if(speed < 9) speed *= 1.5;
			}
			else if(playerCollision(otherTwo)){
				angle -= 180;
				if(speed < 9) speed *= 1.5;
			}
		}


};

int main()
{
    sf::RenderWindow window(sf::VideoMode(1200, 800), "PONG!");
	window.setFramerateLimit(100);
	sf::RectangleShape playerOne(sf::Vector2f(25.f, 120.f));
	sf::RectangleShape ball(sf::Vector2f(25.f, 25.f));
	sf::RectangleShape playerTwo(sf::Vector2f(25.f, 120.f));
    ball.setFillColor(sf::Color::White);
	playerOne.setFillColor(sf::Color::White);
	
	sf::Text p1ScoreText;
	sf::Text p2ScoreText;
	sf::Font font;
	if(!font.loadFromFile("Roboto-Black.ttf"))
	{
	}

	p2ScoreText.setFont(font);
	p2ScoreText.setString("Hello World!");
	
	p1ScoreText.setFont(font);
	p1ScoreText.setString("Hello World!");
	p1ScoreText.setCharacterSize(30);
	p2ScoreText.setCharacterSize(30);

	sf::RectangleShape lineMid(sf::Vector2f(5.f, 800.f));
	sf::RectangleShape lineTop(sf::Vector2f(1200.f, 5.f));
	sf::RectangleShape lineBot(sf::Vector2f(1200.f, 5.f));

	Player pOne(50.f, 400.f);
	Player pTwo(1150.f, 400.f);
	Ball b;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
			switch(event.type)
			{
				case sf::Event::Closed:
					window.close();
					break;
				case sf::Event::Resized:
					std::cout << "new width: " << event.size.width << std::endl;
					std::cout << "new height: " << event.size.height << std::endl;
					break;
			}
		}	
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){
			pTwo.moveUp();
        }
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down)){
			pTwo.moveDown();
		}
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::W)){
			pOne.moveUp();
		}
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::S)){
			pOne.moveDown();
		}

		sf::Vector2u size = window.getSize();
		unsigned int width = size.x;
		unsigned int height = size.y;
        window.clear();
		

		window.draw(lineMid);
		window.draw(lineTop);
		window.draw(lineBot);

        window.draw(ball);
		window.draw(playerOne);
		window.draw(playerTwo);
	
		playerOne.setPosition(pOne.locx, pOne.locy);
		playerTwo.setPosition(pTwo.locx, pTwo.locy);
		ball.setPosition(b.locx, b.locy);
		
		p1ScoreText.setString(std::to_string(b.p1score));
		window.draw(p1ScoreText);
		
		p2ScoreText.setString(std::to_string(b.p2score));
		p2ScoreText.setPosition(610,0);
		window.draw(p2ScoreText);

		lineMid.setPosition(600, 0);
		lineTop.setPosition(0, 0);
		lineBot.setPosition(0,795);

		b.move(width, height);
		b.checkCollision(pOne, pTwo);
        window.display();
		
    }

    return 0;
}
