#include "player2.h"
#include "graphics.h"
#include "game.h"
#include "ball.h"

Player2::Player2(const Game& mygame)
	:GameObject(mygame)
{
	
}

void Player2::update()
{

	if (graphics::getKeyState(graphics::SCANCODE_UP))
	{
		pos2_y -= speed * graphics::getDeltaTime() / 10.0f;
	}
	if (graphics::getKeyState(graphics::SCANCODE_DOWN))
	{
		pos2_y += speed * graphics::getDeltaTime() / 10.0f;
	}

	if (pos2_y < 0) pos2_y = 0;
	if (pos2_y > CANVAS_HEIGHT) pos2_y = CANVAS_HEIGHT;
}

void Player2::draw()
{
	graphics::Brush br;
	br.fill_color[0] = 0.5f;
	br.fill_color[1] = 0.0f;
	br.fill_color[2] = 0.0f;
	br.fill_secondary_color[0] = 1.95f;
	br.fill_secondary_color[1] = 0.0f;
	br.fill_secondary_color[2] = 0.0f;
	br.outline_opacity = 0.0f;
	br.fill_opacity = 0.5f;
	br.fill_secondary_opacity = 0.5f;
	br.gradient = true;
	br.gradient_dir_u = 1.0f;
	br.gradient_dir_v = 0.0f;
	graphics::drawRect(pos2_x, pos2_y, 25, 100, br);
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
		graphics::drawRect(hull.cx, hull.cy, 25, 100, br);
	}
}

void Player2::init()
{
}

Rect Player2::getCollisionHull() const
{
	Rect rect;
	rect.cx = pos2_x;
	rect.cy = pos2_y;
	rect.width = 25;
	rect.height = 100;
	return rect;
}
