#include "../Include/Boss.h"


Boss::Boss():
	m_vertices(Quads, 4)
{
	HP = 500;
	ATK = 2;
	face_to_right = true;
	timeSinceLastUpdate = Time::Zero;
	atack_frame = seconds(1.f / 0.2);
	canAtack = false;

	jump_speed = 800;
	speed = 200;
	isMovingLeft = false;
	isMovingRight = false;
	isJumping = false;

	foot_position = 454;

	m_vertices[0].position = Vector2f(0,0);
	m_vertices[1].position = Vector2f(640, 0);
	m_vertices[2].position = Vector2f(640,512);
	m_vertices[3].position = Vector2f(0,512);

	m_texture.loadFromFile("Media/boss/boss1.png");

	m_vertices[0].texCoords = Vector2f(0, 0);
	m_vertices[1].texCoords = Vector2f(640, 0);
	m_vertices[2].texCoords = Vector2f(640,512);
	m_vertices[3].texCoords = Vector2f(0, 512);
}

void Boss::load(const string& p)
{
	m_texture.loadFromFile("Media/boss/" + p + ".png");
}

void Boss::Shift()
{
	if (face_to_right)
		move(Vector2f(100, 0));
	else
		move(Vector2f(-100, 0));
}


void Boss::remoteAtack()
{
	//攻速
	Time dtt = clock.restart();
	timeSinceLastUpdate += dtt;

	if (timeSinceLastUpdate > atack_frame)
	{
		timeSinceLastUpdate = Time::Zero;
		canAtack = true;
	}
	else
		canAtack = false;
	//

	if (canAtack)
	{
		int a = rand();
		for (int i = 0; i < a % 25; i++)
		{
			Power power;
			int b = rand(), c=rand(), d=rand();
			power.load("point", getPosition().x + c%200, getPosition().y - d%500, b%2==1 ? 1 : -1);
			Remote.push_back(power);
		}
	}
}


void Boss::update(Time dt)
{
	//对于远程攻击的更新
	for (auto it = Remote.begin(); it != Remote.end();)
	{
		it->update(dt);
		//回收
		if (it->getPosition().x > 640 * 6 || it->getPosition().x < -640 * 6)
		{
			it = Remote.erase(it);
		}
		else
			it++;
	}

	Vector2f movement(0.f, 0.f);
	float drop_y = 0.f;
	//处理移动
	if (isJumping)
	{
		movement.y -= jump_speed;
		drop_y -= jump_speed;
	}
	if (isMovingLeft)
	{
		movement.x -= speed;
		face_to_right = false;
	}
	if (isMovingRight)
	{
		movement.x += speed;
		face_to_right = true;
	}

	if (foot_position < 454)
	{
		movement.y += DROP_SPEED;
		drop_y += DROP_SPEED;
	}
	foot_position += drop_y * dt.asSeconds();

	move(movement * dt.asSeconds());
}