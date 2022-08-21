#pragma once
#include "player1.h"
#include "player2.h"
#include "ball.h"



class Game
{
	typedef enum {STATUS_START, STATUS_PLAYING, STATUS_END} status_t;
	Player1* player1 = nullptr;
	bool player1_initialized = false;
	Player2* player2 = nullptr;
	bool player2_initialized = false;
	bool debug_mode = false;
	Ball* ball = nullptr;
	void spawnBall();
	void checkBall();
	status_t status = STATUS_START;
	int level;

	void updateStartScreen();
	void updateLevelScreen();
	void updateEndScreen();
	void drawStartScreen();
	void drawLevelScreen();
	void drawEndScreen();
	bool checkCollision1();
	bool checkCollision2();


public:
	void setDebugMode(bool d) { debug_mode = d; }
	bool getDebugMode() const { return debug_mode; }
	void setLevel(int l) { level = l; }
	int getLevel() { return level; }

	void update();
	void draw();
	void init();
	Game();
	~Game();
};
