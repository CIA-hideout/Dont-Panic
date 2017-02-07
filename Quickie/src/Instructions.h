#pragma once

#include <vector>
#include "State.h"
#include "CollisionManager.h"
#include "Player.h"
#include <stack>

namespace instructionsNS
{
	enum Scene
	{
		MOVE_RIGHT,
		MOVE_LEFT,
		MOVE_UP,
		MOVE_DOWN,
		TELEPORT,
		BLINK
	};

	const UINT				sqr1X = GAME_WIDTH / 4;
	const UINT				sqr2X = GAME_WIDTH / 1.5;
	const UINT				sqrY = GAME_HEIGHT / 2.5;
	const int				z = 19.5;
}

class Instructions : public State
{
	bool			blink = false;
	float*			deltaTime;
	D3DXMATRIX		worldMatrix;

	instructionsNS::Scene					currentScene;

	Player* sqr1;
	Player* sqr2;
	D3DXVECTOR2		sqr1Pos = D3DXVECTOR2(instructionsNS::sqr1X, instructionsNS::sqrY);
	D3DXVECTOR2		sqr2Pos = D3DXVECTOR2(instructionsNS::sqr2X, instructionsNS::sqrY);
	std::vector<VertexShape*>	qEnvironmentObj;

public:
	Instructions();
	virtual ~Instructions();

	void initialize(Graphics* graphics, Input* input, Audio* audio, rapidjson::Document& doc, float* deltaTime);
	void update() override;
	void ai() override{};
	void render() override;
	void collisions() override{};
	void releaseAll() override{};
	void resetAll() override{};
};
