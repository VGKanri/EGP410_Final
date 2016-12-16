#include "ChangeRoomMessage.h"
#include "GameApp.h"
#include "Grid.h"
#include "GridVisualizer.h"
#include "UnitManager.h"
#include "SoundManager.h"


ChangeRoomMessage::ChangeRoomMessage(int index) :
GameMessage(CHANGE_ROOM_MESSAGE)
{
	mIndex = index;
}

ChangeRoomMessage::~ChangeRoomMessage()
{

}

void ChangeRoomMessage::process()
{
	int key = gpGameApp->getGrid()->getValueAtIndex(mIndex);

	gpGameApp->getGridVisualizer()->switchGrid(gpGameApp->getGrid()->getLink(key));
	gpGameApp->changeCurrentRoom(gpGameApp->getGrid()->getLink(key));	

	//set player position
	gpGameApp->getUnitManager()->getPlayer()->setVelocity(Vector2D(0, 0));
	gpGameApp->getUnitManager()->getPlayer()->setPosition(gpGameApp->getGrid()->getULCornerOfSquare(mIndex));
	gpGameApp->getUnitManager()->getPlayer()->resetCollider();
	gpGameApp->getUnitManager()->getPlayer()->changeState(PlayerState::IDLE);

	//update enemy logic
	gpGameApp->getUnitManager()->setEnemyActive(gpGameApp->getGrid());

	//update sound
	//gpGameApp->getSoundManager()->playSoundEffect(STAIR_KEY);
}