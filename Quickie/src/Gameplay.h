#pragma once

#include <vector>
#include <stack>

#include "State.h"
#include "Player.h"
#include "Wall.h"
#include "Obstacle.h"
#include "LevelManager.h"
#include "Menu.h"
#include "Behaviour.h"

namespace gameplayNS
{
	enum Mode {
		LEVEL_1,
		LEVEL_2,
		LEVEL_3,
		LEVEL_SHUFFLE,
		LEVEL_RANDOM,
		REVERT
	};

	const std::string options[] = { "Level 1",
									"Level 2",
									"Level 3",
									"Shuffle Levels",
									"Really Randomise Levels", };
	const int optionsLength = 5;
}

class Gameplay : public State
{
	rapidjson::Document			obstacleDoc;
	std::vector<VertexShape*>	qEnvironmentObj;
	std::vector<VertexShape*>	qPlayer;

	LevelManager*				lManager;
	bool						gameplay = false;
	bool						AIGame = false;
	
	gameplayNS::Mode						selectedMode;
	std::stack<gameplayNS::Mode>			gameStack;

	Obstacle* o1;
	Obstacle* o2;
	Obstacle* o3;
	Obstacle* o4;
	Obstacle* o5;
	Obstacle* o6;

	Wall* w1;		// - up
	Wall* w2; 		// - down
	Wall* w3; 		// | left
	Wall* w4;		// | right

	Player* sqr1;
	Player* sqr2;
	Player* sqr3;

	Behaviour	AIBehaviour;
	AI*			computer;

public:
	Gameplay();
	virtual ~Gameplay();
	Menu* menu;

	void initialize(Graphics* graphics, Input* input, Audio* audio, rapidjson::Document& doc, float* deltaTime) override;
	void update() override;
	void ai() override;
	void render() override;
	void collisions() override{};
	void releaseAll() override{};
	void resetAll() override{};
	void Gameplay::setCurrentSceneByInput(gameplayNS::Mode, int);
	void Gameplay::selectMode(gameplayNS::Mode, int);
};
