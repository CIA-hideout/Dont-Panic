#pragma once

#include "ParticleSource.h"
#include "QLine.h"

enum CooldownType {
	COOLDOWN_BLINK,
	COOLDOWN_TELEPORT,
	INVULNERABLE,
	SPAWN_TIME
};

class Player : public VertexShape {
public:

	std::map<CooldownType, float>	cooldown;
	std::map<Control, int>			controls;
	int								health;
	bool							locked;

	ParticleSource					ps;

	Player() = default;
	~Player();

	Player(D3DXVECTOR3& pos, D3DXVECTOR3& dimension, D3DXVECTOR3& scale, D3DXVECTOR3& color);

	void init(Graphics*, Input*);
	void draw(D3DXMATRIX&);
	void update(float, std::vector<VertexShape*>&);
	void move(std::vector<VertexShape*>& vS, float);
	void respawn();
	void blink(std::vector<VertexShape*>&, float);
	void teleport();
	void assignControl(rapidjson::Document&, int player);

	void startDeath();
	
	// GET
	int getHealth(){ return health; }
	bool getLocked(){ return locked; }

	// SET
	void setHealth(int h){ health = h; }
	void setLocked(bool l){ locked = l; }

};
