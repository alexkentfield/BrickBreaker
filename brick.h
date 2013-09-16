#pragma once
#include <SFML\Graphics.hpp>
#include <SFML\Audio.hpp>
#include "ball.h"
#include "gameObject.h"
#include <vector>

class Brick : public GameObject
{
private:
	bool player;
	bool bDestroyed;
	int health;
	float playerSpin;
	int brickWidth;
	int brickHeight;
	sf::SoundBuffer brickBuffer;
	sf::Sound brickSound;
	sf::SoundBuffer finishBuffer;
	sf::Sound finishSound;
	sf::Vector2f ballLastPos;

public:
	sf::RectangleShape m_Brick;
	Brick(int xPos, int yPos, int setHealth);
	~Brick();

	virtual void Init();
	virtual void Update(Ball* ball);
	virtual void Draw(sf::RenderWindow *window);
	virtual void CheckCollisions(Ball* ball);
	virtual int GetBrickWidth();
	virtual int GetBrickHeight();
	virtual bool isDestroyed();
};
