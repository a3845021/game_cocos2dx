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
public:
	Entity();
	~Entity();
	static Entity* create(Pos* pos);
	bool init(Pos* pos);
	void BindSprite(std::string path);
	//Ҫ�Ȱ�Sprite֮���ٰ�Animation����Ȼ��������ʾ������
	void BindAnimation(std::string name, int len,float time,Size size);
	//�󶨶���֮����Ҫ����
	void SetAnimationPlay(bool play);
	void SetSpriteSize(Size size);
	bool IsContains(Point pos);
	//�ƶ�
	void move(Vec2 dir, float dt);
	//���ø��ڵ������
	void SetPosFather(Vec2 pos);
};