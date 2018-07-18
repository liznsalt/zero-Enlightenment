#include "Person.h"


Person::Person() 
{
	money = 1000;
	HP = 50; 
	level = 1; 
	ATK = 2;
	nearATK = 4;
	//攻击频率要调
	atack_frame = seconds(1.f / 2.f); 
	nearatack_frame = seconds(1.f / 2.f);
	timeSinceLastUpdate = tslu = Time::Zero;
	jump_speed = 500; 
	speed = 250; 
	drop_speed = 1000;
	foot_position = 454;

	isMovingLeft = false;
	isMovingRight = false;
	isJumping = false;
	face_to_right = true;
	standing = true;
	canAtack = true;

	atacking = false;
	nearatacking = true;

	m_vertices[0].position = Vector2f(10, 330);
	m_vertices[1].position = Vector2f(80, 330);
	m_vertices[2].position = Vector2f(80, 454);
	m_vertices[3].position = Vector2f(10, 454);

	m_texture.loadFromFile("person/0.png");

	m_vertices[0].texCoords = Vector2f(0, 0);
	m_vertices[1].texCoords = Vector2f(709/6.0, 0);
	m_vertices[2].texCoords = Vector2f(709/6.0, 106);
	m_vertices[3].texCoords = Vector2f(0, 106);
}



//人物远程攻击
void Person::remoteAtack()
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
		Power power;
		atacking = true;
		power.load("normal", getPosition().x, getPosition().y, face_to_right ? 1 : -1);
		Remote.push_back(power);
	}
	//else
		//atacking = false;
}




//人物近战攻击
void Person::nearAtack()
{
	//攻速
	Time dtt = nearclock.restart();
	tslu += dtt;

	if (tslu > nearatack_frame)
	{
		tslu = Time::Zero;
		cannearAtack = true;
	}
	else
		cannearAtack = false;
	//
	if (cannearAtack)
	{
		atacking = true;
		nearAtacking();
	}
	else
	{
		notnearAtacking();
		//atacking = false;
	}
}

//位移
void Person::Shift()
{
	if (face_to_right)
		move(Vector2f(100, 0));
	else
		move(Vector2f(-100, 0));
}

void Person::upgrade()
{
	HP+=10;
	level++;
	ATK+=3;
	speed++;
}