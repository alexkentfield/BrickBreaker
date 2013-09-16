#include "levelManager.h"

LevelManager::LevelManager()
{

}

void LevelManager::Update(Ball* gameBall)
{
	for (std::vector<Brick*>::iterator it = bricks.begin(); it != bricks.end(); ++it)	
	{
		(*it)->Update(gameBall);
	}

	for (std::vector<Brick*>::iterator it = bricks.begin(); it != bricks.end(); ++it)	
	{
		if ((*it)->isDestroyed() && it + 1 == bricks.end() && !areAllBricksDestroyed)
		{
			areAllBricksDestroyed = true;
		}
		else if (!(*it)->isDestroyed())
		{
			break;
		}		
	}
}

void LevelManager::LoadLevel( int levelToLoad )
{
	ClearLevel();

	std::string levelNumber = std::to_string(levelToLoad);
	levelNumber.append(".txt");

	if (levelToLoad > 0 && levelToLoad <= 5)
	{
		currentLevel.open(levelNumber);

		if (currentLevel.is_open())
		{
			int rowIdx=0;
			int colIdx=0;

			while (currentLevel.good())
			{
				char bricktype = currentLevel.get();

				if( bricktype == '\n' )
				{
					printf("\n");
					rowIdx++;
					colIdx=0;
				}
				else
				{
					// Skip the brick
					if( bricktype == '0' )
					{	
						printf("[-]", bricktype);
					}
					else
					{			
						if( bricktype == '1' )
						{
							printf("[1]", bricktype);	
							Brick* newBrick = new Brick((colIdx * 70) + 70, (rowIdx * 30) + 60, 1);
							bricks.push_back(newBrick);
						}
						else if( bricktype == '2' )
						{
							printf("[2]", bricktype);	
							Brick* newBrick = new Brick((colIdx * 70) + 70, (rowIdx * 30) + 60, 2);
							bricks.push_back(newBrick);
						}
						else if( bricktype == '3' )
						{
							printf("[3]", bricktype);	
							Brick* newBrick = new Brick((colIdx * 70) + 70, (rowIdx * 30) + 60, 3);
							bricks.push_back(newBrick);
						}
						else if( bricktype == '4' )
						{
							printf("[4]", bricktype);	
							Brick* newBrick = new Brick((colIdx * 70) + 70, (rowIdx * 30) + 60, 4);
							bricks.push_back(newBrick);
						}

					}
		
					colIdx++;
				}
			}

	
		}
	}
	currentLevel.close();
	areAllBricksDestroyed = false;
}

void LevelManager::Init()
{
	areAllBricksDestroyed = false;
	for (std::vector<Brick*>::iterator it = bricks.begin(); it != bricks.end(); ++it)
	{
		(*it)->Init();
	}
}

void LevelManager::Draw(sf::RenderWindow* window)
{
	for (std::vector<Brick*>::iterator it = bricks.begin(); it != bricks.end(); ++it)	
	{
		(*it)->Draw(window);
	}
}

void LevelManager::ClearLevel()
{
	bricks.clear();
}

bool LevelManager::AllBricksDestroyed()
{
	return areAllBricksDestroyed;
}