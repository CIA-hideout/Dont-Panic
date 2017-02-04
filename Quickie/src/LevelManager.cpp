#include "LevelManager.h"

LevelManager::LevelManager()
{

}

LevelManager::~LevelManager()
{
	
}

// set obstacles location for level 1
void LevelManager::setLevelOne(std::vector<VertexShape*> vS)
{
	for (int i = 0; i < vS.size(); i++) {
		Obstacle* tempObs = (Obstacle*) vS[i];
		tempObs->setLevel1();
	}
}

// set obstacles location for level 2
void LevelManager::setLevelTwo(std::vector<VertexShape*> vS)
{
	for (int i = 0; i < vS.size(); i++) {
		Obstacle* tempObs = (Obstacle*)vS[i];
		tempObs->setLevel2();
	}
}

// set obstacles location for level 3
void LevelManager::setLevelThree(std::vector<VertexShape*> vS)
{
	for (int i = 0; i < vS.size(); i++) {
		Obstacle* tempObs = (Obstacle*)vS[i];
		tempObs->setLevel3();
	}
}

// set obstacles location for random levels
void LevelManager::setRandomLevel(std::vector<VertexShape*> vS)
{
	// assign random levels into vector
	if (randomLevel.empty())
		assignRandomLevel();

	int level = randomLevel[0];
	randomLevel.erase(randomLevel.begin()); // clear 1st element 

	switch (level)
	{
		case 1: setLevelOne(vS);
				break;

		case 2: setLevelTwo(vS);
				break;

		case 3: setLevelThree(vS);
				break;
	}
}

// set random levels and store into vector
void LevelManager::assignRandomLevel()
{
	isRandom = true;
	randomLevel.push_back(1);
	randomLevel.push_back(2);
	randomLevel.push_back(3);

	std::random_device rd;     // only used once to initialise (seed) engine
	std::mt19937 rng(rd());    // random-number engine used (Mersenne-Twister in this case)
	std::shuffle(randomLevel.begin(), randomLevel.end(), rng); //ramdomise vector
}