#include "CoinPickUpMessage.h"
#include "GameApp.h"
#include "Grid.h"
#include "SoundManager.h"
#include "DebugDisplay.h"

CoinPickUpMessage::CoinPickUpMessage(int index)
:GameMessage(COIN_PICK_UP_MESSAGE)
{
	mIndex = index;
}

CoinPickUpMessage::~CoinPickUpMessage()
{
}

void CoinPickUpMessage::process()
{
	gpGameApp->getGrid()->setValueAtIndex(mIndex, CLEAR_VALUE);

	gpGameApp->getSoundManager()->playSoundEffect(COIN_KEY);

	gpGameApp->getDebugDisplay()->coinGot();
}