#pragma once
#include "Entity.h"
class Ammo :public Entity {
private:
	int _damage;
	int _speed;
	Vec2 _dir;

	//�Ƿ�ʱ�����˺�
	bool is_delay;

	float timer_life;

public:
	Ammo();
	~Ammo();
	static Ammo* create(Vec2 vec);
	void SetDir(Vec2 dir);
	void updateAmmo(float dt);

	//��ײ
	bool coled();
	int GetDamage();

	//�����ӵ���ֵ
	void SetValuesByInfo(ValueVector vv);
};