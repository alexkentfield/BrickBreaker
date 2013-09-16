#include "brickGame.h"

BrickGame::BrickGame(sf::RenderWindow* win, int screenHeight, int screenWidth)
{
	window = win;
	screenX = screenWidth;
	screenY = screenHeight;
}

void BrickGame::Init()
{
	gameBall = new Ball(screenX, screenY);
	gamePaddle = new Paddle(screenX, screenY);

	isTitleOn = true;
	playerHealth = 3;
	currentLevel = 1;

	font.loadFromFile("Content/gothic.ttf");

	music.openFromFile("Content/backgroundMusic.wav");
	music.setPosition(0, 1, 10); // change its 3D position
	music.setPitch(2);           // increase the pitch
	music.setVolume(100);         // reduce the volume
	music.setLoop(true);         // make it loop
	music.play();

	livesLabel.setFont(font);
	livesLabel.setCharacterSize(40);
	livesLabel.setStyle(sf::Text::Bold);
	livesLabel.setColor(sf::Color::White);
	livesLabel.setPosition(40, 5);
	livesLabel.setString("LIVES");

	levelLabel.setFont(font);
	levelLabel.setCharacterSize(40);
	levelLabel.setStyle(sf::Text::Bold);
	levelLabel.setColor(sf::Color::White);
	levelLabel.setPosition(screenX - 150, 5);
	levelLabel.setString("LEVEL");

	titleLabel.setFont(font);
	titleLabel.setCharacterSize(100);
	titleLabel.setStyle(sf::Text::Bold);
	titleLabel.setColor(sf::Color::White);
	titleLabel.setPosition(screenX / 2 - 160, screenY / 3);
	titleLabel.setString("Brick Breaker");

	spaceLabel.setFont(font);
	spaceLabel.setCharacterSize(60);
	spaceLabel.setStyle(sf::Text::Bold);
	spaceLabel.setColor(sf::Color::White);
	spaceLabel.setPosition(screenX / 2 - 130, screenY / 2);
	spaceLabel.setString("Space to Continue");

	winLabel.setFont(font);
	winLabel.setCharacterSize(100);
	winLabel.setStyle(sf::Text::Bold);
	winLabel.setColor(sf::Color::White);
	winLabel.setPosition(screenX / 2 - 130, screenY / 3);
	winLabel.setString("You Win!");

	playerLives.setCharacterSize(40);
	playerLives.setFont(font);
	playerLives.setColor(sf::Color::Cyan);
	playerLives.setPosition(115, 5);
	playerConvert << playerHealth;

	levelNumber.setCharacterSize(40);
	levelNumber.setFont(font);
	levelNumber.setColor(sf::Color::Cyan);
	levelNumber.setPosition(screenX - 70, 5);
	levelConvert << currentLevel;

	startBuffer.loadFromFile("Content/startBall.wav");
	startSound.setVolume(80);
	startSound.setBuffer(startBuffer);

	lossBuffer.loadFromFile("Content/enemyScore.wav");
	lossSound.setVolume(80);
	lossSound.setBuffer(lossBuffer);

	levelManager.LoadLevel(currentLevel);
	levelManager.Init();

	isPlaying = false;

	gameBall->Init();
	gamePaddle->Init();
}

void BrickGame::Update(sf::Clock& clock)
{


	while (window->isOpen())
	{
		if ( isTitleOn )
		{
			window->draw(titleLabel);
			window->draw(spaceLabel);

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
			{
				isTitleOn = false;
			}
		}
			deltaTime = clock.restart();
			window->display();
			window->clear();
			
			if (!isTitleOn)
			{
				window->draw(livesLabel);
				window->draw(levelLabel);

				window->draw(playerLives);
				window->draw(levelNumber);

				gameBall->Draw(window);
				gamePaddle->Draw(window);
				levelManager.Draw(window);
			}

			playerLives.setString(playerConvert.str());
			levelNumber.setString(levelConvert.str());

			sf::Event event;
			while (window->pollEvent(event))
			{
				if (event.type == sf::Event::Closed)
					window->close();
			}

			if (!isPlaying)
			{
				gameBall->gameBall.setPosition(screenX / 2,screenY / 2.5);
				gameBall->Velocity(sf::Vector2f(150.3f, 250.45f));
				
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
				{
					isPlaying = true;
					startSound.play();
				}
			}

			gamePaddle->Update(gameBall, deltaTime);

			if (isPlaying)
			{
				gameBall->Update(deltaTime);
				

				levelManager.Update(gameBall);

				if (gameBall->gameBall.getPosition().y >= screenY)
				{	
					playerHealth--;

					if (playerHealth <= 0)
					{
						playerHealth = 3;
						isPlaying = false;
						levelManager.LoadLevel(currentLevel);
						levelManager.Init();
					}

					lossSound.play();
					playerConvert = std::ostringstream();
					playerConvert << playerHealth;
					isPlaying = false;
				}

				if (levelManager.AllBricksDestroyed())
				{
					currentLevel++;
					if (currentLevel >= 6)
					{
						window->draw(winLabel);
						isPlaying = false;
					}
					isPlaying = false;
					levelConvert = std::ostringstream();
					levelConvert << currentLevel;
					levelManager.LoadLevel(currentLevel);
					levelManager.Init();
					playerHealth = 3;
					playerConvert = std::ostringstream();
					playerConvert << playerHealth;
				}


			}
	}

}

BrickGame::~BrickGame()
{

}