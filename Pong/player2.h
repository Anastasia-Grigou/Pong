#pragma once
#include "gameobject.h"
#include "config.h"


class Player2 : public GameObject, public CollidableR
{
	float speed = 10.0f;
	float pos2_x = CANVAS_WIDTH / 1.025f, pos2_y = CANVAS_HEIGHT / 2;
	int score2 = 0;
public:
	Player2(const class Game& mygame);
	void update() override;
	void draw() override;
	void init() override;
	float getPos2_x() { return pos2_x; }
	float getPos2_y() { return pos2_y; }
	int addScore2() {return score2 += 1; }
	int getScore2() { return score2; }
	int resetScore2() { return score2 = 0; }
	Rect getCollisionHull() const override;
};
