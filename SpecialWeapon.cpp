#include "SpecialWeapon.h"
#include <wx/file.h>
#include <wx/dcclient.h>

SpecialWeapon::SpecialWeapon(wxWindow* parent, list<TreeNode> *D)
    : SpecialWeaponBaseClass(parent)
{
	DisplayWindow = new SpecialWeaponWindow(this, D);
	ZoomLevel = 3;
	ZoomLevels[0] = 0.25, ZoomLevels[1] = 0.50, ZoomLevels[2] = 0.75, ZoomLevels[3] = 1.0, ZoomLevels[4] = 2.0;
}

void SpecialWeapon::onZoomIn(wxCommandEvent& event)
{
	wxUnusedVar(event);
	if(ZoomLevel < 4){ ZoomLevel++; }
	else{ return; }
	DisplayWindow->scale = ZoomLevels[ZoomLevel];
	DisplayWindow->update = true;
	DisplayWindow->Refresh();
	return;
}

void SpecialWeapon::onZoomOut(wxCommandEvent& event)
{
	wxUnusedVar(event);
	if(ZoomLevel > 0){ ZoomLevel--; }
	else{ return; }
	DisplayWindow->scale = ZoomLevels[ZoomLevel];
	DisplayWindow->update = true;
	DisplayWindow->Refresh();
	return;
}

void SpecialWeapon::onSaveData(wxCommandEvent& event)
{
	wxUnusedVar(event);
	wxString ParsedSave = "{";
	for(std::list<TreeNode>::const_iterator curr = DisplayWindow->data->begin(), last = DisplayWindow->data->end(); curr != last; ++curr)
	{
		if(curr->level > 0)
		{
			ParsedSave << "<" << curr->name << "|" << curr->level << ">";
		}
	}
	ParsedSave << "}";
	wxFile SaveData;
	if(SaveData.Exists("SHIT.txt"))
	{
		SaveData.Open("SHIT.txt", wxFile::read_write);
		if(!SaveData.IsOpened()){ return; }
		wxString Data;
		SaveData.ReadAll(&Data);
		SaveData.Close();
		SaveData.Create("SHIT.txt", true);
		SaveData.Write("(" + Data.AfterFirst('(').BeforeFirst(')') + ")" + "[" + Data.AfterFirst('{').BeforeFirst('}') + "]" + ParsedSave);
	}
	else
	{
		SaveData.Create("SHIT.txt");
		SaveData.Write("()[]" + ParsedSave);
	}
	SaveData.Close();
	return;
}

void SpecialWeapon::onSavePNG(wxCommandEvent& event)
{
	wxUnusedVar(event);
	DisplayWindow->Image.SaveFile("SpecialAircraft.PNG", wxBITMAP_TYPE_PNG);
	return;
}

void SpecialWeapon::onEdit(wxCommandEvent& event)
{
	wxUnusedVar(event);
	DisplayWindow->edit = !DisplayWindow->edit;
	return;
}

void SpecialWeapon::onClose(wxCloseEvent& event)
{
	Freeze();
	Hide();
}
