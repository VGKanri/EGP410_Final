#include "SpawnEnemyMessage.h"
#include "Enemy.h"

SpawnEnemyMessage::SpawnEnemyMessage(Enemy* enemy)
:GameMessage(SPAWN_ENEMY_MESSAGE)
{
	mEnemy = enemy;
}

SpawnEnemyMessage::~SpawnEnemyMessage()
{

}

void SpawnEnemyMessage::process()
{
	mEnemy->respawn();
}