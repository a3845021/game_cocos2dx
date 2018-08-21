#pragma once
#include "Entity.h"
#include "Pos.h"
class Monster :public Entity {
private:
	int _hp;
	int _speed;
	Vector<Pos*> _path;
public:
	Monster();
	~Monster();
	static Monster* createByPath(Vector<Pos*> path);
};