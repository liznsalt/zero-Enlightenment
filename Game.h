#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include "Person.h"
#include "Scenes.h"
#include "Menu.h"
#include "Boss.h"
#include "Button.h"
#include "Prop.h"
#include "Monster.h"
#include "EasyPerson.h"
using namespace std;
using namespace sf;

namespace HomeState
{
	enum ID
	{
		FIGHT,
		PLOT,
		HELP,
		SETTING,
		EXIT
	};
}

namespace MenuState
{
	enum ID
	{
		CONTINUE,
		HOME,
		FIGHT,
		PLOT,
		HELP,
		SETTING,
		EXIT
	};
}

namespace GameState
{
	enum ID
	{
		FIGHT,
		PLOT,
		HELP,
		HOME
	};
}

namespace PlotState
{
	enum ID
	{
		CHAPTER1,
		CHAPTER2
	};
}

/*
�ƻ�
1.HELP�����
2.Plot
3.Setting
*/


/*
�����Ƕ�ս���Ǿ��飬
�������ǡ����Ѻ͵��ˣ��ֱ���Player��(vector<Person>) teammate��monster��
����ContinueGame()Ӧ�����Ȱ��ϴε������ֽ�ɫ��������Ȼ��ص���Ӧ����
*/
class Game
{
	Person plotPlayer;
	View plotView;
	Boss boss;

public:
	void RPG();
	void chapter1();
	void chapter2();
	void restart();
	void chapter(int i);

	void plotrender();
	void plotupdate(Time dt);



private:

	//������Ѿ�
	Clock updateClock;
	vector<Monster> monsters;
	vector<Person> friends;

	//����֡��
	static const Time TIME_PER_FRAME;

	//��Ϸ״̬
	GameState::ID gamestate;
	PlotState::ID plotstate;

	RenderWindow window;//��С640x512
	Person Player;//709x106���أ������С70x124��λ��10,330
	Scenes scenes;//640x512���أ���С640x512
	Scenes battleleft;
	Menu menu;//200x300���أ���С200x300
	View BattleView;//ս���ӽ�
	View minimapView;//С��ͼ
	Scenes head;
	RectangleShape rectangle;//С��ͼ�߿�
	Music backgroungMusic;//��������

public:
	Game();

	void run();
	void showHome();
	void MOBA();
	void AI();

	void HELP();
	void Error();

	void ContinueGame();
	void showMenu();
	void showSetting();

	void showStore();
	void showInventory();
	void showCastle();
	void showMap();

	void changeAttr(int voice, int hp, int atk);

	void handleEvents(Person& p);
	void handlePlayerInput(Keyboard::Key key, bool isPressed, Person& p);
	
	//����
	void update(Time dt);

	//����window�У�֮��Ҫ����display
	void render();
};