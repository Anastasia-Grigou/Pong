#include "ball.h"
#include "graphics.h"
#include "config.h"
#include <random>
#include "util.h"
#include "game.h"


void Ball::update()
{
	pos_x += speed * dir_x;
	pos_y -= (speed) * dir_y;
	rotation += 0.1f * graphics::getDeltaTime();
	rotation = fmodf(rotation, 360);
}

void Ball::draw()
{
	graphics::setOrientation(rotation);
	brush.texture = std::string(ASSET_PATH) + "moon.png";
	brush.outline_opacity = 0.0f;
	graphics::drawRect(pos_x, pos_y, size, size, brush);
	graphics::resetPose();

	if (game.getDebugMode())
	{
		graphics::Brush br;
		br.outline_opacity = 1.0f;
		br.texture = "";
		br.fill_color[0] = 1.0f;
		br.fill_color[1] = 0.3f;
		br.fill_color[2] = 0.3f;
		br.fill_opacity = 0.3f;
		br.gradient = false;
		Disk hull = getCollisionHull();
		graphics::drawDisk(hull.cx, hull.cy, hull.radius, br);
	}
}


void Ball::init()
{
	pos_x = CANVAS_WIDTH / 2;
	pos_y = CANVAS_HEIGHT / 2;
	dir_x = -1.0f;
	dir_y = 0.0f;
	rotation = 360 * rand0to1();
	size = 30;
}

Disk Ball::getCollisionHull() const
{
	Disk disk;
	disk.cx = pos_x;
	disk.cy = pos_y;
	disk.radius = size * 0.46f;
	return disk;

}

Ball::Ball(const class Game& mygame)
	:GameObject(mygame)
{
	init();
}

Ball::~Ball()
{
}
