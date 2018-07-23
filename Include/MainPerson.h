#pragma once
#include "BasePerson.h"
#include "Animation.h"
#include "Power.h"
#include "Data.h"
using namespace sf;
using namespace std;

namespace PersonState
{
	enum ID
	{
		Monster,
		Friend
	};
}


//基础人物类
class MainPerson :
	public BasePerson
{
public:
	MainPerson();
	void load(const string & p, float x, float width, float high);

	//动作
	Animation RWalk, LWalk, RAtack, LAtack;
	//关于攻速
	Clock clock, nearclock;
	Time timeSinceLastUpdate, tslu;
	Time atack_frame, nearatack_frame;
	bool canAtack, cannearAtack;
	//属性
	int HP, ATK, nearATK;
	float jump_speed, speed, drop_speed;
	int level;
	PersonState::ID personstate;
	//移动，朝向
	bool isMovingLeft, isMovingRight, isJumping;
	bool face_to_right, standing;
	bool atacking, nearatacking;
	//落脚点
	float foot_position;
	//纹理、顶点数组
	VertexArray m_vertices;
	Texture m_texture;

public:
	//奇怪的函数
	void MovingLeft();
	void notMovingLeft();
	void MovingRight();
	void notMovingRight();
	void Jumping();
	void notJumping();
	void Atacking();
	void notAtacking();
	void nearAtacking()
	{
		nearatacking = true;
	}
	void notnearAtacking()
	{
		nearatacking = false;
	}
	bool isnearAtacking()
	{
		return nearatacking;
	}
	bool isAlive();
	int getHP();
	int getATK()
	{
		return ATK;
	}
	int getnearATK()
	{
		return nearATK;
	}
	void setHP(int hp)
	{
		HP = hp;
	}
	void setATK(int atk)
	{
		ATK = atk;
	}
	void setnearATK(int atk)
	{
		nearATK = atk;
	}

	void turnright();
	void turnleft();

	void harm(MainPerson& p, int atk);
	void changeHP(int i)
	{
		HP = i;
	}
public:
	//远程攻击
	vector<Power> Remote;

	//更新人物状态
	void updateMovement(Time dt);
	void update(Time dt);


	bool atack_to(MainPerson& p, Time dt);
	void shenyuan_atack(MainPerson& p, Time dt);
	void remoteAtack();


	//绘画再屏幕上
	virtual void draw(RenderTarget& target, RenderStates states) const
	{
		states.transform *= getTransform();
		if (atacking)
		{
			if (face_to_right)
				target.draw(RAtack, states);
			else
				target.draw(LAtack, states);
		}	
		else
		{
			if (standing)
			{
				states.texture = &m_texture;
				target.draw(m_vertices, states);
			}
			else
			{
				if (isMovingRight)
					target.draw(RWalk, states);
				else if (isMovingLeft)
					target.draw(LWalk, states);
			}
		}
	}

};