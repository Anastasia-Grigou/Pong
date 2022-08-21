#include "player1.h"
#include "graphics.h"
#include "game.h"

Player1::Player1(const Game& mygame)
	:GameObject(mygame)
{
	init();
}

void Player1::update()
{
	
	if (graphics::getKeyState(graphics::SCANCODE_W))
	{
		pos1_y -= speed * graphics::getDeltaTime() / 10.0f;
	}
	if (graphics::getKeyState(graphics::SCANCODE_S))
	{
		pos1_y += speed * graphics::getDeltaTime() / 10.0f;
	}

	if(pos1_y < 0) pos1_y = 0;
	if(pos1_y > CANVAS_HEIGHT) pos1_y = CANVAS_HEIGHT; 
}

void Player1::draw()
{
	graphics::Brush br;
	br.fill_color[0] = 0.0f;
	br.fill_color[1] = 0.0f;
	br.fill_color[2] = 0.5f;
	br.fill_secondary_color[0] = 0.0f;
	br.fill_secondary_color[1] = 0.0f;
	br.fill_secondary_color[2] = 1.95f;
	br.outline_opacity= 0.0f;
	br.fill_opacity = 0.5f;
	br.fill_secondary_opacity = 0.5f;
	br.gradient = true;
	br.gradient_dir_u = 1.0f;
	br.gradient_dir_v = 0.0f;
	graphics::drawRect(pos1_x, pos1_y, 25, 100, br);
	graphics::resetPose();

	if (game.getDebugMode())
	{
		br.outline_opacity = 1.0f;
		br.texture = "";
		br.fill_color[0] = 0.3f;
		br.fill_color[1] = 1.0f;
		br.fill_color[2] = 0.3f;
		br.fill_opacity = 0.3f;
		br.gradient = false;
		Rect hull = getCollisionHull();
		graphics::drawRect(hull.cx, hull.cy,25, 100, br);
	}
}

void Player1::init()
{
}

Rect Player1::getCollisionHull() const
{
	Rect rect;
	rect.cx = pos1_x;
	rect.cy = pos1_y;
	rect.width = 25;
	rect.height = 100;
	return rect;
}
