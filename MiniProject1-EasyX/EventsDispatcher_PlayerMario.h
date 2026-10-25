#pragma once

class EventsDispatcher_PlayerMario
{
private:
	bool IsFlagPulling;
public:
	EventsDispatcher_PlayerMario();
	bool GetIsFlagPulling();
	void SetIsFlagPulling(bool InputState);
};

