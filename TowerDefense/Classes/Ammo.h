#pragma once
#include "Entity.h"
class Ammo :public Entity {
private:
	int _damage;
	int _speed;
	Vec2 _dir;

	//�Ƿ�ʱ�����˺�
	bool is_delay;

	//����Ч��
	int type_extra;

	float timer_life;
	float time_life;
	//�������Ч��
	bool is_wave;
	int range_wave;

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

	//����Ч��
	int GetExtraType();
	//�����
	bool IsWave();
	int GetWaveRange();
};