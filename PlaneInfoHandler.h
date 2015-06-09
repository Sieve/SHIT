#ifndef PLANEINFOHANDLER_H
#define PLANEINFOHANDLER_H
#include "DataStructs.h"
#include <wx/app.h>
#include <wx/list.h>
#include <string>
using namespace std;
#include <list>
using namespace std;

class PlaneInfoHandler
{
public:
	PlaneInfoHandler();
	~PlaneInfoHandler();
	
	void updatePlaneData();
	void updateFilterList();
	void SetEvent(bool Event);
	void SetNonEvent(bool NonEvent);
	void SetSorting(bool sorting);
	

	list<PlaneInfo> PlaneData;
	bool SortEvent;
	bool SortNonEvent;
	bool SortDescending;
};

#endif // PLANEINFOHANDLER_H
