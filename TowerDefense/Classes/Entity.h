#pragma once
#include "cocos2d.h"

#include "Pos.h"
using namespace cocos2d;
class Entity :public Layer{
private:
	Vec2 _pos;
	Sprite* _sprite;
	Animate* _anim;

	Vec2 pos_father;

	bool is_active;

	bool has_life;
	float time_life;
	float timer_life;
public:
	Entity();
	~Entity();
	static Entity* create(Pos* pos);
	bool init(Pos* pos);
	void BindSprite(std::string path);
	Sprite* GetSprite();
	//Ҫ�Ȱ�Sprite֮���ٰ�Animation����Ȼ��������ʾ������
	void BindAnimation(std::string name, int len,float time,Size size);
	//�󶨶���֮����Ҫ����
	void SetAnimationPlay(bool play,bool once=false);
	void SetSpriteSize(Size size);
	bool IsContains(Point pos);
	//�ƶ�
	void move(Vec2 dir, float dt);
	//���ø��ڵ������
	void SetPosFather(Vec2 pos);
	//��װactive
	void SetActive(bool active);
	bool GetActive();

	void updateLife(float dt);
	void Destroy(float delay);
};