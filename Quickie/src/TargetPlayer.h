#pragma once

#include "Behaviour.h"

class TargetPlayer : public Behaviour
{

public:

	TargetPlayer();
	~TargetPlayer();

	void initialize(NodeManager* nM) override;
	void act(std::vector<VertexShape*>& vS, AI* computer) override;
	void randBehaviour() override;
};