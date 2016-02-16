/*
 * graphicsobjectstorage_x11.cpp
 *
 *  Created on: Feb 16, 2016
 *      Author: janne
 */
#include "winhandling/graphicsobjectstorage_x11.h"

GraphicsObjectStorage_X11* GraphicsObjectStorage_X11::instance = nullptr;
std::mutex GraphicsObjectStorage_X11::instanceCreationMutex;

GraphicsObjectStorage_X11::GraphicsObjectStorage_X11()
{

}

GraphicsObjectStorage_X11* GraphicsObjectStorage_X11::GetApi()
{
	if(nullptr == instance)
	{
		instanceCreationMutex.lock();
		if(nullptr == instance)
		{
			instance = new GraphicsObjectStorage_X11();
		}
	}

	return instance;
}

void GraphicsObjectStorage_X11::AddObject(GraphicsObject_X11* _obj)
{
	objectsMap[_obj->GetObjectId()] = _obj;
}


void GraphicsObjectStorage_X11::Paint(Display* display, Window* win, int screenNo)
{
	IdToObjectPtrMapT::iterator objIter = objectsMap.begin();

	for( ; objIter != objectsMap.end(); ++objIter)
	{
		objIter->second->Paint(display, win, screenNo);
	}
}
