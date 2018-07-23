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


//����������
class MainPerson :
	public BasePerson
{
public:
	MainPerson();
	void load(const string & p, float x, float width, float high);

	//����
	Animation RWalk, LWalk, RAtack, LAtack;
	//���ڹ���
	Clock clock, nearclock;
	Time timeSinceLastUpdate, tslu;
	Time atack_frame, nearatack_frame;
	bool canAtack, cannearAtack;
	//����
	int HP, ATK, nearATK;
	float jump_speed, speed, drop_speed;
	int level;
	PersonState::ID personstate;
	//�ƶ�������
	bool isMovingLeft, isMovingRight, isJumping;
	bool face_to_right, standing;
	bool atacking, nearatacking;
	//��ŵ�
	float foot_position;
	//������������
	VertexArray m_vertices;
	Texture m_texture;

public:
	//��ֵĺ���
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
	//Զ�̹���
	vector<Power> Remote;

	//��������״̬
	void updateMovement(Time dt);
	void update(Time dt);


	bool atack_to(MainPerson& p, Time dt);
	void shenyuan_atack(MainPerson& p, Time dt);
	void remoteAtack();


	//�滭����Ļ��
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