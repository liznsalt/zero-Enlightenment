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
计划
1.HELP的左边
2.Plot
3.Setting
*/


/*
不管是对战还是剧情，
都有主角、队友和敌人，分别是Player、(vector<Person>) teammate、monster，
所以ContinueGame()应该是先把上次的这三种角色画出来，然后回到相应函数
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

	//怪物和友军
	Clock updateClock;
	vector<Monster> monsters;
	vector<Person> friends;

	//更换帧率
	static const Time TIME_PER_FRAME;

	//游戏状态
	GameState::ID gamestate;
	PlotState::ID plotstate;

	RenderWindow window;//大小640x512
	Person Player;//709x106像素，人物大小70x124，位置10,330
	Scenes scenes;//640x512像素，大小640x512
	Scenes battleleft;
	Menu menu;//200x300像素，大小200x300
	View BattleView;//战场视角
	View minimapView;//小地图
	Scenes head;
	RectangleShape rectangle;//小地图边框
	Music backgroungMusic;//背景音乐

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
	
	//更新
	void update(Time dt);

	//画在window中，之后要加上display
	void render();
};