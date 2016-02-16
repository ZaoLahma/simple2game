#include "jobdispatcher/jobdispatcher.h"
#include "winhandling/winapi_x11.h"
#include "winhandling/coord.h"

int main(void)
{
	WinApi_X11 winApi(Coord(300, 300));

	winApi.EventLoop();

	JobDispatcher::GetApi()->DropInstance();

	return 0;
}
