/*
 * winapi_x11.cpp
 *
 *  Created on: Feb 15, 2016
 *      Author: janne
 */

#include "winhandling/winapi_x11.h"
#include "winhandling/graphicsobject_x11.h"
#include "winhandling/graphicsobjectstorage_x11.h"
#include "winhandling/graphicsevents.h"

#include "jobdispatcher/jobdispatcher.h"

#include <iostream>

WinApi_X11::WinApi_X11(const Coord& _winSize) :
winSize(_winSize),
displayPtr(nullptr),
screenNo(-1),
running(false)
{
	XInitThreads();
	displayPtr = XOpenDisplay(NULL);

	screenNo = DefaultScreen(displayPtr);

	window = XCreateSimpleWindow(displayPtr,
								 RootWindow(displayPtr, screenNo),
								 10,
								 10,
								 winSize.GetX(),
								 winSize.GetY(),
								 1,
	                             BlackPixel(displayPtr, screenNo),
								 WhitePixel(displayPtr, screenNo));

	XSelectInput(displayPtr,
			     window,
				 ExposureMask |
				 KeyPressMask |
				 ButtonPressMask |
				 ButtonReleaseMask);

    XMapWindow(displayPtr, window);

    XStoreName(displayPtr, window, "Janne 2D Engine");

	WM_DELETE_WINDOW = XInternAtom(displayPtr, "WM_DELETE_WINDOW", False);

	XSetWMProtocols(displayPtr, window, &WM_DELETE_WINDOW, 1);

	//Testing purposes... Remove me
	GraphicsObjectString_X11* testString = new GraphicsObjectString_X11(Coord(20, 20), "Hej");

	JobDispatcher::GetApi()->SubscribeToEvent(GRAPHICS_AVAIL_EVENT, this);

	JobDispatcher::GetApi()->SubscribeToEvent(GRAPHICS_WIN_RESIZE_EVENT, this);

	JobDispatcher::GetApi()->RaiseEvent(GRAPHICS_AVAIL_EVENT, nullptr);

	//Testing purposes... Remove me
	JobDispatcher::GetApi()->RaiseEvent(GRAPHICS_WIN_RESIZE_EVENT, new WinResizeEventData(Coord(400, 400)));
}

void WinApi_X11::EventLoop()
{
	running = true;

	XEvent e;
	while(running)
	{
		XNextEvent(displayPtr, &e);
		if (e.type == Expose)
		{
			GraphicsObjectStorage_X11::GetApi()->Paint(displayPtr, &window, screenNo);
		}

		if(e.type == ButtonPress)
		{

		}

		if(e.type == ButtonRelease)
		{

		}

		if (e.type == KeyPress)
		{

		}

		if ((e.type == ClientMessage) &&
			(static_cast<unsigned int>(e.xclient.data.l[0]) == WM_DELETE_WINDOW))
		{
		  break;
		}
	}
	XDestroyWindow(displayPtr, window);
	XCloseDisplay(displayPtr);

}

void WinApi_X11::HandleEvent(const uint32_t eventNo, const EventDataBase* dataPtr)
{
	switch(eventNo)
	{
	case GRAPHICS_AVAIL_EVENT:
		break;

	case GRAPHICS_WIN_RESIZE_EVENT:
	{
		const WinResizeEventData* resizeDataPtr = static_cast<const WinResizeEventData*>(dataPtr);
		winSize = resizeDataPtr->GetNewSize();
		ResizeWindow(winSize);
	}
		break;
	default:
		break;
	}
}

void WinApi_X11::ResizeWindow(const Coord& newSize)
{
	XResizeWindow(displayPtr, window, newSize.GetX(), newSize.GetY());
}
