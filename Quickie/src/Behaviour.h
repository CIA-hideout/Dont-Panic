#pragma once

#include "VertexShape.h"
#include "AI.h"
#include "NodeManager.h"

namespace behaviourNS
{
	const int targetsNum = 3;
	const int behaviourNum = 4;
	const int behaviourRand = 1000;
	const int baseRand = 100;
	const int range = 5;

	enum Type
	{
		TARGET_PLAYER,
		RUN,
		HIDE,
		STOP
	};
}

class Behaviour
{

protected:
	NodeManager* nodeManager;
	Node* bestMove;
	behaviourNS::Type currentBehaviour;
	behaviourNS::Type nextBehaviour;

public:

	Behaviour();
	virtual ~Behaviour();

	virtual void initialize(NodeManager* nM);
	virtual void act(std::vector<VertexShape*>& vS, AI* computer) = 0;
	virtual void randBehaviour() = 0;

	behaviourNS::Type getCurrentBehaviour() const { return currentBehaviour; }
	behaviourNS::Type getNextBehaviour() const { return nextBehaviour; }
};