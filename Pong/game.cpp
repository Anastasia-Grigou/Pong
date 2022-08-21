#include "game.h"
#include "graphics.h"
#include "config.h"

void Game::spawnBall()
{
	if (!ball)
	{
		ball = new Ball(*this);
	};
}

void Game::checkBall()
{
	if (ball && !ball->isActive())
	{
		delete ball;
		ball = nullptr;
	}
}

void Game::updateStartScreen()
{
	if (graphics::getKeyState(graphics::SCANCODE_1))
	{
		setLevel(1);
		status = STATUS_PLAYING;
	}
	if (graphics::getKeyState(graphics::SCANCODE_2))
	{
		setLevel(2);
		status = STATUS_PLAYING;
	}
	if (graphics::getKeyState(graphics::SCANCODE_3))
	{
		setLevel(3);
		status = STATUS_PLAYING;
	}
	
}

void Game::updateLevelScreen()
{
	if (!player1_initialized && graphics::getGlobalTime() > 1000)
	{
		player1 = new Player1(*this);
		player1_initialized = true;
	}

	if (player1)
	{
		player1->update();
	}



	if (!player2_initialized && graphics::getGlobalTime() > 1000)
	{
		player2 = new Player2(*this);
		player2_initialized = true;
	}

	if (player2)
	{
		player2->update();
	}

	checkBall();
	spawnBall();

	if (getLevel() == 1)
	{
		ball->setSpeed(5.0f);
	}
	if (getLevel() == 2)
	{
		ball->setSpeed(10.0f);
	}
	if (getLevel() == 3)
	{
		ball->setSpeed(15.0f);
	}

	if (ball)
	{
		ball->update();
	}

	if (checkCollision1())
	{
		float t = ((ball->getPos_y() - player1->getPos1_y()) / player1 -> getPos1_x()) - 0.5f;
		ball->setDir_x(fabs(ball->getDir_x()));
		ball->setDir_y(t);
		graphics::playSound(std::string(ASSET_PATH) + "hit1.mp3", 0.4f, false);
	}
	if (checkCollision2())
	{
		float t = ((ball->getPos_y() - player2->getPos2_y()) / player2->getPos2_x()) - 0.5f;
		ball->setDir_x(-fabs(ball->getDir_x()));
		ball->setDir_y(t);
		graphics::playSound(std::string(ASSET_PATH) + "hit1.mp3", 0.4f, false);
	}

	if (ball->getPos_x() > CANVAS_WIDTH)
	{
		player1->addScore1();
		ball->setPos_x(CANVAS_WIDTH / 2);
		ball->setPos_y(CANVAS_HEIGHT / 2);
		ball->setDir_x(fabs(ball->getDir_x()));
		ball->setDir_y(0);
		graphics::playSound(std::string(ASSET_PATH) + "lose.mp3", 0.4f, false);
	}
	if (ball->getPos_x() < 0) 
	{
		player2->addScore2();
		ball->setPos_x(CANVAS_WIDTH / 2);
		ball->setPos_y(CANVAS_HEIGHT / 2);
		ball->setDir_x(-fabs(ball->getDir_x()));
		ball->setDir_y(0);
		graphics::playSound(std::string(ASSET_PATH) + "lose.mp3", 0.4f, false);
	}
	if (ball->getPos_y() > CANVAS_HEIGHT)
	{
		ball->setDir_y(fabs(ball->getDir_y()));
		graphics::playSound(std::string(ASSET_PATH) + "hit2.mp3", 0.4f, false);
	}
	if (ball->getPos_y() < 0)
	{
		ball->setDir_y(-fabs(ball->getDir_y()));
		graphics::playSound(std::string(ASSET_PATH) + "hit2.mp3", 0.4f, false);
	}

	if (player1->getScore1()== 10 || player2->getScore2()== 10)
	{
		status = STATUS_END;
		graphics::playSound(std::string(ASSET_PATH) + "win1.mp3", 0.4f, false);
	}
}

void Game::updateEndScreen()
{
	if (graphics::getKeyState(graphics::SCANCODE_RETURN))
	{
		player1->resetScore1() ;
		player2->resetScore2() ;
		status = STATUS_START;
	}
}

void Game::drawStartScreen()
{
	graphics::Brush br;
	br.texture = std::string(ASSET_PATH) + "stars.png";
	br.outline_opacity = 0.0f;
	br.gradient = true;
	br.gradient_dir_u = 1.0f;
	br.gradient_dir_v = 0.0f;

	//draw background 
	graphics::drawRect(CANVAS_WIDTH / 2, CANVAS_HEIGHT / 2, CANVAS_WIDTH, CANVAS_WIDTH, br);
	
	char info[40];
	sprintf_s(info, "easy (press 1)");
	graphics::drawText(375, 125, 50, info, br);
	sprintf_s(info, "medium (press 2)");
	graphics::drawText(350, 250, 50, info, br);
	sprintf_s(info, "hard(press 3)");
	graphics::drawText(375, 375, 50, info, br);

}

void Game::drawLevelScreen()
{
	graphics::Brush br;
	br.texture = std::string(ASSET_PATH) + "stars.png";
	br.outline_opacity = 0.0f;

	//draw background 
	graphics::drawRect(CANVAS_WIDTH / 2, CANVAS_HEIGHT / 2, CANVAS_WIDTH, CANVAS_WIDTH, br);

	//draw player1
	if (player1)
	{
		player1->draw();
	}

	//draw player2
	if (player2)
	{
		player2->draw();
	}

	if (ball)
	{
		ball->draw();
	}

	//UI/info layer
	if (player1 && player2)
	{
		char info1[40];
		sprintf_s(info1, "Player1    :    Player2");
		graphics::drawText(375, 50, 30, info1, br);
		char info2[40];
		sprintf_s(info2, "%d                         %d", player1->getScore1(), player2->getScore2());
		graphics::drawText(412, 75, 30, info2, br);
	}
}

void Game::drawEndScreen()
{
	graphics::Brush br;
	br.texture = std::string(ASSET_PATH) + "stars.png";
	br.outline_opacity = 0.0f;
	br.gradient = true;
	br.gradient_dir_u = 1.0f;
	br.gradient_dir_v = 0.0f;

	//draw background 
	graphics::drawRect(CANVAS_WIDTH / 2, CANVAS_HEIGHT / 2, CANVAS_WIDTH, CANVAS_WIDTH, br);

	br.texture = std::string(ASSET_PATH) + "confetti.png";
	br.outline_opacity = 0.0f;
	br.gradient = true;
	br.gradient_dir_u = 1.0f;
	br.gradient_dir_v = 0.0f;
	graphics::drawRect(CANVAS_WIDTH / 2, CANVAS_HEIGHT / 2, CANVAS_WIDTH, CANVAS_WIDTH, br);

	char info1[40];
	sprintf_s(info1, "winner");
	graphics::drawText(375, 150, 100, info1, br);

	if (player1->getScore1()== 10)
	{
		char info[40];
		sprintf_s(info, "player1");
		graphics::drawText(410, 300, 63, info, br);
	}
	else if (player2->getScore2() == 10)
	{
		char info[40];
		sprintf_s(info, "player2");
		graphics::drawText(410, 300, 63, info, br);
	}

	char info[40];
	sprintf_s(info, "press enter to play again");
	graphics::drawText(330, 475, 35, info, br);
}

bool Game::checkCollision1()
{
	if (!player1 || !ball)
	{
		return false;
	}
	
	Rect r1 = player1->getCollisionHull();
	Disk d1 = ball->getCollisionHull();

	float dx = abs(d1.cx - r1.cx);
	float dy = abs(d1.cy - r1.cy);

	if (dx > (r1.width / 2 + d1.radius))
	{
		return false;
	}
	if (dy > (r1.height / 2 + d1.radius))
	{
		return false;
	}
	if (dx <= (r1.width / 2))
	{
		return true;
	}
	if (dy <= (r1.height / 2))
	{
		return true;
	}
	float corner = (dx - r1.width / 2) * (dx - r1.width / 2) + (dy - r1.height / 2) * (dy - r1.height / 2);
	return(corner <= (d1.radius * d1.radius));
	
}

bool Game::checkCollision2()
{
	if (!player2 || !ball)
	{
		return false;
	}

	Rect r2 = player2->getCollisionHull();
	Disk d2 = ball->getCollisionHull();

	float dx = abs(d2.cx - r2.cx);
	float dy = abs(d2.cy - r2.cy);

	if (dx > (r2.width / 2 + d2.radius))
	{
		return false;
	}
	if (dy > (r2.height / 2 + d2.radius))
	{
		return false;
	}
	if (dx <= (r2.width / 2))
	{
		return true;
	}
	if (dy <= (r2.height / 2))
	{
		return true;
	}
	float corner = (dx - r2.width / 2) * (dx - r2.width / 2) + (dy - r2.height / 2) * (dy - r2.height / 2);
	return(corner <= (d2.radius * d2.radius));
}

void Game::update()
{
	if (status == STATUS_START)
	{
		updateStartScreen();
	}
	else if (status == STATUS_PLAYING)
	{
		updateLevelScreen();
	}
	else if (status == STATUS_END)
	{
		updateEndScreen();
	}
}

void Game::draw()
{
	if (status == STATUS_START)
	{
		drawStartScreen();
	}
	else if (status == STATUS_PLAYING)
	{
		drawLevelScreen();
	}
	else if (status == STATUS_END)
	{
		drawEndScreen();
	}

	
}

void Game::init()
{
	graphics::setFont(std::string(ASSET_PATH) + "font.ttf");
	graphics::playMusic(std::string(ASSET_PATH) + "music.mp3", 0.15f, true, 4000);
}

Game::Game()
{
}

Game::~Game()
{
	if (player1)
	{
		delete player1;
	}
	if (player2)
	{
		delete player2;
	}
}
