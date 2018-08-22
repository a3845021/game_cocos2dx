#pragma once
#include "Entity.h"
#include "Pos.h"
class Monster :public Entity {
private:
	int _hp;
	int _speed;
	Vector<Pos*> _path;
	int index_target;

	//Ѫ��
	Sprite* sprite_hp;
	Sprite* sprite_hp_bg;
public:
	Monster();
	~Monster();
	static Monster* createByPath(Vector<Pos*> path);
	void moveByPath(float dt);

	//��Ѫ��
	void BindHp(std::string path,std::string path1);
};