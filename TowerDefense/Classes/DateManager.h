#pragma once
#include "RecordManager.h"
class DataManager {
public:
	void init();

	//����װ�ˣ���̬����
	static int level_current;
	static int num_monster;
	
	static int money_current;
	static int hp_current;


	//��Ϸ������ʼ��������
	static void initGame();

	//�����־û�������
	static int num_kill;
	static int num_win;
	static void initRecord();
	static void saveRecord();
};