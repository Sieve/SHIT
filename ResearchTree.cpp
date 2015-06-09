#include "ResearchTree.h"
#include <wx\dcclient.h>
//#include <wx\file.h>
//#include <wx\gdicmn.h>

ResearchTree::ResearchTree(wxWindow* parent, TreeBase *B)
	: ResearchTreeBaseClass(parent)
{
	DisplayWindow = new ResearchTreeWindow(this, B);
	ZoomLevel = 3;
	ZoomLevels[0] = 0.25, ZoomLevels[1] = 0.50, ZoomLevels[2] = 0.75, ZoomLevels[3] = 1.0, ZoomLevels[4] = 2.0;
}

void ResearchTree::onZoomIn(wxCommandEvent& event)
{
	wxUnusedVar(event);
	if(ZoomLevel < 4){ ZoomLevel++; }
	else{ return; }
	//DisplayWindow->SetScale(DisplayWindow->width*ZoomLevels[ZoomLevel], DisplayWindow->height*ZoomLevels[ZoomLevel]);
	DisplayWindow->scale = ZoomLevels[ZoomLevel];
	DisplayWindow->update = true;
	DisplayWindow->Refresh();
	//DisplayWindow->Scroll(DisplayWindow->GetPosition());
	return;
}
void ResearchTree::onZoomOut(wxCommandEvent& event)
{
	wxUnusedVar(event);
	if(ZoomLevel > 0){ ZoomLevel--; }
	else{ return; }
	//DisplayWindow->SetScale(DisplayWindow->width*ZoomLevels[ZoomLevel], DisplayWindow->height*ZoomLevels[ZoomLevel]);
	//Temp.x /= DisplayWindow->scale;
	//Temp.y /= DisplayWindow->scale;
	DisplayWindow->scale = ZoomLevels[ZoomLevel];
	DisplayWindow->update = true;
	DisplayWindow->Refresh();
	return;
}

/*void ResearchTree::onClose(wxCloseEvent& event)
{
	wxUnusedVar(event);
	DestroyChildren();
	Destroy();
	return;
}*/

void ResearchTree::onSaveData(wxCommandEvent& event)
{
	wxUnusedVar(event);
	wxString ParsedSave = "(";
	for(std::list<TreeBranch*>::const_iterator C = DisplayWindow->RTree->TreeBranches.begin(), L = DisplayWindow->RTree->TreeBranches.end(); C != L; ++C)
	{
		for(std::list<TreeNode*>::const_iterator curr = (*C)->Nodes.begin(), last = (*C)->Nodes.end(); curr != last; ++curr)
		{
			if((*curr)->aquired)
			{
				ParsedSave << "<" << (*curr)->name << "|";
				if((*curr)->nodetype == 1){ ParsedSave << "0" << ">"; }
				else{ ParsedSave << (*curr)->level << ">"; }
			}
		}
	}
	ParsedSave << ")";
	wxFile SaveData;
	if(SaveData.Exists("SHIT.txt"))
	{
		SaveData.Open("SHIT.txt", wxFile::read_write);
		if(!SaveData.IsOpened()){ return; }
		wxString Data;
		SaveData.ReadAll(&Data);
		SaveData.Close();
		SaveData.Create("SHIT.txt", true);
		SaveData.Write(ParsedSave + "[" + Data.AfterFirst('[').BeforeFirst(']') + "]" + "{" + Data.AfterFirst('{').BeforeFirst('}') + "}");
	}
	else
	{
		SaveData.Create("SHIT.txt");
		SaveData.Write(ParsedSave + "[]" + "{}");
	}
	SaveData.Close();
	return;
}

void ResearchTree::onSavePNG(wxCommandEvent& event)
{
	wxUnusedVar(event);
	DisplayWindow->Image.SaveFile("ResearchTree.PNG", wxBITMAP_TYPE_PNG);
	return;
}

void ResearchTree::onEdit(wxCommandEvent& event)
{
	wxUnusedVar(event);
	DisplayWindow->edit = !DisplayWindow->edit;
	return;
}

void ResearchTree::onClose(wxCloseEvent& event)
{
	Freeze();
	Hide();
}
