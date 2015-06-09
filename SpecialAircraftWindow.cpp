#include "SpecialAircraftWindow.h"
#include <wx/brush.h>
#include <wx/dcclient.h>
#include <wx/dcmemory.h>
#include <wx/gdicmn.h>

SpecialAircraftWindow::SpecialAircraftWindow(wxWindow *parent, list<TreeNode> *D)
	: SHITScrolledWindow(parent, D)
{
	width = (6*150)+100, height = (17*150)+100;
	Image.Create(width*scale, height*scale);
	this->SetLabel(wxT("Special Aircraft"));
	UpdateImage();
	Bind(wxEVT_LEFT_UP, &SpecialAircraftWindow::onLeftClick, this);
	Bind(wxEVT_RIGHT_UP, &SpecialAircraftWindow::onRightClick, this);
}

SpecialAircraftWindow::~SpecialAircraftWindow()
{
	Unbind(wxEVT_LEFT_UP, &SpecialAircraftWindow::onLeftClick, this);
	Unbind(wxEVT_RIGHT_UP, &SpecialAircraftWindow::onRightClick, this);
}

void SpecialAircraftWindow::OnDraw(wxDC &dc)
{
	if(update)
	{
		update = false;
		Image.Create(width*scale, height*scale);
		UpdateImage();
	}
	dc.DrawBitmap(Image,0,0,false);
	return;
}

void SpecialAircraftWindow::UpdateImage()
{
	wxMemoryDC dc(Image);
	if(!dc.IsOk()){ return; }
	dc.SetUserScale(scale, scale);
	dc.SetBrush(wxColour(2,11,26));
	dc.DrawRectangle(0,0,width,height);
	dc.SetTextForeground(wxColour(204,211,229));
	fontsize = 10;
	dc.SetFont(MakePanelFont(fontsize));
	
	int x = 0, y = 0;
	int pnode = 3;
	for(std::list<TreeNode>::iterator curr = data->begin(), last = data->end(); curr != last; ++curr)
	{
		if(curr->valid)
		{
			//std::cout << curr->name << endl << std::flush;
			if(curr->nodetype != pnode){ x = 0, y += 2, pnode = curr->nodetype; }
			int XPOS = 50 + (150*x), YPOS = 50 + (150*y);
			if(first){ HitZones.push_back(HitZone(&(*curr), XPOS, YPOS, 100, 100)); }
			
			dc.SetBrush(wxColour(204,211,229));
			dc.DrawRectangle(wxRect(XPOS, YPOS, 100, 100));
			dc.SetBrush(GetNodeColor(&(*curr)));
			dc.DrawRectangle(wxRect(XPOS+10, YPOS+10, 80, 80));
			
			wxString T = "Lv.";
			T << curr->level;
			while(dc.GetTextExtent(T).GetWidth() > 75 && dc.GetFont().GetPointSize() >= 6){ dc.SetFont(MakePanelFont(dc.GetFont().GetPointSize() - 1)); }
			dc.DrawText(T, XPOS+90-2-dc.GetTextExtent(T).GetWidth(), YPOS+10+dc.GetTextExtent(T).GetHeight());
			dc.SetFont(MakePanelFont(fontsize));
			
			//if(curr->cost == "0"){ curr->cost = "0 "; }				//Hacky as FUCK
			while(dc.GetTextExtent(curr->cost[curr->level]).GetWidth() > 75 && dc.GetFont().GetPointSize() >= 6){ dc.SetFont(MakePanelFont(dc.GetFont().GetPointSize() - 1)); }
			dc.DrawText(curr->cost[curr->level], XPOS+90-2-dc.GetTextExtent(curr->cost[curr->level]).GetWidth(), YPOS+10);//-(10*(*N)->cost.size())-4
			dc.SetFont(MakePanelFont(fontsize));
			
			//wxString TempName(curr->name);
			wxString TempName(curr->name);
			wxString TempExtra(curr->name);
			TempName = TempName.BeforeFirst(' ');
			TempName << " -" << curr->abbreviation << "-";
			TempExtra = TempExtra.AfterFirst(' ');
			while(dc.GetTextExtent(TempExtra).GetWidth() > 79 && dc.GetFont().GetPointSize() >= 6){ dc.SetFont(MakePanelFont(dc.GetFont().GetPointSize() - 1)); }
			int YOFF = YPOS+90-(dc.GetTextExtent(TempExtra).GetHeight());
			dc.DrawText(TempExtra, XPOS+11, YOFF);
			dc.SetFont(MakePanelFont(fontsize));
			while(dc.GetTextExtent(TempName).GetWidth() > 79 && dc.GetFont().GetPointSize() >= 6){ dc.SetFont(MakePanelFont(dc.GetFont().GetPointSize() - 1)); }
			dc.DrawText(TempName, XPOS+11, YOFF-(dc.GetTextExtent(TempName).GetHeight()));
			dc.SetFont(MakePanelFont(fontsize));
			
			/*TempName.replace(TempName.find(" -"), 1, " -" + curr->abbreviation + "-\n");
			while(dc.GetMultiLineTextExtent(TempName).GetWidth() > 75 && dc.GetFont().GetPointSize() >= 6){ dc.SetFont(MakePanelFont(dc.GetFont().GetPointSize() - 1)); }
			dc.DrawText(TempName, XPOS+12, YPOS+90-(dc.GetMultiLineTextExtent(TempName).GetHeight()));
			dc.SetFont(MakePanelFont(fontsize));*/
			
			x++;
		}
		if(x >= 6){ x = 0, y++; }
	}
	
	
	if(!first && scale != lastscale)
	{
		wxPoint Temp = CalcUnscrolledPosition(wxPoint(0,0));
		SetScrollbars(1,1,width*scale,height*scale, Temp.x/lastscale*scale, Temp.y/lastscale*scale);
		//Scroll(Temp.x*scale, Temp.y*scale);
		lastscale = scale;
	}
	if(first)
	{
		SetScrollbars(1,1,width*scale,height*scale,0,0);
		first = false;
	}
	return;
}

void SpecialAircraftWindow::onLeftClick(wxMouseEvent& event)
{
	if(!edit){ return; }
	//std::cout << event.GetX() << "|" << event.GetY() << endl << std::flush;
	int XPOS, YPOS;
	this->CalcUnscrolledPosition(event.GetX(), event.GetY(), &XPOS, &YPOS);
	XPOS /= scale, YPOS /= scale;
	//std::cout << XPOS << "|" << YPOS << endl << std::flush;
	for(std::list<HitZone>::const_iterator curr = HitZones.begin(), last = HitZones.end(); curr != last; ++curr)
	{
		if( (XPOS > curr->Corner.x && XPOS < curr->Corner.x + curr->width) && (YPOS > curr->Corner.y && YPOS < curr->Corner.y + curr->height))
		{
			//std::cout << curr->node->name << endl << std::flush;
			switch(emode)
			{
				case(NONE):
					break;
				case(UNLOCK):
					if(curr->node->aquired)
					{
						curr->node->aquired = false;
						curr->node->level = 0;
					}
					else
					{
						curr->node->aquired = true, curr->node->level = 1;
					}
					break;
				case(LEVEL):
					if(curr->node->aquired && curr->node->level < curr->node->maxlevel){ curr->node->level++; }
					break;
				case(DELEVEL):
					if(curr->node->aquired && curr->node->level > 1){ curr->node->level--; }
					break;
			}
			break;
		}
	}
	UpdateImage();
	Refresh();
	return;
}

void SpecialAircraftWindow::onRightClick(wxMouseEvent& event)
{
	wxUnusedVar(event);
	if(!edit){ return; }
	wxMenu menu;
	menu.AppendRadioItem(0, "None");
	menu.AppendRadioItem(1, "Unlock");
 	menu.AppendRadioItem(2, "Level");
 	menu.AppendRadioItem(3, "Delevel");
	menu.Check(emode, true);
 	menu.Connect(wxEVT_COMMAND_MENU_SELECTED, (wxObjectEventFunction)&SpecialAircraftWindow::OnPopupClick, NULL, this);
 	PopupMenu(&menu);
	return;
}

void SpecialAircraftWindow::OnPopupClick(wxCommandEvent &evt)
{
	switch(evt.GetId())
	{
		case(0):
			emode = NA;
			break;
		case(1):
			emode = UNLOCK;
			break;
		case(2):
			emode = LEVEL;
			break;
		case(3):
			emode = DELEVEL;
			break;
	}
	return;
}
