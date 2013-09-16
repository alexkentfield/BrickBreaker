#include <SFML\Graphics.hpp>
#include <SFML\Audio.hpp>
#include "ball.h"
#include "paddle.h"
#include "levelManager.h"
#include <sstream>

class BrickGame
{
private:
	int screenX;
	int screenY;
	bool isPlaying;
	int playerHealth;
	int currentLevel;
	bool isTitleOn;

	sf::Time deltaTime;

	sf::RenderWindow* window;
	LevelManager levelManager;

	Ball* gameBall;
	Paddle* gamePaddle;

	sf::SoundBuffer startBuffer;
	sf::Sound startSound;
	sf::SoundBuffer lossBuffer;
	sf::Sound lossSound;
	sf::Music music;

	sf::Text playerLives;
	std::ostringstream playerConvert;

	sf::Text levelNumber;
	std::ostringstream levelConvert;

	sf::Font font;
	sf::Text livesLabel;
	sf::Text levelLabel;
	sf::Text spaceLabel;
	sf::Text titleLabel;
	sf::Text winLabel;

public:
	BrickGame(sf::RenderWindow* win, int screenHeight, int screenWidth);
	~BrickGame();

	void Init();
	void Update(sf::Clock& clock);
};