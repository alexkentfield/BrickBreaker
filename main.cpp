#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "ball.h"
#include "gameObject.h"
#include "paddle.h"
#include "brick.h"
#include "levelManager.h"
#include "brickGame.h"
#include <vector>


int main()
{
	int const screenWidth = 900;
	int const screenHeight = 900;
	
	sf::Clock clock;
	sf::RenderWindow* window = new sf::RenderWindow(sf::RenderWindow(sf::VideoMode(screenWidth, screenHeight), "-= Brick Breaker =-"));

	BrickGame brickGame(window, screenWidth, screenHeight);

	brickGame.Init();
	brickGame.Update(clock);


	return 0;
}