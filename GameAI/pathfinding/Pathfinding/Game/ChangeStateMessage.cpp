#include "ChangeStateMessage.h"

ChangeStateMessage::ChangeStateMessage(GameState state)
:GameMessage(CHANGE_MENU_SELECTION_MESSAGE)
,mState(state)
{
}

void ChangeStateMessage::process()
{
	gpGameApp->setState(mState);
}