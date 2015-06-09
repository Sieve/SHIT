#include "SpecialAircraft.h"
#include <wx/file.h>
//#include <wx/msw/brush.h>
#include <wx/dcclient.h>

SpecialAircraft::SpecialAircraft(wxWindow* parent, list<TreeNode> *SA)
    : SpecialAircraftBaseClass(parent)
{
	DisplayWindow = new SpecialAircraftWindow(this, SA);
	ZoomLevel = 3;
	ZoomLevels[0] = 0.25, ZoomLevels[1] = 0.50, ZoomLevels[2] = 0.75, ZoomLevels[3] = 1.0, ZoomLevels[4] = 2.0;
}

void SpecialAircraft::onZoomIn(wxCommandEvent& event)
{
	wxUnusedVar(event);
	if(ZoomLevel < 4){ ZoomLevel++; }
	else{ return; }
	DisplayWindow->scale = ZoomLevels[ZoomLevel];
	DisplayWindow->update = true;
	DisplayWindow->Refresh();
	return;
}

void SpecialAircraft::onZoomOut(wxCommandEvent& event)
{
	wxUnusedVar(event);
	if(ZoomLevel > 0){ ZoomLevel--; }
	else{ return; }
	DisplayWindow->scale = ZoomLevels[ZoomLevel];
	DisplayWindow->update = true;
	DisplayWindow->Refresh();
	return;
}

void SpecialAircraft::onSaveData(wxCommandEvent& event)
{
	wxUnusedVar(event);
	wxString ParsedSave = "[";
	for(std::list<TreeNode>::const_iterator curr = DisplayWindow->data->begin(), last = DisplayWindow->data->end(); curr != last; ++curr)
	{
		if(curr->level > 0)
		{
			ParsedSave << "<" << curr->name << "|" << curr->level << ">";
		}
	}
	ParsedSave << "]";
	wxFile SaveData;
	if(SaveData.Exists("SHIT.txt"))
	{
		SaveData.Open("SHIT.txt", wxFile::read_write);
		if(!SaveData.IsOpened()){ return; }
		wxString SD;
		SaveData.ReadAll(&SD);
		SaveData.Close();
		SaveData.Create("SHIT.txt", true);
		SaveData.Write("(" + SD.AfterFirst('(').BeforeFirst(')') + ")" + ParsedSave + "{" + SD.AfterFirst('{').BeforeFirst('}') + "}");
	}
	else
	{
		SaveData.Create("SHIT.txt");
		SaveData.Write("()" + ParsedSave + "{}");
	}
	SaveData.Close();
	return;
}

void SpecialAircraft::onSavePNG(wxCommandEvent& event)
{
	wxUnusedVar(event);
	DisplayWindow->Image.SaveFile("SpecialAircraft.PNG", wxBITMAP_TYPE_PNG);
	return;
}

void SpecialAircraft::onEdit(wxCommandEvent& event)
{
	wxUnusedVar(event);
	DisplayWindow->edit = !DisplayWindow->edit;
	return;
}

void SpecialAircraft::onClose(wxCloseEvent& event)
{
	Freeze();
	Hide();
}
