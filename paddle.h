#pragma once
#include <SFML\Graphics.hpp>
#include <SFML\Audio.hpp>
#include "ball.h"
#include "gameObject.h"

class Paddle : public GameObject
{
private:
	int paddleWidth;
	int paddleHeight;
	sf::SoundBuffer paddleBuffer;
	sf::Sound paddleSound;
	sf::Vector2f ballLastPos;

public:
	sf::RectangleShape m_Paddle;
	Paddle(int screenWidth, int screenHeight);
	~Paddle();

	virtual void Init();
	virtual void Update(Ball* ball, sf::Time& time);
	virtual void Draw(sf::RenderWindow *window);
	virtual void CheckCollisions(Ball* ball);
	void resetPaddleSize();

};
