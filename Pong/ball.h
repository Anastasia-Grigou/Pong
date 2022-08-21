#pragma once
#include "gameobject.h"
#include "config.h"
#include "graphics.h"


class Ball : public GameObject, public Collidable
{
	float pos_x , pos_y;
	float dir_x, dir_y;
	float speed;
	float rotation;
	float size;
	graphics::Brush brush;
	bool active = true;
public:
	void update() override;
	void draw() override;
	void init() override;
	bool isActive() { return active; }
	float getPos_x() { return pos_x; }
	void setPos_x(float x) { pos_x = x; }
	float getPos_y() { return pos_y; }
	void setPos_y(float y) { pos_y = y; }
	void setDir_x(float d) { dir_x = d; }
	float getDir_x(){ return dir_x; }
	void setDir_y(float d) { dir_y = d; }
	float getDir_y() { return dir_y; }
	void setSpeed(float s) { speed = s; }
 
	Disk getCollisionHull()const override;
	Ball(const class Game& mygame);
	~Ball();
};
