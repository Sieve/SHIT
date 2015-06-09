#include "SpecialWeaponWindow.h"

SpecialWeaponWindow::SpecialWeaponWindow(wxWindow *parent, list<TreeNode> *D)
	: SHITScrolledWindow(parent, D)
{
	width = (11*150)+100, height = (5*150)+100;
	Image.Create(width*scale, height*scale);
	this->SetLabel(wxT("Special Weapons"));
	UpdateImage();
	Bind(wxEVT_LEFT_UP, &SpecialWeaponWindow::onLeftClick, this);
	Bind(wxEVT_RIGHT_UP, &SpecialWeaponWindow::onRightClick, this);
}

SpecialWeaponWindow::~SpecialWeaponWindow()
{
	Unbind(wxEVT_LEFT_UP, &SpecialWeaponWindow::onLeftClick, this);
	Unbind(wxEVT_RIGHT_UP, &SpecialWeaponWindow::onRightClick, this);
}

void SpecialWeaponWindow::OnDraw(wxDC &dc)
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

void SpecialWeaponWindow::UpdateImage()
{
	wxMemoryDC dc(Image);
	if(!dc.IsOk()){ return; }
	dc.SetUserScale(scale, scale);
	dc.SetBrush(wxColour("ACI-DarkBlue"));
	dc.DrawRectangle(0,0,width,height);
	dc.SetTextForeground(wxColour(204,211,229));
	dc.SetFont(MakePanelFont(fontsize));
	
	int x = 0, y = 0;
	int pnode = 7;
	for(std::list<TreeNode>::iterator curr = data->begin(), last = data->end(); curr != last; ++curr)
	{
		if(curr->valid)
		{
			if(curr->aquired){ dc.SetBrush(wxColour("ACI-LightBlue")); }
			else{ dc.SetBrush(wxColour("ACI-Blue")); }
			//std::cout << curr->name << endl << std::flush;
			if(curr->nodetype != pnode){ x = 0, y += 2, pnode = curr->nodetype; }
			int XPOS = 50 + (150*x), YPOS = 50 + (150*y);
			if(first){ HitZones.push_back(HitZone(&(*curr), XPOS, YPOS, 100, 100)); }
			
			dc.DrawRectangle(wxRect(XPOS, YPOS, 100, 100));
			dc.SetBrush(GetNodeColor(&(*curr)));
			dc.DrawRectangle(wxRect(XPOS+10, YPOS+10, 80, 80));
			
			wxString level = "Lv.";
			level << curr->level;
			dc.DrawText(level, XPOS+50-(dc.GetTextExtent(level).GetWidth()/2), YPOS+50-(dc.GetTextExtent(level).GetHeight()/2));
			
			if(curr->aquired && curr->level < 5)
			{ 
				while(dc.GetTextExtent(curr->cost[curr->level]).GetWidth() > 75 && dc.GetFont().GetPointSize() >= 6){ dc.SetFont(MakePanelFont(dc.GetFont().GetPointSize() - 1)); }
				dc.DrawText(curr->cost[curr->level], XPOS+90-2-dc.GetTextExtent(curr->cost[curr->level]).GetWidth(), YPOS+10);
				dc.SetFont(MakePanelFont(fontsize));
			}
			
			while(dc.GetTextExtent(curr->name).GetWidth() > 75 && dc.GetFont().GetPointSize() >= 6){ dc.SetFont(MakePanelFont(dc.GetFont().GetPointSize() - 1)); }
			dc.DrawText(curr->name, XPOS+12, YPOS+90-(dc.GetTextExtent(curr->name).GetHeight()));
			dc.SetFont(MakePanelFont(fontsize));
			
			x++;
		}
	}
	
	if(!first && scale != lastscale)
	{
		wxPoint Temp = CalcUnscrolledPosition(wxPoint(0,0));
		SetScrollbars(1,1,width*scale,height*scale, Temp.x/lastscale*scale, Temp.y/lastscale*scale);
		lastscale = scale;
	}
	if(first)
	{
		SetScrollbars(1,1,width*scale,height*scale,0,0);
		first = false;
	}
	return;
}

void SpecialWeaponWindow::onLeftClick(wxMouseEvent& event)
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
					//if(curr->branch->loc[0] == 0){ break; }
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
					if(curr->node->aquired && curr->node->level < 5){ curr->node->level++; }
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

void SpecialWeaponWindow::onRightClick(wxMouseEvent& event)
{
	wxUnusedVar(event);
	if(!edit){ return; }
	wxMenu menu;
	menu.AppendRadioItem(0, "None");
	menu.AppendRadioItem(1, "Unlock");
 	menu.AppendRadioItem(2, "Level");
 	menu.AppendRadioItem(3, "Delevel");
	menu.Check(emode, true);
 	menu.Connect(wxEVT_COMMAND_MENU_SELECTED, (wxObjectEventFunction)&SpecialWeaponWindow::OnPopupClick, NULL, this);
 	PopupMenu(&menu);
	return;
}

void SpecialWeaponWindow::OnPopupClick(wxCommandEvent &evt)
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
