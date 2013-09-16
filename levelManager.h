#pragma once
#include "brick.h"
#include "levelManager.h"
#include <fstream>
#include <string>

class LevelManager
{
private:
	std::vector<Brick*> bricks;
	std::ifstream currentLevel;
	bool areAllBricksDestroyed;

public:

	LevelManager();

	void Update(Ball* gameBall);
	void LoadLevel( int levelToLoad );
	void ClearLevel();
	void Init();
	void Draw(sf::RenderWindow* window);
	bool AllBricksDestroyed();
};

