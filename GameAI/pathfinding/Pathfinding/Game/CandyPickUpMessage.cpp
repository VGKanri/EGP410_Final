#include "CandyPickUpMessage.h"
#include "GameApp.h"
#include "Grid.h"
#include "UnitManager.h"
#include "SoundManager.h"

CandyPickUpMessage::CandyPickUpMessage(int index)
:GameMessage(CANDY_PICK_UP_MESSAGE)
{
	mIndex = index;
}

CandyPickUpMessage::~CandyPickUpMessage()
{

}

void CandyPickUpMessage::process()
{
	//update grid
	gpGameApp->getGrid()->setValueAtIndex(mIndex, CLEAR_VALUE);

	//update player
	gpGameApp->getUnitManager()->getPlayer()->setIsCandied(true);
	gpGameApp->getUnitManager()->getPlayer()->changeState(gpGameApp->getUnitManager()->getPlayer()->getPlayerState());
	gpGameApp->getUnitManager()->getPlayer()->resetCandyTimer();

	//update sound managaer
	gpGameApp->getSoundManager()->playSoundEffect(POWER_EFFECT_KEY);
	gpGameApp->getSoundManager()->stopSong();
	gpGameApp->getSoundManager()->playSong(POWER_UP_KEY);
}