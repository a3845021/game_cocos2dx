#pragma once
#include "cocos2d.h"
#include "Entity.h"
#include "DateManager.h"
#include "SceneManager.h"
#include "AudioManager.h"
using namespace cocos2d;
class SceneStart :public Layer {
public:
	static Scene * createScene();
	CREATE_FUNC(SceneStart);
	virtual bool init();

	Node* node_UI;
	Sprite* _title;

	Node* node_menu_level;
	Node* node_menu_settings;

	void initUI();

	void initTouch();

	void update(float dt);

	void ShowStar(Vec2 pos);

	void ShowMeteor();

	//�����������½����ˣ���ֱ�Ӹ��ƴ����ˣ�������Ŀ���Ƽ���ôд
	float timer_star;
	float time_star;
	float timer_star1;
	float time_star1;
	float timer_star2;
	float time_star2;
	void CreateStarByRandom(float dt);
	void CreateStarByRandom1(float dt);
	void CreateStarByRandom2(float dt);

	//����ͬ��
	float timer_meteor;
	float time_meteor;
	float timer_meteor1;
	float time_meteor1;
	void CreateMeteorByRandom(float dt);
	void CreateMeteorByRandom1(float dt);
private:
	Vector<Entity*> vec_todestroy;
public:
	//��UI�йص�һЩ����
	void OpenPlanet();
	void OpenStation();
	void ReturnToSpace();

	float timer_click;
	float time_click;
	bool can_click;
	void updateClick(float dt);
	void DisableClick(float time);
};