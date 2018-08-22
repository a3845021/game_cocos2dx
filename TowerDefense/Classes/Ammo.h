#pragma once
#include "Entity.h"
class Ammo :public Entity {
private:
	int _damage;
	int _speed;
	Vec2 _dir;

	//�Ƿ�ʱ�����˺�
	bool is_delay;
	//�Ƿ��Ѿ���ײ
	bool is_active;
public:
	Ammo();
	~Ammo();
	static Ammo* create(Vec2 vec);
	void SetValues(int damage, int speed,Vec2 dir);
	void SetDir(Vec2 dir);
	void moveAmmo(float dt);

	//��ײ
	bool coled();
};