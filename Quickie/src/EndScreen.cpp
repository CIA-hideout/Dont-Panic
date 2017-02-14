#include "EndScreen.h"

EndScreen::EndScreen()
{
	currentScene = endscreenNS::EXPLODE;
	D3DXMatrixIdentity(&worldMatrix);
}

EndScreen::~EndScreen()
{
	
}

void EndScreen::initialize(Graphics* g, Input* i, Audio* a, rapidjson::Document& doc, float* dT)
{
	D3DXVECTOR3 pos3D;
	State::initialize(g, i, a, doc, dT);
	Player temp = Player();

	graphics->camera->pointInWorld(pos3D, sqr1Pos, playerNS::z);
	if (temp.winner == 1)
		sqr1 = new Player(pos3D, D3DXVECTOR3(2, 2, 2), D3DXVECTOR3(1, 1, 1), D3DXVECTOR3(240, 240, 0));
	else
		sqr1 = new Player(pos3D, D3DXVECTOR3(2, 2, 2), D3DXVECTOR3(1, 1, 1), D3DXVECTOR3(0, 240, 240));
	graphics->camera->pointInWorld(pos3D, sqr2Pos, playerNS::z);
	if (temp.winner == 2)
		sqr2 = new Player(pos3D, D3DXVECTOR3(2, 2, 2), D3DXVECTOR3(1, 1, 1), D3DXVECTOR3(0, 240, 240));
	else
		sqr2 = new Player(pos3D, D3DXVECTOR3(2, 2, 2), D3DXVECTOR3(1, 1, 1), D3DXVECTOR3(240, 240, 0));

	if (temp.winner == 0)
	{
		sqr1->color = D3DXVECTOR3(0, 240, 0);
		sqr2->color = D3DXVECTOR3(0, 240, 0);
	}

	sqr1->init(g, i, a);
	sqr2->init(g, i, a);
	audio->stopCue(BGMRand);
	audio->playCue(menuBGM);
	menu->canPlaySound = false;
	State::initialize(g, i, a, doc, dT);
}

void EndScreen::update()
{
	if (input->getKeyState(controls.at(CONTROL_ENTER)))
	{
		nextState = stateNS::REVERT;
		pNextState = &nextState;
		audio->playCue(menuSelect);
	}
	else
	{
		switch (currentScene)
		{
		case endscreenNS::EXPLODE:
			{
			sqr1->velocity.y += *deltaTime * playerNS::speed;
			sqr1->controlled = true;
			sqr2->velocity.y += *deltaTime * playerNS::speed;
			sqr2->controlled = true;

			D3DXVECTOR2 pos2D = D3DXVECTOR2(0, GAME_HEIGHT / 6);
			D3DXVECTOR3 pos3D;
			graphics->camera->pointInWorld(pos3D, pos2D, playerNS::z);
			if (sqr1->pos.y > pos3D.y)
			{
				sqr1->die(false);
				sqr2->die(false);
			}
		
			if (!sqr1->alive && !sqr2->alive)
				currentScene = endscreenNS::RESPAWN;
			}
			
			break;

		case endscreenNS::RESPAWN:
			if (sqr1->alive && sqr2->alive)
			{
				D3DXVECTOR3 pos3D;

				graphics->camera->pointInWorld(pos3D, sqr1Pos, playerNS::z);
				sqr1->pos.x = pos3D.x;
				sqr1->pos.y = pos3D.y;

				graphics->camera->pointInWorld(pos3D, sqr2Pos, playerNS::z);
				sqr2->pos.x = pos3D.x;
				sqr2->pos.y = pos3D.y;
				
				currentScene = endscreenNS::EXPLODE;
			}
			break;
		}
		
		graphics->camera->update(*deltaTime);
		sqr1->update(*deltaTime, qEnvironmentObj);
		sqr2->update(*deltaTime, qEnvironmentObj);

		for (int i = 0; i < qEnvironmentObj.size(); ++i)
		{
			if (qEnvironmentObj[i]->objectType == OBJECT_TYPE_QLINE) {
				QLine* temp = (QLine*)qEnvironmentObj[i];
				temp->update(*deltaTime, qEnvironmentObj);
			}
		}
	}
}

void EndScreen::render()
{
	Font f;

	f = fonts.at(fontsNS::HEADING1);
	
	// Set Title Screen
	if (sqr1->winner == 1)
	{
		f.print(
			GAME_WIDTH / 2 - f.getTotalWidth("Player 1 wins") / 2,
			GAME_HEIGHT / 5,
			fontNS::YELLOW,
			"Player 1 wins");	
	}
	else if (sqr2->winner == 2)
	{
		f.print(
			GAME_WIDTH / 2 - f.getTotalWidth("Player 2 wins") / 2,
			GAME_HEIGHT / 5,
			fontNS::BLUE,
			"Player 2 wins");
	}
	else if (sqr1->winner == 0)
	{
		f.print(
			GAME_WIDTH / 2 - f.getTotalWidth("Computer wins") / 2,
			GAME_HEIGHT / 5,
			fontNS::GREEN,
			"Computer wins");
	}


	// Set Fonts for Options
	f = fonts.at(fontsNS::END_SCREEN);
	
	if (timeGetTime() % 500 < 250)
		f.print(
			GAME_WIDTH / 2 - f.getTotalWidth("Press Enter to Exit") / 2,
			GAME_HEIGHT / 2,
			"[Press Enter to Exit]");

	for (int i = 0; i < qEnvironmentObj.size(); i++) {
		qEnvironmentObj[i]->draw(worldMatrix);
	}
	sqr1->draw(worldMatrix);
	sqr2->draw(worldMatrix);
}