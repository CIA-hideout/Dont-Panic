#pragma once

#include "ParticleSource.h"
#include "QLine.h"
#include "GUIBar.h"

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
	bool							controlled = false;
	bool							controlledTP = false;
	GUIBar*							healthBar;
	static int						winner;
	ParticleSource					ps;

	Player() = default;
	~Player();

	Player(D3DXVECTOR3& pos, D3DXVECTOR3& dimension, D3DXVECTOR3& scale, D3DXVECTOR3& color);

	void init(Graphics*, Input*, Audio*);
	void draw(D3DXMATRIX&);
	void update(float, std::vector<VertexShape*>&);
	void move(std::vector<VertexShape*>& vS, float);
	void respawn();
	void die();
	void blink(std::vector<VertexShape*>&, float);
	void teleport(std::vector<VertexShape*>&, float);
	void assignControl(rapidjson::Document&, int player);
};
