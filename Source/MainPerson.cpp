#include "../Include/MainPerson.h"

MainPerson::MainPerson() :
	m_vertices(Quads, 4),
	RWalk("0_rightwalk"),
	LWalk("0_leftwalk"),
	RAtack("0_rightatack"),
	LAtack("0_leftatack")
{
	m_vertices[0].position = Vector2f(10, 330);
	m_vertices[1].position = Vector2f(80, 330);
	m_vertices[2].position = Vector2f(80, 454);
	m_vertices[3].position = Vector2f(10, 454);

	m_vertices[0].texCoords = Vector2f(0, 0);
	m_vertices[1].texCoords = Vector2f(709 / 6.0, 0);
	m_vertices[2].texCoords = Vector2f(709 / 6.0, 106);
	m_vertices[3].texCoords = Vector2f(0, 106);
}

void MainPerson::load(const string & p, float x, float width, float high)
{
	move(Vector2f(x - getPosition().x, 0));

	m_vertices[0].position = Vector2f(x, 454 - high);
	m_vertices[1].position = Vector2f(x + width, 454 - high);
	m_vertices[2].position = Vector2f(x + width, 454);
	m_vertices[3].position = Vector2f(x, 454);

	m_texture.loadFromFile("Media/person/" + p + ".png");

	m_vertices[0].texCoords = Vector2f(0, 0);
	m_vertices[1].texCoords = Vector2f(709 / 6.0, 0);
	m_vertices[2].texCoords = Vector2f(709 / 6.0, 106);
	m_vertices[3].texCoords = Vector2f(0, 106);

	LWalk.load(p + "_leftwalk", x, width, high);
	RWalk.load(p + "_rightwalk", x, width, high);
	LAtack.load(p + "_leftatack", x, width, high);
	RAtack.load(p + "_rightatack", x, width, high);

	setOrigin(Vector2f(x - 10, 0));
}


/////////////////////////////////////////////////////////
void MainPerson::Jumping()
{
	isJumping = true;
}
void MainPerson::notJumping()
{
	isJumping = false;
}
void MainPerson::MovingLeft()
{
	turnleft();
	isMovingLeft = true;
	standing = false;
	face_to_right = false;
}
void MainPerson::notMovingLeft()
{
	isMovingLeft = false;
	standing = true;
}
void MainPerson::MovingRight()
{
	turnright();
	isMovingRight = true;
	standing = false;
	face_to_right = true;
}
void MainPerson::notMovingRight()
{
	isMovingRight = false;
	standing = true;
}
void MainPerson::Atacking()
{
	atacking = true;
}
void MainPerson::notAtacking()
{
	atacking = false;
}
void MainPerson::turnright()
{
	face_to_right = true;
	m_vertices[0].texCoords = Vector2f(0, 0);
	m_vertices[1].texCoords = Vector2f(709 / 6.0, 0);
	m_vertices[2].texCoords = Vector2f(709 / 6.0, 106);
	m_vertices[3].texCoords = Vector2f(0, 106);
}
void MainPerson::turnleft()
{
	face_to_right = false;
	m_vertices[0].texCoords = Vector2f(709 / 6.0, 0);
	m_vertices[1].texCoords = Vector2f(709 / 3.0, 0);
	m_vertices[2].texCoords = Vector2f(709 / 3.0, 106);
	m_vertices[3].texCoords = Vector2f(709 / 6.0, 106);
}
bool MainPerson::isAlive()
{
	return HP > 0;
}

int MainPerson::getHP()
{
	return HP;
}

void MainPerson::harm(MainPerson& p, int atk)
{
	p.HP -= atk;
}
/////////////////////////////////////////////////////////


bool MainPerson::atack_to(MainPerson& p, Time dt)
{
	//攻速
	Time dtt = clock.restart();
	timeSinceLastUpdate += dtt;
	if (timeSinceLastUpdate > nearatack_frame)
	{
		timeSinceLastUpdate = Time::Zero;
		canAtack = true;
	}
	else
		canAtack = false;
	//

	Vector2f movement(0.f, 0.f);
	Vector2f p_pos = p.getPosition();
	Vector2f pos = getPosition();

	if (
		((face_to_right && p_pos.x > pos.x) || (!face_to_right && p_pos.x < pos.x))
		&& fabs(p_pos.y - pos.y) < 50 && fabs(p_pos.x - pos.x) < 50
		)
	{
		isMovingLeft = false;
		isMovingRight = false;
		atacking = true;
		if (canAtack)
		{
			p.HP -= ATK;
			canAtack = false;
		}
		canAtack = false;
		return true;
	}
	else
	{
		atacking = false;

		if (face_to_right && p_pos.x < pos.x)
			turnleft();
		else if (!face_to_right && p_pos.x > pos.x)
			turnright();

		if (p_pos.x - pos.x > 50)
		{
			movement.x += speed;
			isMovingRight = true;
			isMovingLeft = false;
		}
		else if(pos.x - p_pos.x > 50)
		{
			movement.x -= speed;
			isMovingLeft = true;
			isMovingRight = false;
		}
	}

	move(movement * dt.asSeconds());
	return false;
}


void MainPerson::remoteAtack()
{
	/*/攻速
	Time dtt = clock.restart();
	timeSinceLastUpdate += dtt;

	if (timeSinceLastUpdate > atack_frame)
	{
		timeSinceLastUpdate = Time::Zero;
		canAtack = true;
	}
	else
		canAtack = false;
	/*/

	//if (canAtack)
	//{
		Power power;
		atacking = true;
		power.load("dark", getPosition().x, getPosition().y, face_to_right ? 1 : -1);
		Remote.push_back(power);
	//}
}

void MainPerson::shenyuan_atack(MainPerson& p, Time dt)
{
	//攻速
	Time dtt = clock.restart();
	timeSinceLastUpdate += dtt;
	if (timeSinceLastUpdate > nearatack_frame)
	{
		timeSinceLastUpdate = Time::Zero;
		canAtack = true;
	}
	else
		canAtack = false;
	//

	Vector2f movement(0.f, 0.f);
	Vector2f p_pos = p.getPosition();
	Vector2f pos = getPosition();

	if ((face_to_right && p_pos.x > pos.x) ||
		(!face_to_right && p_pos.x < pos.x))
	{
		int a = rand() % 100;
		if (a < 10)
			remoteAtack();
	}

	if (canAtack)
	{
		canAtack = false;
		int a = rand() % 2;
		if (a == 1)
		{
			int b = rand() % 2;
			if(b==1)
				move(Vector2f(-getPosition().x + p.getPosition().x - 100
					, -getPosition().y + p.getPosition().y));
			else
				move(Vector2f(-getPosition().x + p.getPosition().x - 100
					, 330 - getPosition().y));
			turnright();
		}
		else
		{
			int b = rand() % 2;
			if(b == 1)
				move(Vector2f(-getPosition().x + p.getPosition().x + 100
					, -getPosition().y + p.getPosition().y));
			else
				move(Vector2f(-getPosition().x + p.getPosition().x + 100
					, 330-getPosition().y));
			turnleft();
		}
		remoteAtack();
	}
	else
	{
		if (p_pos.x - pos.x > 50)
		{
			movement.x += speed;
			isMovingRight = true;
			isMovingLeft = false;
		}
		else if (pos.x - p_pos.x > 50)
		{
			movement.x -= speed;
			isMovingLeft = true;
			isMovingRight = false;
		}
	}
}


////////////////////////////////////////////////////////

//人物总更新
void MainPerson::update(Time dt)
{
	LWalk.update(dt);
	RWalk.update(dt);
	LAtack.update(dt);
	RAtack.update(dt);

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

	updateMovement(dt);
}

//更新玩家位置
void MainPerson::updateMovement(Time dt)
{
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
		standing = false;
	}
	if (isMovingRight)
	{
		movement.x += speed;
		face_to_right = true;
		standing = false;
	}

	//正在降落
	if (foot_position < 454)
	{
		movement.y += DROP_SPEED;
		drop_y += DROP_SPEED;
	}
	//改变脚的位置
	foot_position += drop_y * dt.asSeconds();

	move(movement * dt.asSeconds());
	//cout << "x:"<<getPosition().x << endl;
}