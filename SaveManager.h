#ifndef SAVEMANAGER_H
#define SAVEMANAGER_H
#include "DataStructs.h"
#include <wx/string.h>

class SaveManager
{
public:
	SaveManager(int slot);
	~SaveManager();
	
	bool CheckSlot(int slot);
	//bool Save();
	
	wxString Name;

};

#endif // SAVEMANAGER_H
