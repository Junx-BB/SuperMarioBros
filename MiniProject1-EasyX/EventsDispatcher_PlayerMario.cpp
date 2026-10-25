#include "EventsDispatcher_PlayerMario.h"

EventsDispatcher_PlayerMario::EventsDispatcher_PlayerMario()
{
	IsFlagPulling = false;
}

bool EventsDispatcher_PlayerMario::GetIsFlagPulling()
{
	return IsFlagPulling;
}

void EventsDispatcher_PlayerMario::SetIsFlagPulling(bool InputState)
{
	IsFlagPulling = InputState;
}

