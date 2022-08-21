#pragma once
#include "gameobject.h"
#include "config.h"

class Player1 : public GameObject, public CollidableR
{
	float speed = 10.0f;
	float pos1_x = CANVAS_WIDTH/40, pos1_y = CANVAS_HEIGHT/2;
	int score1 = 0;
public:
	Player1(const class Game& mygame);
	void update() override;
	void draw() override;
	void init() override;
	float getPos1_x() { return pos1_x; }
	float getPos1_y() { return pos1_y; }
	int addScore1() { return score1 += 1; }
	int getScore1() { return score1; }
	int resetScore1() { return score1 = 0; }
	Rect getCollisionHull() const override;
};
