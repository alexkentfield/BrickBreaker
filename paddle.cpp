#include "paddle.h"
#include "gameObject.h"

Paddle::Paddle(int screenWidth, int screenHeight)
{
	screenX = screenWidth;
	screenY = screenHeight;
}

void Paddle::Init()
{
	paddleWidth = 150;
	paddleHeight = 20;

	paddleBuffer.loadFromFile("Content/paddleHit.wav");
	paddleSound.setVolume(80);
	paddleSound.setBuffer(paddleBuffer);

	velocity.x = 0.1f;
	velocity.y = 0.1f;

	m_Paddle.setSize(sf::Vector2f(paddleWidth, paddleHeight));
	m_Paddle.setOrigin(0,0);
	m_Paddle.setOutlineThickness(3);
	m_Paddle.setOutlineColor(sf::Color::Blue);
	m_Paddle.setPosition(screenX / 2, screenY - 40);
}


void Paddle::Update(Ball* ball, sf::Time& time)
{
	CheckCollisions(ball);

	position = m_Paddle.getPosition();

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		m_Paddle.move(-500 * time.asSeconds(), 0 * time.asSeconds());
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		m_Paddle.move(500 * time.asSeconds(), 0 * time.asSeconds());
	}
}

void Paddle::Draw(sf::RenderWindow *window)
{
	window->draw(m_Paddle);
}

void Paddle::CheckCollisions(Ball* m_ball)
{
	if (m_Paddle.getPosition().x <= 0)
	{
		m_Paddle.setPosition(sf::Vector2f(0,position.y));
	}

	if (m_Paddle.getPosition().x >= screenX - paddleWidth)
	{
		m_Paddle.setPosition(sf::Vector2f(screenX - paddleWidth,position.y));
	}

	if ((m_ball->gameBall.getPosition().x - m_ball->GetBallRadius() < m_Paddle.getPosition().x + paddleWidth) && 
		(m_ball->gameBall.getPosition().x + m_ball->GetBallRadius() > m_Paddle.getPosition().x))
	{
		if ((m_ball->gameBall.getPosition().y - m_ball->GetBallRadius() < m_Paddle.getPosition().y + paddleHeight) &&
			(m_ball->gameBall.getPosition().y + m_ball->GetBallRadius() > m_Paddle.getPosition().y))
		{
			if (ballLastPos.x + m_ball->GetBallRadius() > m_Paddle.getPosition().x && ballLastPos.x  - m_ball->GetBallRadius() < m_Paddle.getPosition().x + paddleWidth)
			{

				if (m_ball->Velocity().y > 0)
				{
					m_ball->Velocity(sf::Vector2f(m_ball->Velocity().x, m_ball->Velocity().y  * - 1));
					m_ball->Velocity(sf::Vector2f(m_ball->Velocity().x * 1.03f, m_ball->Velocity().y * 1.03f));
					m_ball->gameBall.setPosition(m_ball->gameBall.getPosition().x, m_Paddle.getPosition().y - m_ball->GetBallRadius());
				}

				if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
				{
					m_ball->Velocity(sf::Vector2f(m_ball->Velocity().x - 150, m_ball->Velocity().y ));
				}
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
				{
					m_ball->Velocity(sf::Vector2f(m_ball->Velocity().x + 150, m_ball->Velocity().y ));
				}

			}
			else if (ballLastPos.y - m_ball->GetBallRadius() < m_Paddle.getPosition().y + paddleHeight && ballLastPos.y + m_ball->GetBallRadius()> m_Paddle.getPosition().y)
			{
				m_ball->Velocity(sf::Vector2f(m_ball->Velocity().x * - 1, m_ball->Velocity().y));
				m_ball->Velocity(sf::Vector2f(m_ball->Velocity().x * 1.05f, m_ball->Velocity().y * 1.05f));

				if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
				{
					m_ball->Velocity(sf::Vector2f(m_ball->Velocity().x - 0.04f, m_ball->Velocity().y));
				}
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
				{
					m_ball->Velocity(sf::Vector2f(m_ball->Velocity().x + 0.04f, m_ball->Velocity().y));
				}
			}			
			paddleSound.play();
		}
	}

	ballLastPos =  m_ball->gameBall.getPosition();
}

void Paddle::resetPaddleSize()
{
	paddleHeight = 150;
}