#include "brick.h"
#include "gameObject.h"
#include <vector>

Brick::Brick(int xPos, int yPos, int setHealth)
{
	m_Brick.setPosition(xPos,yPos);
	health = setHealth;
	bDestroyed = false;
}

Brick::~Brick()
{

}

void Brick::Init()
{
	brickWidth = 60;
	brickHeight = 20;
	playerSpin = 0.1f;
	brickBuffer.loadFromFile("Content/paddleHit.wav");
	brickSound.setVolume(80);
	brickSound.setBuffer(brickBuffer);

	finishBuffer.loadFromFile("Content/youScore.wav");
	finishSound.setVolume(80);
	finishSound.setBuffer(finishBuffer);


	velocity.x = 0.1f;
	velocity.y = 0.1f;

	m_Brick.setSize(sf::Vector2f(brickWidth, brickHeight));
	m_Brick.setOutlineThickness(1);
	m_Brick.setOrigin(0,0);
	//m_Brick.setOutlineColor(sf::Color::Cyan);
}


void Brick::Update(Ball* ball)
{
	if (!bDestroyed)
	{
		CheckCollisions(ball);
	}
}

void Brick::Draw(sf::RenderWindow *window)
{
	window->draw(m_Brick);

	if (!bDestroyed)
	{
		

		if (health == 4)
		{
			m_Brick.setFillColor(sf::Color::Red);
		}
		else if (health == 3)
		{
			m_Brick.setFillColor(sf::Color::Yellow);
		}
		else if (health == 2)
		{
			m_Brick.setFillColor(sf::Color::Green);
		}
		else if (health == 1)
		{
			m_Brick.setFillColor(sf::Color::Blue);
		}

		position = m_Brick.getPosition();
	}
	else
	{
		m_Brick.setOutlineThickness(0);
		m_Brick.setTexture(NULL);
		m_Brick.setFillColor(sf::Color::Transparent);
	}
}

void Brick::CheckCollisions(Ball* m_ball)
{

	if ((m_ball->gameBall.getPosition().x - m_ball->GetBallRadius() < m_Brick.getPosition().x + brickWidth) && 
		(m_ball->gameBall.getPosition().x + m_ball->GetBallRadius() > m_Brick.getPosition().x))
	{
		if ((m_ball->gameBall.getPosition().y - m_ball->GetBallRadius() < m_Brick.getPosition().y + brickHeight) &&
			(m_ball->gameBall.getPosition().y + m_ball->GetBallRadius() > m_Brick.getPosition().y))
		{
			if (ballLastPos.x + m_ball->GetBallRadius() > m_Brick.getPosition().x && ballLastPos.x - m_ball->GetBallRadius() < m_Brick.getPosition().x + brickWidth)
			{
				if (m_ball->Velocity().y > 0)
				{
					m_ball->Velocity(sf::Vector2f(m_ball->Velocity().x, m_ball->Velocity().y  * - 1));
					m_ball->gameBall.setPosition(m_ball->gameBall.getPosition().x, m_Brick.getPosition().y - m_ball->GetBallRadius());
				}
				else if(m_ball->Velocity().y < 0)
				{
					m_ball->Velocity(sf::Vector2f(m_ball->Velocity().x, m_ball->Velocity().y  * - 1));
					m_ball->gameBall.setPosition(m_ball->gameBall.getPosition().x, m_Brick.getPosition().y + brickHeight + m_ball->GetBallRadius());
				}


				health--;
				if (health <= 0)
				{
					bDestroyed = true;
					//delete this;
					finishSound.play();
				}
			}
			else if (ballLastPos.y - m_ball->GetBallRadius() < m_Brick.getPosition().y + brickHeight && ballLastPos.y > m_Brick.getPosition().y)
			{
				if (m_ball->Velocity().x > 0)
				{
					m_ball->Velocity(sf::Vector2f(m_ball->Velocity().x * - 1, m_ball->Velocity().y));
					m_ball->gameBall.setPosition( m_Brick.getPosition().x  - m_ball->GetBallRadius(), m_ball->gameBall.getPosition().y);
				}
				else if(m_ball->Velocity().x < 0)
				{
					m_ball->Velocity(sf::Vector2f(m_ball->Velocity().x * - 1, m_ball->Velocity().y));
					m_ball->gameBall.setPosition( m_Brick.getPosition().x + brickWidth + m_ball->GetBallRadius(), m_ball->gameBall.getPosition().y);
				}
				health--;
				if (health <= 0)
				{
					bDestroyed = true;
					//delete this;
					finishSound.play();
				}
			}		
			if (!bDestroyed)
			{
				brickSound.play();
			}
		}
	}

	ballLastPos =  m_ball->gameBall.getPosition();
}

int Brick::GetBrickWidth()
{
	return brickWidth;
}

int Brick::GetBrickHeight()
{
	return brickHeight;
}

bool Brick::isDestroyed()
{
	return bDestroyed;
}