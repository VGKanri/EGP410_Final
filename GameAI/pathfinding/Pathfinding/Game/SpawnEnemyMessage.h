#pragma once

#include "GameMessage.h"

class Enemy;

class SpawnEnemyMessage :public GameMessage
{
public:
	SpawnEnemyMessage(Enemy* enemy);
	~SpawnEnemyMessage();

	void process();

private:
	Enemy* mEnemy;
};