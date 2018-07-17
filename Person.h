#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/OpenGL.hpp>
#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <string>
#include <cassert>
#include "Data.h"
#include "Animation.h"
#include "Power.h"
#include "Boss.h"
#include "Prop.h"
#include "Inventory.h"
#include "MainPerson.h"
using namespace sf;
using namespace std;


class Person:
	public MainPerson
{
public:
	Person();

	//Ǯ
	int money;
	//������Ʒ
	Inventory inventory;
	void sub(Prop& p)
	{
		inventory.sub(p);
	}
	void add(Prop& p)
	{
		inventory.add(p);
	}
	int hasThis(string name)
	{
		return inventory.cnt(name);
	}
	void subMoney(int n)
	{
		money -= n;
	}
	void addHP(int hp)
	{
		HP += hp;
	}
	void addATK(int atk)
	{
		ATK += atk;
	}
	//��ս����
	void nearAtack();

	void gethurt(int atk)
	{
		HP -= atk;
	}

	int getLevel()
	{
		return level;
	}
	void set(PersonState::ID p)
	{
		personstate = p;
	}
	PersonState::ID getPersonState()
	{
		return personstate;
	}

	//Զ�̹���
	void remoteAtack();
	//����
	void Shift();
	//����
	void upgrade();
};