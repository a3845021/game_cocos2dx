#include "SceneGame.h"
#include "Pos.h"
#include "Entity.h"
#include "TowerBase.h"
#include "Monster.h"
#include "Tower.h"
#include "ui/CocosGUI.h"
#include "ReaderJson.h"

using namespace ui;

#define ROWS (32)
#define COLS (18)

#define TOWERBASE_Z (5)
#define TOWER_Z (10)
#define MOSTER_Z (15)
#define AMMO_Z (16)
#define UI_Z (20)

Scene * SceneGame::createScene()
{
	auto scene = Scene::create();
	auto layer = SceneGame::create();
	scene->addChild(layer);
	return scene;
}

bool SceneGame::init()
{
	if (!Layer::init()) {
		return false;
	}
	//��ʼ���ڵ�
	initNode();
	//��ʼ��UI
	initUI();
	//��ʼ�����/����������
	initTouch();
	//��ʼ����ͼ
	initMap(0);
	
	Monster*
	test =(Monster*) Monster::createByPath(vec_path);
	test->BindSprite("TestAnim/test0.png");
	test->BindAnimation("TestAnim/test", 6,0.1f);
	test->SetAnimationPlay(true);
	this->addChild(test,MOSTER_Z);
	vec_monster.pushBack(test);

	//��update����
	this->schedule(schedule_selector(SceneGame::update));
}

void SceneGame::update(float dt)
{
	//�����ƶ�
	{
		int num_monster = vec_monster.size();
		for (int i = 0; i < num_monster; i++) {
			//vec_monster.at(i)->move(Vec2(50, 0), dt);
			vec_monster.at(i)->moveByPath(dt);
		}
	}
	//����������
	{
		int num_tower = vec_tower.size();
		for (int i = 0; i < num_tower; i++) {
			bool flag_fire = false;
			Vec2 dir_fire;
			//������й���
			{
				for (int j = 0; j < vec_monster.size(); j++) {
					float distance = vec_tower.at(i)->vec_local.distance(vec_monster.at(j)->getPosition());
					if (distance < 1000.0f) {
						flag_fire = true;
						dir_fire = Vec2(vec_tower.at(i)->vec_local, vec_monster.at(j)->getPosition());
						break;
					}
				}
			}
			if (flag_fire) {
				vec_tower.at(i)->fire(dt, Vec2(0, 30), dir_fire, vec_ammo, this, AMMO_Z);
			}
		}
	}
	//�ӵ��ƶ�
	{
		int num_ammo = vec_ammo.size();
		for (int i = 0; i < num_ammo; i++) {
			vec_ammo.at(i)->moveAmmo(dt);
		}
	}
}


void SceneGame::initNode()
{
	//��ʼ��UI_tower�ڵ�
	{
		if (node_UI_tower != NULL) {
			CC_SAFE_DELETE(node_UI_tower);
		}
		node_UI_tower = Node::create();
		this->addChild(node_UI_tower, UI_Z);
		node_UI_tower->setVisible(false);
	}
	
}

void SceneGame::initUI()
{
	//��ʼ��panel_tower
	{
		Entity* panel_tower = Entity::create(new Pos(0,1));
		panel_tower->BindSprite("TestUI/panel_tower.png");
		panel_tower->SetSpriteSize(Size(200, 80));
		panel_tower->setPosition(Vec2(0, 100));
		node_UI_tower->addChild(panel_tower, UI_Z);
		node_UI_tower->setVisible(false);
		
		Button* button = Button::create("TestUI/icon_tower.png", "TestUI/icon_tower.png", "TestUI/icon_tower.png");
		button->addTouchEventListener([&](Ref* sender, Widget::TouchEventType type) {
			if (type == ui::Widget::TouchEventType::ENDED) {
				//���ｨ���Ĺ���
				Tower* tower = Tower::create();
				tower->BindSprite("TestAnim/testtower0.png");
				tower->BindAnimation("TestAnim/testtower", 6,0.2f);
				tower->SetAnimationPlay(true);
				vec_towerbase.at(index_towerbase_selected)->SetTower(tower);
				//��ӵ�vec_towet����
				vec_tower.pushBack(tower);
			}
		});
		panel_tower->addChild(button);
	}
}

void SceneGame::initTouch()
{
	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = [](Touch* touch, Event* event) {
		//���/������ʼʱ
		return true;
	};
	listener->onTouchMoved = [](Touch* touch, Event* event) {
		//���/�������ƶ�ʱ
		return true;
	};
	listener->onTouchEnded = [&](Touch* touch, Event* event) {
		//���/��������ʱ
		Point pos = touch->getLocationInView();
		Point point = Director::getInstance()->convertToGL(pos);
		log("pos%f,%f", pos.x, pos.y);
		log("point%f,%f", point.x, point.y);
		DetectorVecTowebase(point);
		return true;
	};
	listener->setSwallowTouches(true);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

}

void SceneGame::initMap(int i)
{
	std::string path = String::createWithFormat("Maps/map%d.tmx", i)->getCString();
	if (_map != NULL) {
		CC_SAFE_DELETE(_map);
	}
	_map = TMXTiledMap::create(path);
	this->addChild(_map);
	//��GIDΪ0�ĵ�ͼ����ӿ��Ե���ĸ���
	for (int i = 0; i < ROWS; i++) {
		for (int j = 0; j < COLS; j++) {
			Pos* pos =new Pos(i, j);
			if (GetGridIndex(pos) == 0) {
				TowerBase* towerbase = TowerBase::create(pos, 0);
				towerbase->BindSprite("TestSprites/tower.png");
				this->addChild(towerbase,TOWERBASE_Z);
				vec_towerbase.pushBack(towerbase);
			}
		}
	}
	//��ȡ�������Ϣ�����·���ڵ�
	auto group_node_path = _map->getObjectGroup("path");
	auto vec_node_path = group_node_path->getObjects();
	int num = vec_node_path.size();
	for (unsigned int i = 0; i < num; i++) {
		auto node_path = vec_node_path.at(i).asValueMap();
		float posx = node_path.at("x").asFloat();
		float posy = node_path.at("y").asFloat();
		vec_path.pushBack(new Pos(posx, posy));
	}
}

int SceneGame::GetGridIndex(Pos* pos)
{
	auto maplayer = _map->getLayer("base");
	Vec2 vec = Vec2(pos->GetPosx(), COLS - 1 - pos->GetPosy());
	auto tileid = maplayer->getTileGIDAt(vec);
	return (int)tileid-1;
}

bool SceneGame::IsTowerbaseSelected(int index,Point point)
{
	TowerBase* towerbase = vec_towerbase.at(index);
	return towerbase->IsContains(point);
}

void SceneGame::DetectorVecTowebase(Point point)
{
	//flag���Ƿ�����Ч���
	bool flag_total = false;
	//����vec_towerbase���ж��Ƿ�����Towerbase
	int size = vec_towerbase.size();
	for (int i = 0; i < size; i++) {
		bool flag = IsTowerbaseSelected(i, point);
		if (flag) {
			flag_total = true;
			index_towerbase_selected = i;
			{
				Vec2 pos = vec_towerbase.at(i)->getPosition();
				node_UI_tower->setPosition(pos);
				node_UI_tower->setVisible(true);
			}
			
			log("selected: %d",i);
		}
		else {
			log("not selected: %d", i);
		}
	}
	//���������Ч�������ִ��
	if (!flag_total) {
		node_UI_tower->setVisible(false);
	}
}
