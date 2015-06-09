#include "SaveManager.h"
#include <wx/file.h>

SaveManager::SaveManager(int slot)
{
	if(!slot){ Name = "tree"; }
	else{ Name = "Slot " + slot; }
}

SaveManager::~SaveManager(){}

bool SaveManager::CheckSlot(int slot)
{
	if (wxFile::Exists(Name)){ return true; }
	else{ return false; }
}

