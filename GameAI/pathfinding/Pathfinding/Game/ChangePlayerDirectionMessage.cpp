#include "ChangePlayerDirectionMessage.h"
#include "GameApp.h"
#include "UnitManager.h"

ChangePlayerDirectionMessage::ChangePlayerDirectionMessage(int direction)
:GameMessage(CHANGE_PLAYER_DIRECTION_MESSAGE)
,mDirection(direction)
{
}

ChangePlayerDirectionMessage::~ChangePlayerDirectionMessage()
{
}

void ChangePlayerDirectionMessage::process()
{
	//Add in get UnitManager Here and process direction change
	std::cout << "My direction is: " << mDirection << std::endl;
	switch (mDirection)
	{
	case 0:
		gpGameApp->getUnitManager()->getUnit("player")->setVelocity(Vector2D(0, -25));
		gpGameApp->getUnitManager()->getPlayer()->changeState(up);
		break;
	case 1:
		gpGameApp->getUnitManager()->getUnit("player")->setVelocity(Vector2D(25, 0));
		gpGameApp->getUnitManager()->getPlayer()->changeState(right_);
		break;
	case 2:
		gpGameApp->getUnitManager()->getUnit("player")->setVelocity(Vector2D(0, 25));
		gpGameApp->getUnitManager()->getPlayer()->changeState(down);
		break;
	case 3:
		gpGameApp->getUnitManager()->getUnit("player")->setVelocity(Vector2D(-25, 0));
		gpGameApp->getUnitManager()->getPlayer()->changeState(left_);
		break;
	}
}