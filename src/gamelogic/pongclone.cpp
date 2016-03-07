/*
 * pongclone.cpp
 *
 *  Created on: Feb 17, 2016
 *      Author: janne
 */

#include "gamecore/gameobjectstorage_x11.h"
#include "gamelogic/pongclone.h"
#include "gamelogic/pongballgameobject.h"
#include "jobdispatcher/jobdispatcher.h"
#include "winhandling/graphicsevents.h"
#include "coord.h"

#include <iostream>

#define TEST_TIMEOUT_EVENT 0x00004500

PongClone::PongClone() :
gameObjectPtr(nullptr)
{
	//Testing purposes
	gameObjectPtr = new PongBallGameObject(Coord(90, 90), Coord(1, 1));

	JobDispatcher::GetApi()->SubscribeToEvent(TEST_TIMEOUT_EVENT, this);

	JobDispatcher::GetApi()->SubscribeToEvent(GRAPHICS_AVAIL_EVENT, this);

	JobDispatcher::GetApi()->RaiseEventIn(TEST_TIMEOUT_EVENT, nullptr, 100);
}

PongClone::~PongClone()
{
	JobDispatcher::GetApi()->UnsubscribeToEvent(TEST_TIMEOUT_EVENT, this);
	JobDispatcher::GetApi()->UnsubscribeToEvent(GRAPHICS_AVAIL_EVENT, this);
	GameObjectStorage_X11::GetApi()->DropInstance();

	std::cout<<"PongClone DTOR exiting"<<std::endl;
}

void PongClone::HandleEvent(const uint32_t eventNo, const EventDataBase* dataPtr)
{
	switch(eventNo)
	{
	case TEST_TIMEOUT_EVENT:
		GameObjectStorage_X11::GetApi()->Update();
		JobDispatcher::GetApi()->RaiseEvent(GRAPHICS_REDRAW_EVENT, nullptr);
		JobDispatcher::GetApi()->RaiseEventIn(TEST_TIMEOUT_EVENT, nullptr, 5);
		break;
	case GRAPHICS_AVAIL_EVENT:
		break;
	default:
		break;
	}
}
