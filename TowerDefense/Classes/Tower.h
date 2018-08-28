#pragma once
#include "Entity.h"
#include "Ammo.h"
#include "AudioManager.h"
class Tower :public Entity {
private:
	int _cost;
	float _cd;
	float _timer;

	//�ӵ�����
	ValueVector vv_ammo;
	ValueVector vv_ammo_file;

	int _type;
public:
	Vec2 vec_local;
	Vec2 vec_offset_fire;

	Tower();
	~Tower();
	static Tower* create();
	
	void fire(float dt,Vec2 dir,Vector<Ammo*> &vec_ammo,Layer* scene,int order);

	//���ӵ�
	void BindAmmoByInfo(ValueVector vv,ValueVector vv_file);
	//������ֵ
	void SetValuesByInfo(ValueVector vv);

	int GetCost();

	void SetType(int type);
};
