#include "../Include/Game.h"
#include "../Include/Data.h"

const Time Game::TIME_PER_FRAME = seconds(1.f / 20.f);

Game::Game() : 
	window(VideoMode(640, 512), L"����"),
	BattleView(FloatRect(0,0,640,512)),
	plotView(FloatRect(0, 0, 640, 512)),
	rectangle(Vector2f(160, 128))
{
	battlestate = BattleState::NORMAL;

	srand((unsigned)time(NULL));
	rectangle.setPosition(Vector2f(480, 0));
	rectangle.setFillColor(Color::White);
	rectangle.setOutlineThickness(1);
	rectangle.setOutlineColor(Color::Black);
	head.load("head", 1);
	battleleft.load("battleleft");
	battleleft.setPosition(Vector2f(-2560, 0));
	backgroungMusic.setVolume(50);

	for (int i = 0; i < 1; i++)
	{
		Monster monster;
		int a = rand() % 7;
		monster.load(to_string(a), 2560 - (rand() % 4) * 80, 70, 124);//70 x 124
		monsters.push_back(monster);
	}

	window.setVerticalSyncEnabled(true);
}


/**************************************************************/
/**************************************************************/


//��Ϸ���г���
void Game::run() 
{
	showHome();
}

//MOBA����
void Game::update(Time dt)
{
	Player.update(dt);
	BattleView.setCenter(Player.getPosition().x, 256);
	rectangle.setPosition(Player.getPosition().x + 160, 1);

	//���
	for (auto it1 = Player.Remote.begin(); it1 != Player.Remote.end(); )
	{
		auto it2 = shenyuan.begin();
		for (; it2 != shenyuan.end(); it2++)
		{
			float x = it1->getPosition().x, y = it1->getPosition().y;
			if (fabs(it2->getPosition().x - x) < 15
				&& y >= it2->getPosition().y - 70
				&& y <= it2->getPosition().y + 70)
			{
				it1 = Player.Remote.erase(it1);
				Player.harm(*it2, Player.getATK());
				cout << it2->HP << endl;
				break;
			}
		}
		if (it2 == shenyuan.end())
			it1++;
	}
	for (auto it1 = Player.Remote.begin(); it1 != Player.Remote.end(); )
	{
		auto it2 = monsters.begin();
		for (; it2 != monsters.end(); it2++)
		{
			float x = it1->getPosition().x, y = it1->getPosition().y;
			if (fabs(it2->getPosition().x - x) < 15
				&& y >= it2->getPosition().y - 70
				&& y <= it2->getPosition().y + 70)
			{
				it1 = Player.Remote.erase(it1);
				Player.harm(*it2, Player.getATK());
				break;
			}
		}
		if (it2 == monsters.end())
			it1++;
	}

	//��Ԩ
	for (auto it = shenyuan.begin(); it != shenyuan.end(); it++)
	{
		it->update(dt);
		for (auto it1 = it->Remote.begin();
			it1 != it->Remote.end(); )
		{
			float x = it1->getPosition().x,
				y = it1->getPosition().y;

			//�ȴ����
			if (fabs(Player.getPosition().x - x) < 15
				&& y >= Player.getPosition().y - 70
				&& y <= Player.getPosition().y + 70)
			{
				it1 = it->Remote.erase(it1);
				it->harm(Player, it->getATK());
				continue;
			}
			else
				it1++;
		}
	}


	//������ս����
	for (auto it = monsters.begin(); it != monsters.end(); it++)
	{
		if (Player.isnearAtacking() &&
			fabs(it->getPosition().x - Player.getPosition().x) < 10)
		{
			Player.harm(*it, Player.getnearATK());

			//cout << "ok" << endl;
		}
	}
	//

	//��������Ĺ���
	for (auto it = monsters.begin(); it != monsters.end();)
	{
		it->update(dt);
		if (!it->isAlive())
		{
			it = monsters.erase(it);
			Player.money += 10;
			cout << "��ֻ��������\n";
		}
		else
			it++;
	}
	for (auto it = shenyuan.begin(); it != shenyuan.end();)
	{
		it->update(dt);
		if (!it->isAlive())
		{
			it = shenyuan.erase(it);
			Player.money += 1000;
			cout << "��Ԩ��������\n";
		}
		else
			it++;
	}

	//����������
	if (!Player.isAlive())
	{
		cout << "�������" << endl;
		scenes.load("battle");
		battleleft.load("battleleft");
		battlestate = BattleState::NORMAL;
		for (auto it = shenyuan.begin(); it != shenyuan.end();)
		{
			it = shenyuan.erase(it);
		}

		Player.addHP(50);
		Player.move(Vector2f(-Player.getPosition().x
			, -Player.getPosition().y ));
	}

}

//����ս��
void Game::MOBA()
{
	backgroungMusic.openFromFile("Media/music/moba.ogg");
	backgroungMusic.play();

	gamestate = GameState::FIGHT;

	//��Ҫ���Ͻ�ɫ������

	Clock clock;
	Time timeSinceLastUpdate = Time::Zero;

	while (window.isOpen())
	{
		Time dt = clock.restart();
		timeSinceLastUpdate += dt;

		while (timeSinceLastUpdate > TIME_PER_FRAME)
		{
			timeSinceLastUpdate -= TIME_PER_FRAME;
			handleEvents(Player);
			//
			AI();
			update(TIME_PER_FRAME);
		}

		window.setView(BattleView);
		render();
		window.display();

		//cout << Player.getPosition().x << endl;
	}
}

//��ϷAI
void Game::AI()
{
	if (battlestate == BattleState::NORMAL)
	{
		while (monsters.size() < 1)
		{
			Monster monster;
			int a = rand() % 7;
			monster.load(to_string(a), 2560 - (rand() % 4) * 80, 70, 124);//70 x 124
			monsters.push_back(monster);
		}
	}

	//
	for (auto it1 = monsters.begin(); it1 != monsters.end(); it1++)
	{
			it1->atack_to(Player, TIME_PER_FRAME);
	}
	//


	//��ԨAI
	for (auto it1 = shenyuan.begin(); it1 != shenyuan.end(); it1++)
	{
		it1->shenyuan_atack(Player, TIME_PER_FRAME);
	}

}

//����,֮��Ҫdisplay��ǰҪ�涨��ͼ
void Game::render()
{
	if(battlestate==BattleState::NORMAL)
		window.clear(Color::White);
	else
		window.clear();

	window.draw(scenes);
	window.draw(battleleft);

	//��������
	for (auto it = monsters.begin(); it != monsters.end(); it++)
	{
		window.draw(*it);
	}

	for (auto it = shenyuan.begin(); it != shenyuan.end(); it++)
	{
		window.draw(*it);
		vector<Power>& q = it->Remote;
		for (auto it1 = q.begin(); it1 != q.end(); it1++)
		{
			window.draw(*it1);
		}
	}

	//��������͹���
	window.draw(Player);
	vector<Power>& p = Player.Remote;
	for (auto it = p.begin(); it != p.end(); it++)
		window.draw(*it);

	//С��ͼ�߿�
	if (battlestate==BattleState::NORMAL)
		window.draw(rectangle);

	//д������
	Font font;
	font.loadFromFile("Media/font/attribute.ttf");
	Text text;
	text.setFont(font);
	string attr = "HP:";
	int hp = Player.getHP(),atk=Player.getATK(),level=Player.getLevel();
	attr += to_string(hp);
	attr += "  ATK:";
	attr += to_string(atk);
	attr += "/";
	attr += to_string(Player.getnearATK());
	attr += "  Lv:";
	attr += to_string(level);
	attr += "  Money:" + to_string(Player.money);
	text.setString(attr);
	if(battlestate==BattleState::NORMAL)
		text.setFillColor(Color::Black);
	else
		text.setFillColor(Color::White);
	text.setCharacterSize(15);
	text.setPosition(Vector2f(Player.getPosition().x - 320, 484));
	window.draw(text);

	//�˵�ͼ��
	head.setPosition(Vector2f(Player.getPosition().x-320, 0));
	window.draw(head);

	//���桢�


	//��ʾ


	//minimap
	if (battlestate == BattleState::NORMAL)
	{
		minimapView.setCenter(1280, 256);
		minimapView.setViewport(FloatRect(0.75f, 0, 0.25f, 0.25f));
		window.setView(minimapView);
		window.draw(scenes);
		window.draw(Player);
		for (auto it = p.begin(); it != p.end(); it++)
			window.draw(*it);
		for (auto it = monsters.begin(); it != monsters.end(); it++)
			window.draw(*it);
	}
}



/**************************************************************/
/**************************************************************/


//����,��BOSS
void Game::RPG()
{
	gamestate = GameState::PLOT;
	//ѡ��ؿ�
	Scenes choose;
	choose.load("rpgchoose", 640, 512);
	choose.setPosition(Vector2f(0, 0));

	Font font;
	font.loadFromFile("Media/font/home.ttf");
	Text text[4];
	for (int i = 0; i < 4; i++)
	{
		text[i].setFont(font);
		text[i].setCharacterSize(20);
		text[i].setFillColor(Color::Black);
		text[i].setOrigin(text[i].getOrigin().x + text[i].getGlobalBounds().width / 2, text[i].getOrigin().y);
		text[i].setPosition(Vector2f(256, 132));
	}
	text[0].setString("Just Fight");
	text[1].setString("Developing");
	text[2].setString("Developing");
	text[3].setString("Developing");
	int state = -1;
	RectangleShape shape;

	Button b[5];
	b[0].set(147, 161, 289, 223);
	b[1].set(354, 162, 495, 224);
	b[2].set(148, 275, 292, 335);
	b[3].set(355, 277, 495, 334);

	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
			if (event.type == Event::KeyPressed)
			{
				switch (event.key.code)
				{
				case Keyboard::Escape:
					showHome();
					break;
				default:
					break;
				}
			}

			Vector2i localPosition = Mouse::getPosition(window);
			float x = localPosition.x, y = localPosition.y;

			for (int i = 0; i<4; i++)
				if (b[i].ispressed(localPosition))
				{
					state = i;
				}
			//cout << x << ' ' << y << endl;
			if (Mouse::isButtonPressed(Mouse::Left))
			{
				for (int i = 0; i<4; i++)
					if (b[i].ispressed(localPosition))
					{
						chapter(i + 1);
					}
			}
		}

		window.clear(Color::White);
		window.draw(choose);

		if (state != -1)
			window.draw(text[state]);
		//�����߿���������
		window.display();
	}
}

void Game::restart()
{
	if (plotstate == PlotState::CHAPTER1)
	{
		plotPlayer.setPosition(Vector2f(0, 0));
		boss.HP = 100;
		chapter1();
	}
	else if(plotstate == PlotState::CHAPTER2)
	{
		chapter2();
	}
}

void Game::chapter(int i)
{
	if (i == 1)
		chapter1();
	else if (i == 2)
		chapter2();
}

void Game::chapter1()
{
	plotstate = PlotState::CHAPTER1;

	Scenes plot;
	plot.load("chapter1");
	if (boss.HP == 0)
		boss.HP = 100;

	Clock clock;
	Time timeSinceLastUpdate = Time::Zero;

	while (window.isOpen())
	{
		Time dt = clock.restart();
		timeSinceLastUpdate += dt;

		while (timeSinceLastUpdate > TIME_PER_FRAME)
		{
			timeSinceLastUpdate -= TIME_PER_FRAME;
			Event event;

			handleEvents(plotPlayer);

			//update
			plotupdate(TIME_PER_FRAME);
		}
		//render
		plotrender();
	}
}

void Game::chapter2()
{
	EasyPerson easyperson;


}

void Game::plotupdate(Time dt)
{
	plotView.setCenter(plotPlayer.getPosition().x, 256);

	vector<Power>& p = plotPlayer.Remote;
	for (auto it = p.begin(); it != p.end(); )
	{
		float l = boss.getPosition().x, r = l + 512;
		float x = it->getPosition().x;
		if (fabs(x - l) <= 5 || fabs(x - r) <= 5 || (x<r&&x>l))
		{
			boss.gethurt(plotPlayer.getATK());
			cout << "�������boss��\n";

			it = p.erase(it);
		}
		else
			it++;
	}

	vector<Power>& q = boss.Remote;
	for (auto it = q.begin(); it != q.end();)
	{
		float l = plotPlayer.getPosition().x, r = l + 70;
		float u = plotPlayer.getPosition().y, d = u + 124;
		float x = it->getPosition().x, y = it->getPosition().y;
		if (x <= r && x >= l && y <= d && y >= u - 80)
		{
			plotPlayer.gethurt(boss.ATK);
			cout << "�㱻������\n";
			it = q.erase(it);
		}
		else
			it++;
	}

	//�����ˣ�����������������
	if (boss.HP <= 0 || plotPlayer.getHP() <= 0)
	{
		Scenes vic;
		vic.load("victory", 640, 512);
		vic.setPosition(Vector2f(plotPlayer.getPosition().x - 320, 0));
		while (window.isOpen())
		{
			Event event;
			while (window.pollEvent(event))
			{
				if (event.type == Event::Closed)
					window.close();
				if (event.type == Event::KeyPressed)
					showHome();
				if (Mouse::isButtonPressed(Mouse::Left))
					showHome();
			}
			window.draw(vic);
			window.display();
		}
	}

	boss.remoteAtack();

	boss.update(TIME_PER_FRAME);
	plotPlayer.update(TIME_PER_FRAME);
}

void Game::plotrender()
{
	window.setView(plotView);
	window.clear(Color::White);
	window.draw(boss);
	window.draw(plotPlayer);

	vector<Power>& p = plotPlayer.Remote;
	for (auto it = p.begin(); it != p.end(); it++)
		window.draw(*it);

	vector<Power>& q = boss.Remote;
	for (auto it = q.begin(); it != q.end(); it++)
		window.draw(*it);

	Font font;
	font.loadFromFile("Media/font/attribute.ttf");
	Text text;
	text.setFont(font);
	string attr = "My HP:";
	attr += to_string(plotPlayer.getHP()) + "  BOSS HP:" + to_string(boss.HP);
	text.setString(attr);
	text.setFillColor(Color::Black);
	text.setCharacterSize(15);
	text.setPosition(Vector2f(plotPlayer.getPosition().x - 320, 484));
	window.draw(text);

	window.display();
}



/**************************************************************/
/**************************************************************/

//����
void Game::showSetting()
{
	//��������ֱͬ������
	//���Ѫ������ս������Զ�̹���
	Scenes setting;
	setting.load("setting", 640, 512);
	setting.setPosition(Vector2f(0, 0));

	int voice = backgroungMusic.getVolume(), hp = Player.getHP(), atk = Player.getATK();

	Font font;
	font.loadFromFile("Media/font/home.ttf");
	Text text[3];
	for (int i = 0; i < 3; i++)
	{
		text[i].setFont(font);
		text[i].setCharacterSize(24);
		text[i].setFillColor(Color::Black);
	}
	text[0].setPosition(Vector2f(470, 150));
	text[1].setPosition(Vector2f(470, 250));
	text[2].setPosition(Vector2f(470, 304));
	text[0].setString(to_string(voice));
	text[1].setString(to_string(hp));
	text[2].setString(to_string(Player.getATK()));

	double t1 = 100.5 / (436 - 162), t2 = 80.5 / (436 - 162), t3 = 21.0 / (436 - 162);
	Scenes point[3];
	point[0].load("point", 1);
	point[1].load("point", 1);
	point[2].load("point", 1);
	
	point[0].setPosition(Vector2f(voice / t1 + 162, 157));
	point[1].setPosition(Vector2f(hp / t2 + 162, 259));
	point[2].setPosition(Vector2f(atk / t3 + 162, 309));



	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();

			if (event.type == Event::KeyPressed)
			{
				switch (event.key.code)
				{
				case Keyboard::Escape:
					if (gamestate == GameState::HOME)
						showHome();
					else
						showMenu();
					break;
				default:
					break;
				}
			}

			if (Mouse::isButtonPressed(Mouse::Left))
			{
				Vector2i localPosition = Mouse::getPosition(window);
				//cout << localPosition.x << ' ' << localPosition.y << endl;

				float x = localPosition.x, y = localPosition.y;

				if (x >= 162 && x <= 436)
				{
					if (fabs(y - 166) <= 10)
					{
						voice = t1 * (x - 162);
						point[0].setPosition(Vector2f(x, 157));
					}
					else if (fabs(y - 268) <= 10)
					{
						hp = t2 * (x - 162);
						point[1].setPosition(Vector2f(x, 259));
					}
					else if (fabs(y - 318) <= 10)
					{
						atk = t3 * (x - 162);
						point[2].setPosition(Vector2f(x, 309));
					}
				}
			}

		}

		changeAttr(voice, hp, atk);
		text[0].setString(to_string(voice));
		text[1].setString(to_string(hp));
		text[2].setString(to_string(Player.getATK()));
		//����
		if (gamestate == GameState::HOME)
		{
			setting.setPosition(Vector2f(0, 0));
			window.draw(setting);
			for (int i = 0; i < 3; i++)
				window.draw(text[i]);
			for (int i = 0; i < 3; i++)
				window.draw(point[i]);
		}
		else
		{
			text[0].setPosition(Vector2f(Player.getPosition().x + 470 - 320, 150));
			text[1].setPosition(Vector2f(470+ Player.getPosition().x - 320, 250));
			text[2].setPosition(Vector2f(470+ Player.getPosition().x - 320, 304));
			setting.setPosition(Vector2f(Player.getPosition().x - 320, 0));
			//
			point[0].setPosition(Vector2f(voice / t1 + 162 + Player.getPosition().x - 320, 157));
			point[1].setPosition(Vector2f(hp / t2 + 162 + Player.getPosition().x - 320, 259));
			point[2].setPosition(Vector2f(atk / t3 + 162 + Player.getPosition().x - 320, 309));
			window.setView(BattleView);
			window.draw(setting);
			for (int i = 0; i < 3; i++)
				window.draw(text[i]);
			for (int i = 0; i < 3; i++)
				window.draw(point[i]);
		}

		//
		window.display();
	}
}

void Game::changeAttr(int voice, int hp, int atk)
{
	backgroungMusic.setVolume(voice);
	Player.setHP(hp);
	Player.setATK(atk);
}


//�̵�
void Game::showStore()
{
	cout << "���̵�" << endl;

	Scenes store;
	store.load("store", 640, 512);
	store.setPosition(Vector2f(Player.getPosition().x - 320, 0));

	Font font;
	font.loadFromFile("Media/font/store.ttf");
	Text text[2];//���ơ�����
	for (int i = 0; i < 2; i++)
	{
		text[i].setFont(font);
		text[i].setCharacterSize(15);
		text[i].setFillColor(Color::Black);
	}
	text[0].setPosition(Vector2f(Player.getPosition().x + 155, 180));
	text[1].setPosition(Vector2f(Player.getPosition().x + 155, 310));

	int state = -1;
	Prop a[4];
	a[0].set("God Blood", "HP+10", 100);
	a[1].set("God Arm", "ATK+10", 100);
	//
	Button b[6];
	b[0].set(140, 155, 220, 210);
	b[1].set(265, 155, 345, 210);
	b[2].set(140, 265, 220, 325);
	b[3].set(265, 265, 345, 325);
	b[4].set(487, 415, 551, 451);
	b[5].set(589, 20,  622,  44);

	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();

			if (event.type == Event::KeyPressed)
				if (event.key.code == Keyboard::Escape)
					MOBA();

			if (Mouse::isButtonPressed(Mouse::Left))
			{
				Vector2i localPosition = Mouse::getPosition(window);
				int x = localPosition.x, y = localPosition.y;

				if (b[5].ispressed(localPosition))
					MOBA();

				for (int i = 0; i < 4; i++)
				{
					if (b[i].ispressed(localPosition))
					{
						text[0].setString(a[i].name);
						text[1].setString(a[i].discribe);
						state = i;
					}
				}
				
				if (b[4].ispressed(localPosition) && state != -1)
				{
					if (Player.money >= a[state].value)
					{
						Player.add(a[state]);
						Player.subMoney(a[state].value);
						cout << "����ɹ�\n";
					}
					else
					{
						cout << "����\n";
					}
				}
			}
		}
		//
		
		//cout << store.getPosition().x << endl;
		window.setView(BattleView);
		window.draw(store);

		for (int i = 0; i < 2; i++)
			window.draw(text[i]);

		//����

		window.display();
	}

}

//��Ʒ��
void Game::showInventory()
{
	cout << "����Ʒ��" << endl;

	Scenes inventory;
	inventory.load("inventory", 640, 512);
	inventory.setPosition(Vector2f(Player.getPosition().x - 320, 0));

	Font font;
	font.loadFromFile("Media/font/store.ttf");
	Text text[3];//���ơ�����
	for (int i = 0; i < 3; i++)
	{
		text[i].setFont(font);
		text[i].setCharacterSize(24);
		text[i].setFillColor(Color::Black);
	}
	text[0].setPosition(Vector2f(Player.getPosition().x -170, 225));
	text[1].setPosition(Vector2f(Player.getPosition().x + 30, 225));
	text[2].setPosition(Vector2f(Player.getPosition().x + 200, 225));

	int state = -1;
	Prop a[4];
	a[0].set("God Blood", "HP+10",100);
	a[1].set("God Arm", "ATK+10", 100);
	Button b[5];
	b[0].set(206, 62, 297, 108);
	b[1].set(350, 65, 440, 112);
	b[2].set(517, 429, 585, 462);
	b[3].set(591, 26, 617, 46);
	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();

			if (event.type == Event::KeyPressed)
				if (event.key.code == Keyboard::Escape)
					MOBA();

			if (Mouse::isButtonPressed(Mouse::Left))
			{
				Vector2i localPosition = Mouse::getPosition(window);
				int x = localPosition.x, y = localPosition.y;

				if (b[3].ispressed(localPosition))
					MOBA();

				for (int i = 0; i < 2; i++)
				{
					if (b[i].ispressed(localPosition))
					{
						text[0].setString(a[i].name);
						text[1].setString(a[i].discribe);
						text[2].setString(to_string(Player.hasThis(a[i].name)));
						state = i;
					}
				}

				if (b[2].ispressed(localPosition) && state != -1)
				{
					if (Player.hasThis(a[state].name) >= 1)
					{
						Player.sub(a[state]);
						if (state == 0)
							Player.addHP(10);
						else if (state == 1)
							Player.addATK(10);

						cout << "ʹ�óɹ�\n";
					}
				}
				//cout << x << ' ' << y << endl;
			}
		}
		//

		//cout << store.getPosition().x << endl;
		window.setView(BattleView);
		window.draw(inventory);

		for (int i = 0; i < 3; i++)
			window.draw(text[i]);

		//����

		window.display();
	}
}


//�Ǳ�
void Game::showCastle()
{
	
	if (battlestate == BattleState::NORMAL)
	{
		cout << "����Ǳ�\n";
		scenes.load("shenyuan");
		battleleft.load("shenyuanleft");
		battlestate = BattleState::SHENYUAN;

		for (auto it=monsters.begin();it!=monsters.end();)
		{
			it = monsters.erase(it);
		}

		for (int i = 0; i < 1; i++)
		{
			Monster monster;
			monster.nearatack_frame = seconds(1.f / 1.5);
			monster.HP = 50;
			monster.ATK = 1;

			int a = rand() % 4;
			while (a == 2)a = rand() % 4;

			monster.load(to_string(a), 2560 - (rand() % 4) * 80, 70, 124);//70 x 124
			shenyuan.push_back(monster);
		}
	}
	else
	{
		cout << "�뿪�Ǳ�\n";
		scenes.load("battle");
		battleleft.load("battleleft");
		battlestate = BattleState::NORMAL;

		for (auto it = shenyuan.begin(); it != shenyuan.end();)
		{
			it = shenyuan.erase(it);
		}
	}

	
}


//��ͼ
void Game::showMap()
{
	cout << "�򿪵�ͼ\n";
	Scenes map;
	map.load("map", 640, 512);
	map.setPosition(Vector2f(Player.getPosition().x - 320, 0));

	int state = -1;
	int a[3] = { -1200,10,-2100 };
	Button b[5];
	b[0].set(283, 146, 310,162);
	b[1].set(245, 321, 276, 338);
	b[2].set(431, 354, 500, 372);
	b[3].set(508, 425, 582, 460);
	b[4].set(589, 21, 622, 46);

	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
			if (event.type == Event::KeyPressed)
			{
				if (event.key.code == Keyboard::Escape)
					MOBA();
			}

			//
			Vector2i localPosition = Mouse::getPosition(window);
			int x = localPosition.x, y = localPosition.y;

			if (Mouse::isButtonPressed(Mouse::Left))
			{
				if (b[4].ispressed(localPosition))
					MOBA();

				for (int i = 0; i < 3; i++)
				{
					if (b[i].ispressed(localPosition))
						state = i;
				}

				if (b[3].ispressed(localPosition) && state != -1)
				{
					Player.move(Vector2f( a[state] - Player.getPosition().x, 
												0));

					MOBA();
				}

				//cout << x << ' ' << y << endl;
			}
		}

		window.setView(BattleView);
		window.draw(map);
		window.display();
	}


}

//��
void Game::showPao()
{
	cout << "����̨\n";

}

//��װ
void Game::showCloth()
{
	cout << "��װ" << endl;

	Scenes inventory;
	inventory.load("cloth", 640, 512);
	inventory.setPosition(Vector2f(Player.getPosition().x - 320, 0));

	int state = -1;
	Button b[6];
	b[0].set(135,147,273,222);
	b[1].set(375,148,516,223);
	b[2].set(134,265,273,334);
	b[3].set(373,268,517,338);
	b[4].set(490, 415, 572, 457);
	b[5].set(591, 27, 617, 48);

	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();

			if (event.type == Event::KeyPressed)
				if (event.key.code == Keyboard::Escape)
					MOBA();

			if (Mouse::isButtonPressed(Mouse::Left))
			{
				Vector2i localPosition = Mouse::getPosition(window);
				int x = localPosition.x, y = localPosition.y;

				if (b[5].ispressed(localPosition))
					MOBA();

				for (int i = 0; i < 4; i++)
					if (b[i].ispressed(localPosition))
						state = i;

				if (b[4].ispressed(localPosition) && state != -1)
				{
					cout << "��װ�ɹ�!" << endl;
					Player.load(to_string(state), Player.getPosition().x, 70, 124);
				}
				//cout << x << ' ' << y << endl;
			}
		}
		//

		//cout << store.getPosition().x << endl;
		window.setView(BattleView);
		window.draw(inventory);

		//����

		window.display();
	}

}



/**************************************************************/
/**************************************************************/



//��������
void Game::HELP()
{
	backgroungMusic.openFromFile("Media/music/help.ogg");
	backgroungMusic.play();


	gamestate = GameState::HELP;
	Clock clock;
	Time timeSinceLastUpdate = Time::Zero;

	Person player;
	Scenes help, helpleft;
	help.load("help");
	helpleft.load("helpleft");
	helpleft.setPosition(Vector2f(-2560, 0));
	View HelpView(FloatRect(0, 0, 640, 512));

	while (window.isOpen())
	{
		Time dt = clock.restart();
		timeSinceLastUpdate += dt;

		while (timeSinceLastUpdate > TIME_PER_FRAME)
		{
			timeSinceLastUpdate -= TIME_PER_FRAME;
			Event event;
			while (window.pollEvent(event))
			{
				switch (event.type)
				{
				case Event::KeyPressed:
				{
					switch (event.key.code)
					{
					case Keyboard::Escape:
						showHome();
						break;
					case Keyboard::Up:
						player.Jumping();
						break;
					case Keyboard::W:
						player.Jumping();
						break;
					case Keyboard::Space:
						player.Jumping();
						break;
					case Keyboard::Left:
						player.MovingLeft();
						break;
					case Keyboard::A:
						player.MovingLeft();
						break;
					case Keyboard::Right:
						player.MovingRight();
						break;
					case Keyboard::D:
						player.MovingRight();
						break;

					case Keyboard::LShift:
						player.Shift();
						break;
					case Keyboard::L:
						player.Shift();
						break;
					case Keyboard::J:
						player.nearAtack();
						break;
					case Keyboard::K:
						player.remoteAtack();
						break;
					default:
						break;
					}
				}
				break;

				case Event::KeyReleased:
				{
					switch (event.key.code)
					{
					case Keyboard::Up:
						player.notJumping();
						break;
					case Keyboard::W:
						player.notJumping();
						break;
					case Keyboard::Space:
						player.notJumping();
						break;
					case Keyboard::Left:
						player.notMovingLeft();
						break;
					case Keyboard::A:
						player.notMovingLeft();
						break;
					case Keyboard::Right:
						player.notMovingRight();
						break;
					case Keyboard::D:
						player.notMovingRight();
						break;
					case Keyboard::J:
						player.notnearAtacking();
						player.notAtacking();
						break;
					case Keyboard::K:
						player.notAtacking();
						break;
					default:
						break;
					}
				}
				break;

				case Event::Closed:
					window.close();
					break;
				default:
					break;
				}
			}

			//����
			player.update(TIME_PER_FRAME);
			HelpView.setCenter(player.getPosition().x, 256);
		}

		window.clear(Color::White);
		window.setView(HelpView);
		window.draw(help);
		window.draw(helpleft);
		window.draw(player);
		vector<Power>& p = player.Remote;
		
		for (auto it = p.begin(); it != p.end(); it++)
			window.draw(*it);

		for (auto it = p.begin(); it != p.end(); it++)
		{
			if (fabs(it->getPosition().x - -(2350)) <= 5)
				Error();
		}

		window.display();
	}
}
void Game::Error()
{
	/*
	Scenes error;
	error.load("error", 640, 512);
	error.setPosition(Vector2f(-2560, 0));
	window.draw(error);
	window.display();
	sleep(seconds(2));

	showHome();
	*/
}


//	HOME:
//		��ս
//		����
//		����
//		����
//		�˳�
void Game::showHome()
{
	gamestate = GameState::HOME;

	backgroungMusic.openFromFile("Media/music/home.ogg");
	backgroungMusic.play();

	Scenes home;
	home.load("home", 640, 512);

	Font font;
	font.loadFromFile("Media/font/home.ttf");

	Text text[5];
	text[0].setString(L"BATTLE");
	text[1].setString(L"PLOT");
	text[2].setString(L"HELP");
	text[3].setString(L"SETTING");
	text[4].setString(L"EXIT");
	for (int i = 0; i < 5; i++)
	{
		text[i].setFont(font);
		text[i].setFillColor(Color::Black);
		text[i].setCharacterSize(24);
		text[i].setOrigin(text[i].getOrigin().x + text[i].getGlobalBounds().width / 2, text[i].getOrigin().y);
	}

	text[0].setPosition(Vector2f(320, 120));
	text[1].setPosition(Vector2f(320, 185));
	text[2].setPosition(Vector2f(320, 250));
	text[3].setPosition(Vector2f(320, 315));
	text[4].setPosition(Vector2f(320, 380));

	HomeState::ID homestate;
	homestate = HomeState::FIGHT;


	while (window.isOpen())
	{
		//
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
			Vector2i localPosition = Mouse::getPosition(window);

			if (localPosition.x <= 400 && localPosition.x >= 240)
			{
				if (localPosition.y <= 120 + 20 && localPosition.y >= 120 - 20)
				{
					homestate = HomeState::FIGHT;
				}
				else if (localPosition.y <= 185 + 20 && localPosition.y >= 185 - 20)
				{
					homestate = HomeState::PLOT;
				}
				else if (localPosition.y <= 250 + 20 && localPosition.y >= 250 - 20)
				{
					homestate = HomeState::HELP;
				}
				else if (localPosition.y <= 315 + 20 && localPosition.y >= 315 - 20)
				{
					homestate = HomeState::SETTING;
				}
				else if (localPosition.y <= 380 + 20 && localPosition.y >= 380 - 20)
				{
					homestate = HomeState::EXIT;
				}
			}
			if (Mouse::isButtonPressed(Mouse::Left))
			{
				if (localPosition.x <= 400 && localPosition.x >= 240)
				{
					if (localPosition.y <= 120 + 20 && localPosition.y >= 120 - 20)
					{
						MOBA();
					}
					else if (localPosition.y <= 185 + 20 && localPosition.y >= 185 - 20)
					{
						RPG();
					}
					else if (localPosition.y <= 250 + 20 && localPosition.y >= 250 - 20)
					{
						HELP();
					}
					else if (localPosition.y <= 315 + 20 && localPosition.y >= 315 - 20)
					{
						showSetting();
					}
					else if (localPosition.y <= 380 + 20 && localPosition.y >= 380 - 20)
					{
						window.close();
					}
				}
			}
			

			if (event.type == Event::KeyPressed)
			{
				switch (event.key.code)
				{
				case Keyboard::W:
					if (homestate == HomeState::PLOT)
						homestate = HomeState::FIGHT;
					else if (homestate == HomeState::HELP)
						homestate = HomeState::PLOT;
					else if (homestate == HomeState::EXIT)
						homestate = HomeState::SETTING;
					else if (homestate == HomeState::SETTING)
						homestate = HomeState::HELP;
					break;
				case Keyboard::Up:
					if (homestate == HomeState::PLOT)
						homestate = HomeState::FIGHT;
					else if (homestate == HomeState::HELP)
						homestate = HomeState::PLOT;
					else if (homestate == HomeState::EXIT)
						homestate = HomeState::SETTING;
					else if (homestate == HomeState::SETTING)
						homestate = HomeState::HELP;
					break;
				case Keyboard::Down:
					if (homestate == HomeState::FIGHT)
						homestate = HomeState::PLOT;
					else if (homestate == HomeState::PLOT)
						homestate = HomeState::HELP;
					else if (homestate == HomeState::HELP)
						homestate = HomeState::SETTING;
					else if (homestate == HomeState::SETTING)
						homestate = HomeState::EXIT;
					break;
				case Keyboard::S:
					if (homestate == HomeState::FIGHT)
						homestate = HomeState::PLOT;
					else if (homestate == HomeState::PLOT)
						homestate = HomeState::HELP;
					else if (homestate == HomeState::HELP)
						homestate = HomeState::SETTING;
					else if (homestate == HomeState::SETTING)
						homestate = HomeState::EXIT;
					break;

				case Keyboard::Enter:
					if (homestate == HomeState::FIGHT)
					{
						MOBA();
					}
					else if (homestate == HomeState::PLOT)
					{
						RPG();
					}
					else if (homestate == HomeState::SETTING)
					{
						showSetting();
					}
					else if (homestate == HomeState::HELP)
					{
						HELP();
					}
					else if (homestate == HomeState::EXIT)
						window.close();
					break;
				case Keyboard::J:
					if (homestate == HomeState::FIGHT)
					{
						MOBA();
					}
					else if (homestate == HomeState::PLOT)
					{
						RPG();
					}
					else if (homestate == HomeState::SETTING)
					{
						showSetting();
					}
					else if (homestate == HomeState::HELP)
					{
						HELP();
					}
					else if (homestate == HomeState::EXIT)
						window.close();
					break;
				default:
					break;
				}
			}
		}

		//
		for (int i = 0; i < 5; i++)
		{
			if (i != homestate)
			{
				text[i].setFillColor(Color::Black);
			}
			else
			{
				text[i].setFillColor(Color::Cyan);
			}
		}
		//
		window.clear();
		BattleView.setCenter(320, 256);
		window.setView(BattleView);
		window.draw(home);
		for (int i = 0; i < 5; i++)
			window.draw(text[i]);
		window.display();
	}
}





/**************************************************************/
/**************************************************************/




//������Ϸ
void Game::ContinueGame()
{
	render();
	window.display();
	switch (gamestate)
	{
	case GameState::FIGHT:
		MOBA();
		break;
	case GameState::PLOT:
		if (plotstate == PlotState::CHAPTER1)
			chapter1();

		//
		break;
	case GameState::HELP:
		HELP();
		break;
	default:
		break;
	}
}

//չʾĿ¼
void Game::showMenu()
{
	if (gamestate == GameState::PLOT)
		return;

	menu.setPosition(Vector2f(Player.getPosition().x - 350, 0));

	Font font;
	font.loadFromFile("Media/font/menu.ttf");

	Text text[7];
	text[0].setString(L"CONTINUE");
	text[1].setString(L"HOME");
	text[2].setString(L"BATTLE");
	text[3].setString(L"PLOT");
	text[4].setString(L"HELP");
	text[5].setString(L"SETTING");
	text[6].setString(L"EXIT");
	for (int i = 0; i < 7; i++)
	{
		text[i].setFont(font);
		text[i].setFillColor(Color::Black);
		text[i].setCharacterSize(20);
		text[i].setOrigin(text[i].getOrigin().x + text[i].getGlobalBounds().width / 2, text[i].getOrigin().y);
	}

	text[0].setPosition(Vector2f(Player.getPosition().x - 250, 15));
	text[1].setPosition(Vector2f(Player.getPosition().x - 250, 60));
	text[2].setPosition(Vector2f(Player.getPosition().x - 250, 105));
	text[3].setPosition(Vector2f(Player.getPosition().x - 250, 150));
	text[4].setPosition(Vector2f(Player.getPosition().x - 250, 195));
	text[5].setPosition(Vector2f(Player.getPosition().x - 250, 240));
	text[6].setPosition(Vector2f(Player.getPosition().x - 250, 285));

	MenuState::ID menustate;
	menustate = MenuState::CONTINUE;


	while (window.isOpen())
	{
		//
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();

			Vector2i localPosition = Mouse::getPosition(window);

			if (localPosition.x <= 120 && localPosition.x >= 20)
			{
				int y = localPosition.y;
				if (y >= 15 - 20 && y <= 15 + 20)
				{
					menustate = MenuState::CONTINUE;
				}
				else if (y >= 60 - 20 && y <= 60 + 20)
				{
					menustate = MenuState::HOME;
				}
				else if (y >= 105 - 20 && y <= 105 + 20)
				{
					menustate = MenuState::FIGHT;
				}
				else if (y >= 150 - 20 && y <= 150 + 20)
				{
					menustate = MenuState::PLOT;
				}
				else if (y >= 195 - 20 && y <= 195 + 20)
				{
					menustate = MenuState::HELP;
				}
				else if (y >= 240 - 20 && y <= 240 + 20)
				{
					menustate = MenuState::SETTING;
				}
				else if (y >= 285 - 20 && y <= 285 + 20)
				{
					menustate = MenuState::EXIT;
				}
			}
			if (Mouse::isButtonPressed(Mouse::Left))
			{
				if (localPosition.x <= 20 && localPosition.y <= 20)
					ContinueGame();

				//
				if (localPosition.x <= 120 && localPosition.x >= 20)
				{
					int y = localPosition.y;
					if (y >= 15 - 20 && y <= 15 + 20)
					{
						ContinueGame();
					}
					else if (y >= 60 - 20 && y <= 60 + 20)
					{
						showHome();
					}
					else if (y >= 105 - 20 && y <= 105 + 20)
					{
						MOBA();
					}
					else if (y >= 150 - 20 && y <= 150 + 20)
					{
						RPG();
					}
					else if (y >= 195 - 20 && y <= 195 + 20)
					{
						HELP();
					}
					else if (y >= 240 - 20 && y <= 240 + 20)
					{
						showSetting();
					}
					else if (y >= 285 - 20 && y <= 285 + 20)
					{
						window.close();
					}
				}
			}

			

			if (event.type == Event::KeyPressed)
			{
				switch (event.key.code)
				{
				case Keyboard::Escape:
					ContinueGame();
					break;

				case Keyboard::W:
					if (menustate == MenuState::HOME)
						menustate = MenuState::CONTINUE;
					else if (menustate == MenuState::FIGHT)
						menustate = MenuState::HOME;
					else if (menustate == MenuState::PLOT)
						menustate = MenuState::FIGHT;
					else if (menustate == MenuState::HELP)
						menustate = MenuState::PLOT;
					else if (menustate == MenuState::EXIT)
						menustate = MenuState::SETTING;
					else if (menustate == MenuState::SETTING)
						menustate = MenuState::HELP;
					break;
				case Keyboard::Up:
					if (menustate == MenuState::HOME)
						menustate = MenuState::CONTINUE;
					else if (menustate == MenuState::FIGHT)
						menustate = MenuState::HOME;
					else if (menustate == MenuState::PLOT)
						menustate = MenuState::FIGHT;
					else if (menustate == MenuState::HELP)
						menustate = MenuState::PLOT;
					else if (menustate == MenuState::EXIT)
						menustate = MenuState::SETTING;
					else if (menustate == MenuState::SETTING)
						menustate = MenuState::HELP;
					break;
				case Keyboard::S:
					if (menustate == MenuState::CONTINUE)
						menustate = MenuState::HOME;
					else if (menustate == MenuState::HOME)
						menustate = MenuState::FIGHT;
					else if (menustate == MenuState::FIGHT)
						menustate = MenuState::PLOT;
					else if (menustate == MenuState::PLOT)
						menustate = MenuState::HELP;
					else if (menustate == MenuState::HELP)
						menustate = MenuState::SETTING;
					else if (menustate == MenuState::SETTING)
						menustate = MenuState::EXIT;
					break;
				case Keyboard::Down:
					if (menustate == MenuState::CONTINUE)
						menustate = MenuState::HOME;
					else if (menustate == MenuState::HOME)
						menustate = MenuState::FIGHT;
					else if (menustate == MenuState::FIGHT)
						menustate = MenuState::PLOT;
					else if (menustate == MenuState::PLOT)
						menustate = MenuState::HELP;
					else if (menustate == MenuState::HELP)
						menustate = MenuState::SETTING;
					else if (menustate == MenuState::SETTING)
						menustate = MenuState::EXIT;
					break;

				case Keyboard::Enter:
					if (menustate == MenuState::CONTINUE)
					{
						ContinueGame();
					}
					else if (menustate == MenuState::FIGHT)
					{
						MOBA();
					}
					else if (menustate == MenuState::PLOT)
					{
						RPG();
					}
					else if (menustate == MenuState::EXIT)
					{
						window.close();
					}
					else if (menustate == MenuState::HOME)
					{
						showHome();
					}
					else if (menustate == MenuState::HELP)
					{
						HELP();
					}
					else if (menustate == MenuState::SETTING)
					{
						showSetting();
					}
					break;
				case Keyboard::J:
					if (menustate == MenuState::CONTINUE)
					{
						ContinueGame();
					}
					else if (menustate == MenuState::FIGHT)
					{
						MOBA();
					}
					else if (menustate == MenuState::PLOT)
					{
						RPG();
					}
					else if (menustate == MenuState::EXIT)
					{
						window.close();
					}
					else if (menustate == MenuState::HOME)
					{
						showHome();
					}
					else if (menustate == MenuState::HELP)
					{
						HELP();
					}
					else if (menustate == MenuState::SETTING)
					{
						showSetting();
					}
					break;
				default:
					break;
				}
			}
		}

		//
		for (int i = 0; i < 7; i++)
		{
			if (i != menustate)
			{
				text[i].setFillColor(Color::Black);
			}
			else
			{
				text[i].setFillColor(Color::Cyan);
			}
		}
		//
		window.setView(BattleView);
		window.draw(menu);
		for (int i = 0; i < 7; i++)
			window.draw(text[i]);
		window.display();
		render();
	}
}


//emmmmmm
void Game::handleEvents(Person& p) 
{
    Event event;
    while (window.pollEvent(event)) 
	{
		//���⴦��
		if (gamestate == GameState::FIGHT)
		{
			if (Mouse::isButtonPressed(Mouse::Left))
			{
				Vector2i localPosition = Mouse::getPosition(window);
				if (localPosition.x <= 20 && localPosition.y <= 20)
					showMenu();
			}
		}

        switch (event.type) 
		{
		case Event::KeyPressed:
			handlePlayerInput(event.key.code, true, p);
			break;
		case Event::KeyReleased:
			handlePlayerInput(event.key.code, false, p);
			break;
        case Event::Closed:
            window.close();
            break;
		default:
			break;
        }
    }
}

void Game::handlePlayerInput(Keyboard::Key key, bool isPressed, Person& p)
{
	switch (key)
	{

	case Keyboard::Escape:
		if (isPressed)
		{
			if(gamestate==GameState::FIGHT)
				showMenu();
			//�ڹؿ��в˵�
			else if (gamestate == GameState::PLOT)
			{
				Scenes choose;
				choose.load("choose", 640, 512);
				choose.setPosition(Vector2f(plotPlayer.getPosition().x - 320, 0));
				while (window.isOpen())
				{
					Event event;
					while (window.pollEvent(event))
					{
						if (event.type == Event::Closed)
							window.close();
						if (event.type == Event::KeyPressed)
						{
							if (event.key.code == Keyboard::Escape)
								return;
						}
						if (Mouse::isButtonPressed(Mouse::Left))
						{
							Vector2i localPosition = Mouse::getPosition(window);
							float x = localPosition.x, y = localPosition.y;
							//cout << x << ' ' << y << endl;
							if (x >= 111 && x <= 224 && y >= 198 && y <= 246)
								return;
							else if (x >= 278 && x <= 382 && y >= 197 && y <= 254)
							{
								//
								restart();
							}
							else if (x >= 428 && x <= 525 && y >= 198 && y <= 251)
								showHome();
						}
					}
					window.draw(choose);
					window.display();
				}
			}
		}
		break;

	case Keyboard::F:
		//��..
		if (isPressed)
			if (gamestate == GameState::FIGHT)
			{
				if (Player.getPosition().x < -1050 && 
					Player.getPosition().x >= -1250)
				{
					showStore();
				}
				else if (Player.getPosition().x < -1950 && 
					Player.getPosition().x >= -2200)
				{
					showCastle();
				}
				else if (Player.getPosition().x < 120 &&
					Player.getPosition().x >= 0)
				{
					showPao();
				}
				//
			}
		break;

	case Keyboard::O:
		//�򿪱���
		if (isPressed)
			if (gamestate == GameState::FIGHT)
			{
				showCloth();
			}
		break;

	case Keyboard::P:
		//�򿪱���
		if (isPressed)
			if (gamestate == GameState::FIGHT)
			{
				showInventory();
			}
		break;

	case Keyboard::M:
		//�򿪵�ͼ
		if (isPressed)
			if (gamestate == GameState::FIGHT)
			{
				showMap();
			}
		break;

	case Keyboard::Up:
		if (isPressed)
			p.Jumping();
		else
			p.notJumping();
		break;
	case Keyboard::W:
		if (isPressed)
			p.Jumping();
		else
			p.notJumping();
		break;
	case Keyboard::Space:
		if (isPressed)
			p.Jumping();
		else
			p.notJumping();
		break;

	case Keyboard::Left:
		if (isPressed)
		{
			p.MovingLeft();
		}
		else
			p.notMovingLeft();
		break;
	case Keyboard::A:
		if (isPressed)
		{
			p.MovingLeft();
		}
		else
			p.notMovingLeft();
		break;

	case Keyboard::Right:
		if (isPressed)
		{
			p.MovingRight();
		}
		else
			p.notMovingRight();
		break;
	case Keyboard::D:
		if (isPressed)
		{
			p.MovingRight();
		}
		else
			p.notMovingRight();
		break;


	case Keyboard::S:
		break;

	case Keyboard::LShift:
		if (isPressed)
			p.Shift();
		break;
	case Keyboard::L:
		if (isPressed)
			p.Shift();
		break;

	case Keyboard::J:
		if (isPressed)
		{
			p.nearAtack();
			//
		}
		else
		{
			p.notAtacking();
			p.notnearAtacking();
		}
		break;
	case Keyboard::K:
		if (isPressed)
		{
			p.remoteAtack();
		}
		else
			p.notAtacking();
		break;

	default:
		break;
	}
}