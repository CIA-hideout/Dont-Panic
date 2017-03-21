#pragma once

#include "Behaviour.h"

class Stop : public Behaviour
{

public:

	Stop();
	~Stop();

	void initialize(NodeManager* nM) override;
	void act(std::vector<VertexShape*>& vS, AI* computer) override;
	void randBehaviour() override;
};
