#pragma once
#include "Entity.h"
#include "Pos.h"
class Monster :public Entity {
private:
	int _speed;
	int _hp;
	Vector<Pos*> _path;
	int index_target;

	//Ѫ��
	Sprite* sprite_hp;
	Sprite* sprite_hp_bg;
	Vec2 anchor_hp;

	int hp_current;
	void ResizeHpSliderAndHp(int hp);
	void RefHp();
public:
	Monster();
	~Monster();
	static Monster* createByPath(Vector<Pos*> path);
	void moveByPath(float dt);

	//��Ѫ��
	void BindHp(std::string path,std::string path1,Vec2 offset);

	//���ò���
	void SetValuesByInfo(ValueVector vv);

	//�����˺�
	void TakeDamage(int damage);
};