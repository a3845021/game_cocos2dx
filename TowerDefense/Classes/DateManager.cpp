#include "DateManager.h"

void DataManager::init()
{
}

void DataManager::initGame()
{
	//���볡��ʱ�����ʼ���ؿ�
	//level_current = 0;
	num_monster = 0;
	
	money_current = 500;
	hp_current = 5;
}

void DataManager::initRecord()
{
	
}

void DataManager::saveRecord()
{
}

int DataManager::level_current = 0;
int DataManager::num_monster = 0;

int DataManager::money_current = 500;
int DataManager::hp_current = 5;