#include "ResearchTreeWindow.h"
#include <wx/brush.h>
#include <wx/dcclient.h>
#include <wx/dcmemory.h>
#include <wx/gdicmn.h>
#include <stdlib.h>

ResearchTreeWindow::ResearchTreeWindow(wxWindow *parent, TreeBase *B)
	: wxScrolledWindow(parent)
{
	RTree = B;
	first = true, update = false, edit = false;
	scale = 1.0, lastscale = 1.0;
	width = (15*150)+100, height = (15*200)+100;
	Image.Create(width*scale, height*scale);
	this->SetLabel(wxT("Research Tree"));
	//SetDoubleBuffered(true);
	//this->SetSizer(S);
	//this->SetSize(parent->GetSize());
	//SetVirtualSize((15*120)+50, (15*120)+50);
	//SetScrollbars(10, 10, (15*120+50)/10, (15*120+50)/10, 0,0);
	//this->ShowScrollbars(wxScrollbarVisibility::wxSHOW_SB_ALWAYS, wxScrollbarVisibility::wxSHOW_SB_ALWAYS);
	for(std::list<TreeBranch*>::const_iterator curr = RTree->TreeBranches.begin(), last = RTree->TreeBranches.end(); curr != last; ++curr)
	{
		for(std::list<TreeBranch*>::const_iterator target = RTree->TreeBranches.begin(); target != last; ++target)
		{
			for(std::list<std::vector<int> >::const_iterator L = (*curr)->Children.begin(), E = (*curr)->Children.end(); L != E; ++L)
			{
				if((*L)[0] == (*target)->loc[0] && (*L)[1] == (*target)->loc[1])
				{
					(*curr)->ChildBranches.push_back((*target));
					(*target)->ParentBranches.push_back((*curr));
				}
			}
			if((*(*curr)->Nodes.begin())->name == "MiG-21" && (*(*target)->Nodes.begin())->name == "MSL SPEED+" && (*(*target)->Nodes.begin())->partsize == "S")//MiG-21
			{
				(*curr)->ChildBranches.push_back((*target));
				(*target)->ParentBranches.push_back((*curr));
			}
			else if( ((*(*curr)->Nodes.begin())->name == "F-15C" || (*(*curr)->Nodes.begin())->name == "F-15C") && (*(*target)->Nodes.begin())->name == "ROLL+" && (*(*target)->Nodes.begin())->partsize == "M")//F-15C
			{
				(*curr)->ChildBranches.push_back((*target));
				(*target)->ParentBranches.push_back((*curr));
			}
			else if( ((*(*curr)->Nodes.begin())->name == "GUN RANGE+" && (*(*curr)->Nodes.begin())->partsize == "S") && (*(*target)->Nodes.begin())->name == "ROLL+" && (*(*target)->Nodes.begin())->partsize == "L")//Gun Range+ S
			{
				(*curr)->ChildBranches.push_back((*target));
				(*target)->ParentBranches.push_back((*curr));
			}
		}
	}
	for(std::list<TreeBranch*>::const_iterator curr = RTree->TreeBranches.begin(), last = RTree->TreeBranches.end(); curr != last; ++curr)
	{
		if((*curr)->loc[0] == 0)
		{
			(*(*curr)->Nodes.begin())->aquired = true, (*curr)->unlocked = true;
			if((*curr)->loc[1] == 7 && (*(*curr)->Nodes.begin())->level == 0){ (*(*curr)->Nodes.begin())->level = 1; }
			(*curr)->UpdateUnlocked();
		}
	}
	
	UpdateImage();
	//Show();
	//SetScrollbars();
	//Connect(wxEVT_PAINT, wxPaintEventHandler(ResearchTreeWindow::onPaint));
	emode = NA;
	Bind(wxEVT_LEFT_UP, &ResearchTreeWindow::onLeftClick, this);
	Bind(wxEVT_RIGHT_UP, &ResearchTreeWindow::onRightClick, this);
	
}

ResearchTreeWindow::~ResearchTreeWindow()
{
	Unbind(wxEVT_LEFT_UP, &ResearchTreeWindow::onLeftClick, this);
	Unbind(wxEVT_RIGHT_UP, &ResearchTreeWindow::onRightClick, this);
}

void ResearchTreeWindow::OnDraw(wxDC& dc)
{
	if(update)
	{
		update = false;
		Image.SetSize(width*scale, height*scale);
		UpdateImage();
	}
	dc.DrawBitmap(Image,0,0,false);
	//std::cout << dc.GetPPI().GetWidth() << dc.GetPPI().GetHeight() << endl << std::flush;
	return;
}

/*void ResearchTreeWindow::onPaint(wxPaintEvent& event)
{
	wxUnusedVar(event);
	wxPaintDC dc(this);
	if(update)
	{
		Image.SetSize(width*scale, height*scale);
		UpdateImage();
		update = false;
	}
	dc.DrawBitmap(Image,0,0,false);
	//std::cout << dc.GetPPI().GetWidth() << dc.GetPPI().GetHeight() << endl << std::flush;
	return;
}*/


void ResearchTreeWindow::UpdateImage()
{
	//wxPaintDC dc(this);
	//wxClientDC dc(this);
	wxMemoryDC dc(Image);
	if(!dc.IsOk()){ return; }
	dc.SetUserScale(scale, scale);
	dc.SetBrush(wxColour(2,11,26));
	dc.DrawRectangle(0,0,width,height);
	dc.SetTextForeground(wxColour(204,211,229));
	fontsize = 10;
	dc.SetFont(MakePanelFont(fontsize));
	
	for(std::list<TreeBranch*>::const_iterator curr = RTree->TreeBranches.begin(), last = RTree->TreeBranches.end(); curr != last; ++curr)
	{
		if((*curr)->valid)
		{
			int x = (*curr)->loc[0];
			int y = (*curr)->loc[1];
			//std::cout << "TEST: " << x << "|" << y << endl << std::flush;
			dc.SetBrush(wxColour(204,211,229));
			//dc.DrawRectangle(wxRect((x*5)+5, (y*5)+5, 3, 3));
			//dc.DrawRectangle(wxRect((x*120)+25, (y*120)+25, 100, 100);
			int offset = 0;
			
			/*bool childunlocked = true;
			for(std::list<TreeNode*>::const_iterator N = (*curr)->Nodes.begin(); N != (*curr)->Nodes.end(); ++N){ if(!(*N)->aquired){ childunlocked = false; } }
			if(childunlocked) { for(std::list<TreeBranch*>::const_iterator C = (*curr)->ChildBranches.begin(); C != (*curr)->ChildBranches.end(); ++C){ (*C)->unlocked = childunlocked; } }*/
			if((*curr)->Nodes.size() == 2){ offset = -46; }
			for(std::list<TreeNode*>::const_iterator N = (*curr)->Nodes.begin(); N != (*curr)->Nodes.end(); ++N)
			{
				if((*N)->nodetype > 0)
				{
					int XPOS = (x*150)+50;
					int YPOS = (y*200)+50+offset;
					if(first){ HitZones.push_back(HitZone((*N), (*curr), XPOS, YPOS, 100, 100)); }
					if((*curr)->unlocked){ dc.SetBrush(wxColour("ACI-LightBlue")); }
					else{ dc.SetBrush(wxColour("ACI-Blue")); }
					dc.SetPen(wxPen(wxColour(0,0,0),1));
					dc.DrawRectangle(wxRect(XPOS, YPOS, 100, 100));
					dc.SetBrush(GetNodeColor((*N)));
					dc.DrawRectangle(wxRect(XPOS+10, YPOS+10, 80, 80));
					if(!((*N)->nodetype == 1 && (*N)->aquired) || (*N)->level != (*N)->maxlevel)
					{
						while(dc.GetTextExtent((*N)->cost[(*N)->level]).GetWidth() > 75 && dc.GetFont().GetPointSize() >= 6){ dc.SetFont(MakePanelFont(dc.GetFont().GetPointSize() - 1)); }
						dc.DrawText((*N)->cost[(*N)->level], XPOS+90-2-dc.GetTextExtent((*N)->cost[(*N)->level]).GetWidth(), YPOS+10);
						dc.SetFont(MakePanelFont(fontsize));
					}
					//if((*N)->cost == "0"){ (*N)->cost = "0 "; }				//Hacky as FUCK
					//dc.DrawText((*N)->cost, XPOS+80-(fontsize*((*N)->cost.size()-2)), YPOS+fontsize);//-(10*(*N)->cost.size())-4
					if((*N)->nodetype != 1)
					{
						wxString T = "Lv.";
						T << (*N)->level;
						while(dc.GetTextExtent(T).GetWidth() > 75 && dc.GetFont().GetPointSize() >= 6){ dc.SetFont(MakePanelFont(dc.GetFont().GetPointSize() - 1)); }
						dc.DrawText(T, XPOS+90-2-dc.GetTextExtent(T).GetWidth(), YPOS+10+dc.GetTextExtent(T).GetHeight());
						dc.SetFont(MakePanelFont(fontsize));
						//dc.DrawText(wxT("Lv.0"), XPOS+50-(fontsize*1.5), YPOS+50-fontsize);
					}
					else
					{
						dc.SetFont(MakePanelFont(fontsize + 8));
						//dc.DrawText((*N)->partsize, XPOS+12, YPOS+(fontsize + 8 - 2)/2);
						dc.DrawText((*N)->partsize, XPOS+12, YPOS+8);
						dc.SetFont(MakePanelFont(fontsize));
						wxString stext = "";
						if((*N)->SlotCosts[0]){ stext << "ARMS:" << (*N)->SlotCosts[0]; }
						else if((*N)->SlotCosts[1] > 0){ stext << "BODY:" << (*N)->SlotCosts[1]; }
						else if((*N)->SlotCosts[2] > 0){ stext << "MISC:" << (*N)->SlotCosts[2]; }
						//std::cout << "TEXT: " << stext << " (" << (*N)->SlotCosts[0] << "," << (*N)->SlotCosts[1] << "," << (*N)->SlotCosts[2] << ")" << endl << std::flush;
						//dc.DrawText(stext, XPOS+90-2-((fontsize-2)*stext.size()), YPOS+(fontsize*2.5));
						if(!(*N)->aquired){ dc.DrawText(stext, XPOS+90-2-dc.GetTextExtent(stext).GetWidth(), YPOS+10+dc.GetTextExtent(stext).GetHeight());; }
						else{ dc.DrawText(stext, XPOS+90-2-dc.GetTextExtent(stext).GetWidth(), YPOS+10+2); }
						//XPOS+90-2-dc.GetTextExtent(stext).GetWidth()
					}
					
					/*if(dc.GetTextExtent((*N)->name).GetWidth() > 75)
					{
						while(dc.GetTextExtent((*N)->name).GetWidth() > 75 && dc.GetFont().GetPointSize() >= 6){ dc.SetFont(MakePanelFont(dc.GetFont().GetPointSize() - 1)); }
						dc.DrawText((*N)->name, XPOS+12, YPOS+80-(dc.GetFont().GetPointSize()/2));
						dc.SetFont(MakePanelFont(fontsize));
					}
					else{ dc.DrawText((*N)->name, XPOS+12, YPOS+80-fontsize/2); }*/
					while(dc.GetTextExtent((*N)->name).GetWidth() > 75 && dc.GetFont().GetPointSize() >= 6){ dc.SetFont(MakePanelFont(dc.GetFont().GetPointSize() - 1)); }
					dc.DrawText((*N)->name, XPOS+12, YPOS+90-dc.GetTextExtent((*N)->name).GetHeight());
					dc.SetFont(MakePanelFont(fontsize));
					
					if(offset == 53)
					{
						//dc.SetPen(wxPen(wxColour(204,211,229), 4));
						dc.SetPen((*wxTRANSPARENT_PEN));
						if((*curr)->unlocked){ dc.SetBrush(wxColour("ACI-LightBlue")); }
						else{ dc.SetBrush(wxColour("ACI-Blue")); }

						//dc.DrawLine(XPOS, YPOS+1, XPOS+100, YPOS+1);
						dc.DrawRectangle(XPOS, YPOS-2, 99, 4);
					}
					if((*curr)->Nodes.size() == 2){ offset = 53; }
				}
			}
		
		
			//DRAWING
			
			if(!(*curr)->Parents.empty() && (*curr)->loc[0] != 0)
			{
				//dc.SetPen(wxPen(wxColour(50,50,50), 1));
				dc.SetPen((*wxTRANSPARENT_PEN));
				if((*curr)->unlocked){ dc.SetBrush(wxColour("ACI-LightBlue")); }
				else{ dc.SetBrush(wxColour("ACI-Blue")); }
				int XPOS = ((*curr)->loc[0]*150)+50, YPOS = ((*curr)->loc[1]*200)+50+50;
				dc.DrawRectangle(XPOS, YPOS, 2, 8);
				/*dc.DrawPoint(XPOS, YPOS);
				dc.DrawPoint(XPOS, YPOS+1);
				dc.DrawPoint(XPOS, YPOS+2);
				dc.DrawPoint(XPOS, YPOS+3);
				dc.DrawPoint(XPOS, YPOS+4);
				dc.DrawPoint(XPOS, YPOS+5);
				dc.DrawPoint(XPOS, YPOS+6);
				dc.DrawPoint(XPOS, YPOS+7);*/
			}
			
			
			if(!(*curr)->Children.empty())
			{
				dc.SetBrush(wxBrush(wxTransparentColour, wxBRUSHSTYLE_TRANSPARENT));
				//if((*curr)->unlocked){ dc.SetPen(wxPen(wxColour("ACI-LightBlue"), 8)); }
				//else{ dc.SetPen(wxPen(wxColour("ACI-Blue"), 8)); }
				
				for(std::list<vector<int> >::const_iterator child = (*curr)->Children.begin(); child != (*curr)->Children.end(); ++child)
				{
					if((*curr)->unlocked)
					{
						for(std::list<TreeBranch*>::const_iterator B = (*curr)->ChildBranches.begin(), L = (*curr)->ChildBranches.end(); B != L; ++B)
						{
							if((*B)->loc[0] == (*child)[0] && (*B)->loc[1] == (*child)[1])
							{
								if((*B)->unlocked){ dc.SetPen(wxPen(wxColour("ACI-LightBlue"), 8)); }
								else{ dc.SetPen(wxPen(wxColour("ACI-Blue"), 8)); }
								break;
							}
						}
					}
					else{ dc.SetPen(wxPen(wxColour("ACI-Blue"), 8)); }
					int XPOS = ((*curr)->loc[0]*150)+100, YPOS = ((*curr)->loc[1]*200)+100;//Centered on boxes
					XPOS += 100 - 1, YPOS += 4;
					if((*child)[1] < (*curr)->loc[1])
					{
						XPOS += 0 - 50 + 5, YPOS += 1;
						DrawArc(dc, XPOS, YPOS, LEFT, UP);
						DrawLine(dc, XPOS, YPOS, false, (((*child)[1] - (*curr)->loc[1])*200)+50);
						DrawArc(dc, XPOS, YPOS, DOWN, RIGHT);
					}
					else if((*child)[1] > (*curr)->loc[1])
					{
						XPOS += 1 - 50 + 2, YPOS += 0;
						DrawArc(dc, XPOS, YPOS, LEFT, DOWN);
						DrawLine(dc, XPOS, YPOS, false, (((*child)[1] - (*curr)->loc[1]) * 200) - 50);
						DrawArc(dc, XPOS, YPOS, UP, RIGHT);
					}
					else if((*child)[1] == (*curr)->loc[1])
					{
						XPOS -= 50;
						DrawLine(dc, XPOS, YPOS, true, 25);
						XPOS -= 23;
						DrawLine(dc, XPOS, YPOS, true, (((*child)[0] - (*curr)->loc[0])*150)-100);
					}
				}
				//Forgive me for what I must do
				if((*curr)->loc[0] == 1 && (*curr)->loc[1] == 6)//MiG-21
				{
					if((*(*curr)->Nodes.begin())->aquired){ dc.SetPen(wxPen(wxColour("ACI-LightBlue"), 8)); }
					else{ dc.SetPen(wxPen(wxColour("ACI-Blue"), 8)); }
					int XPOS = ((*curr)->loc[0]*150)+100, YPOS = ((*curr)->loc[1]*200)+100;//Centered on boxes
					XPOS += 100 + 1 - 52, YPOS += 4;
					DrawLine(dc, XPOS, YPOS, true, 152);
					DrawArc(dc, XPOS, YPOS, LEFT, UP);
					DrawLine(dc, XPOS, YPOS, false, -550+1);
					DrawArc(dc, XPOS, YPOS, DOWN, RIGHT);				
				}
				else if((*curr)->loc[0] == 7 && (*curr)->loc[1] == 3)//Gun Range + S, Air Seek +
				{
					if((*curr)->unlocked){ dc.SetPen(wxPen(wxColour("ACI-LightBlue"), 8)); }
					else{ dc.SetPen(wxPen(wxColour("ACI-Blue"), 8)); }
					int XPOS = ((*curr)->loc[0]*150)+100, YPOS = ((*curr)->loc[1]*200)+100;//Centered on boxes
					XPOS += 100 + 1 + 100, YPOS += 4;
					DrawArc(dc, XPOS, YPOS, LEFT, UP);
					DrawLine(dc, XPOS, YPOS, false, -150);
					DrawArc(dc, XPOS, YPOS, DOWN, RIGHT);
				}
				else if((*curr)->loc[0] == 8 && (*curr)->loc[1] == 4)//Roll+ M
				{
					if((*curr)->unlocked){ dc.SetPen(wxPen(wxColour("ACI-LightBlue"), 8)); }
					else{ dc.SetPen(wxPen(wxColour("ACI-Blue"), 8)); }
					int XPOS = ((*curr)->loc[0]*150)+100, YPOS = ((*curr)->loc[1]*200)+100;//Centered on boxes
					XPOS += 100 + 1 - 150, YPOS += 4;
					DrawLine(dc, XPOS, YPOS, true, -150);
				}
				else if((*curr)->loc[0] == 11 && (*curr)->loc[1] == 14)//Su-34
				{
					if((*curr)->unlocked){ dc.SetPen(wxPen(wxColour("ACI-LightBlue"), 8)); }
					else{ dc.SetPen(wxPen(wxColour("ACI-Blue"), 8)); }
					int XPOS = ((*curr)->loc[0]*150)+100, YPOS = ((*curr)->loc[1]*200)+100;//Centered on boxes
					XPOS += 100 + 1 - 150, YPOS += 4;
					DrawLine(dc, XPOS, YPOS, true, -150);
				}
			}
		
		
			//DRAWING
		}
	}
	
	/*dc.SetBrush(wxBrush(wxTransparentColour, wxBRUSHSTYLE_TRANSPARENT));
	//wxPen TP = dc.GetPen();
	dc.SetPen(wxPen(wxColour(204,211,229), 8));
	for(std::list<TreeBranch*>::const_iterator curr = Tree->TreeBranches.begin(), last = Tree->TreeBranches.end(); curr != last; ++curr)
	{
		if(!(*curr)->Children.empty())
		{
			//if((*curr)->RankBlock != ""){ XPOS += ((*curr)->RankBlockOffset[0])*150, YPOS += ((*curr)->RankBlockOffset[1])*200; }
			//dc.DrawRectangle(wxRect(XPOS-50, YPOS-50, 100, 100));
			for(std::list<vector<int> >::const_iterator child = (*curr)->Children.begin(); child != (*curr)->Children.end(); ++child)
			{
				int XPOS = ((*curr)->loc[0]*150)+100, YPOS = ((*curr)->loc[1]*200)+100;//Centered on boxes
				XPOS += 100 - 1, YPOS += 4;
				if((*child)[1] < (*curr)->loc[1])
				{
					XPOS += 1 - 50;
					DrawArc(dc, XPOS, YPOS, LEFT, UP);
					//dc.DrawArc(XPOS+2-50, YPOS, XPOS+2-25, YPOS-25, XPOS+2-50, YPOS-25);
					DrawLine(dc, XPOS, YPOS, 1, (((*child)[1] - (*curr)->loc[1])*8)+2);
					//dc.DrawLine(XPOS+2-25, YPOS-25, XPOS+2-25, YPOS+25+(((*child)[1] - (*curr)->loc[1])*200));
					//dc.DrawLine(XPOS-52-2, YPOS-1, XPOS-45, YPOS-1);
					////XPOS += 150*((*child)[0] - (*curr)->loc[0]), 
					//XPOS += 1, YPOS += 200*((*child)[1] - (*curr)->loc[1]);
					//dc.DrawArc(XPOS, YPOS, XPOS-25, YPOS+25, XPOS, YPOS+25);
					DrawArc(dc, XPOS, YPOS, DOWN, RIGHT);
				}
				else if((*child)[1] > (*curr)->loc[1])
				{
					XPOS += 1 - 50, YPOS += 0;
					DrawArc(dc, XPOS, YPOS, LEFT, DOWN);
					DrawLine(dc, XPOS, YPOS, 1, (((*child)[1] - (*curr)->loc[1]) * 8) - 2);
					DrawArc(dc, XPOS, YPOS, UP, RIGHT);
				}
				else if((*child)[1] == (*curr)->loc[1])
				{
					XPOS -= 50;
					DrawLine(dc, XPOS, YPOS, 0, 1);
					XPOS -= 23;
					DrawLine(dc, XPOS, YPOS, 0, (((*child)[0] - (*curr)->loc[0])*6)-4);
					//dc.DrawLine(XPOS-50, YPOS, XPOS+(((*child)[0] - (*curr)->loc[0])*150)-150+2,YPOS);
				}
			}
			//dc.SetPen(TP);
			//Forgive me for what I must do
			if((*curr)->loc[0] == 1 && (*curr)->loc[1] == 6)//MiG-21
			{
				int XPOS = ((*curr)->loc[0]*150)+100, YPOS = ((*curr)->loc[1]*200)+100;//Centered on boxes
				XPOS += 100 + 1, YPOS += 4;
				DrawLine(dc, XPOS, YPOS, 0, 4);
				DrawArc(dc, XPOS, YPOS, LEFT, UP);
				DrawLine(dc, XPOS, YPOS, 1, -22);
				DrawArc(dc, XPOS, YPOS, DOWN, RIGHT);				
			}
			else if((*curr)->loc[0] == 7 && (*curr)->loc[1] == 3)//Gun Range + S, Air Seek +
			{
				int XPOS = ((*curr)->loc[0]*150)+100, YPOS = ((*curr)->loc[1]*200)+100;//Centered on boxes
				XPOS += 100 + 1 + 100, YPOS += 4;
				DrawArc(dc, XPOS, YPOS, LEFT, UP);
				DrawLine(dc, XPOS, YPOS, 1, -6);
				DrawArc(dc, XPOS, YPOS, DOWN, RIGHT);
			}
			else if((*curr)->loc[0] == 8 && (*curr)->loc[1] == 4)//Roll+ M
			{
				int XPOS = ((*curr)->loc[0]*150)+100, YPOS = ((*curr)->loc[1]*200)+100;//Centered on boxes
				XPOS += 100 + 1 - 150, YPOS += 4;
				DrawLine(dc, XPOS, YPOS, 0, -6);
			}
			else if((*curr)->loc[0] == 11 && (*curr)->loc[1] == 14)//Su-34
			{
				int XPOS = ((*curr)->loc[0]*150)+100, YPOS = ((*curr)->loc[1]*200)+100;//Centered on boxes
				XPOS += 100 + 1 - 150, YPOS += 4;
				DrawLine(dc, XPOS, YPOS, 0, -6);
			}
		}
	}*/
	
	dc.SetPen(wxPen(wxColour(0,0,0), 1));
	dc.SetBrush(wxBrush(wxColour(64,64,64)));
	for(std::list<TreeBranch*>::const_iterator curr = RTree->TreeBranches.begin(), last = RTree->TreeBranches.end(); curr != last; ++curr)
	{
		if((*curr)->RankBlock != "")
		{
			wxString RankBlock((*curr)->RankBlock);
			int XPOS = (((*curr)->loc[0]+(*curr)->RankBlockOffset[0])*150) + 50, YPOS = (((*curr)->loc[1]+(*curr)->RankBlockOffset[1])*200)+50;
			XPOS += 12, YPOS += 12;
			dc.DrawRectangle(XPOS, YPOS,76,76);
			wxFont T = dc.GetFont();
			while(dc.GetTextExtent(RankBlock.AfterLast('&')).GetWidth() > 70){ dc.SetFont(MakePanelFont(dc.GetFont().GetPointSize()-1)); }
			dc.DrawText(RankBlock.BeforeLast('&'), XPOS+3, YPOS-8+(75-dc.GetFont().GetPointSize()*2));
			dc.DrawText(RankBlock.AfterLast('&'), XPOS+3, YPOS-8+(75-dc.GetFont().GetPointSize()));
			dc.SetFont(T);
		}
		
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
	//delete Image;
	//Image = new wxBitmap(width, height, dc);
	
	return;
	
}

wxColour ResearchTreeWindow::GetNodeColor(TreeNode *Node)
{
	switch(Node->nodetype)
	{
		case(0):
			return wxColour(0,0,0);
		case(1):
			if(Node->aquired){ return wxColour(211,160,53); }
			else{ return wxColour(98,75,33); }
		case(2):
			if(Node->aquired){ return wxColour(185,69,54); }
			else{ return wxColour(93,36,26); }
		case(3):
			if(Node->aquired){ return wxColour(38,111,190); }
			else{ return wxColour(0,49,112); }
		case(4):
			if(Node->aquired){ return wxColour(163,89,184); }
			else{ return wxColour(63,42,103); }
		case(5):
			if(Node->aquired){ return wxColour(0,0,0); }
			else{ return wxColour(0,0,0); }
		case(6):
			if(Node->aquired){ return wxColour(185,69,54); }
			else{ return wxColour(185,69,54);; }
		case(7):
			if(Node->aquired){ return wxColour(38,111,190); }
			else{ return wxColour(38,111,190); }
		case(8):
			if(Node->aquired){ return wxColour(134,187,109); }
			else{ return wxColour(134,187,109); }
		case(9):
			if(Node->aquired){ return wxColour(163,89,184); }
			else{ return wxColour(163,89,184); }
		case(10):
			if(Node->aquired){ return wxColour(0,0,0); }
			else{ return wxColour(0,0,0); }
	}
	return wxColour(0,0,0);
}

wxFontInfo ResearchTreeWindow::MakePanelFont(int size = 10)
{
	wxFontInfo TF(size);
	TF.Family(wxFONTFAMILY_MODERN);
	TF.Bold(true);
	return TF;
}

void ResearchTreeWindow::DrawLine(wxDC &dc, int &XPOS, int &YPOS, bool horizontal, int dist)
{
	wxPen TP = dc.GetPen();
	wxBrush TB = dc.GetBrush();
	dc.SetPen((*wxTRANSPARENT_PEN));
	dc.SetBrush(TP.GetColour());
	if(horizontal)
	{
		dc.DrawRectangle(XPOS, YPOS-4, dist, TP.GetWidth());
		XPOS += dist;
	}
	else
	{
		dc.DrawRectangle(XPOS-4, YPOS, TP.GetWidth(), dist);
		YPOS += dist;
	}
	dc.SetPen(TP);
	dc.SetBrush(TB);
	return;
}
void ResearchTreeWindow::DrawArc(wxDC &dc, int &XPOS, int &YPOS, Dir From, Dir To)
{
	wxPen TP = dc.GetPen();
	wxBrush TB = dc.GetBrush();
	dc.SetPen((*wxTRANSPARENT_PEN));
	dc.SetBrush(wxBrush(TP.GetColour()));
	wxPoint e(XPOS,YPOS), center(XPOS,YPOS);
	switch(From)
	{
		case(UP):
			if(To == LEFT)
			{
				e.x = XPOS - 25, e.y = YPOS + 25;
				dc.DrawRectangle(XPOS-5, YPOS-4, 8, 8);
				dc.DrawRectangle(e.x-4, e.y-5, 8, 8);
			}
			else
			{
				XPOS -= 1, YPOS += 2;
				e.x = XPOS + 25, e.y = YPOS + 25;
				dc.DrawRectangle(XPOS-3, YPOS-4, 8, 8);
				dc.DrawRectangle(e.x-4, e.y-5, 8, 8);
			}
			center.x = e.x;
			center.y = YPOS;
			break;
		case(DOWN):
			if(To == LEFT)
			{
				e.x = XPOS - 25, e.y = YPOS - 25;
				dc.DrawRectangle(XPOS-5, YPOS-4, 8, 8);
				dc.DrawRectangle(e.x-4, e.y-3, 8, 8);
			}
			else
			{
				XPOS -= 1, YPOS -= 2;
				e.x = XPOS + 25, e.y = YPOS - 25;
				dc.DrawRectangle(XPOS-3, YPOS-4, 8, 8);
				dc.DrawRectangle(e.x-4, e.y-3, 8, 8);
			}
			center.x = e.x;
			center.y = YPOS;
			break;
		case(LEFT):
			if(To == UP)
			{
				XPOS += 1-1, YPOS += 1-1;
				e.x = XPOS + 25, e.y = YPOS - 25;
				dc.DrawRectangle(XPOS-4, YPOS-5, 8, 8);
				dc.DrawRectangle(e.x-5, e.y-4, 8, 8);
			}
			else
			{
				XPOS += 1, YPOS -= 1;
				e.x = XPOS + 25, e.y = YPOS + 25;
				dc.DrawRectangle(XPOS-4, YPOS-3, 8, 8);
				dc.DrawRectangle(e.x-5, e.y-4, 8, 8);
			}
			center.x = XPOS;
			center.y = e.y;
			break;
		case(RIGHT):
			if(To == UP)
			{
				e.x = XPOS - 25, e.y = YPOS - 25;
				dc.DrawRectangle(XPOS-4, YPOS-5, 8, 8);
				dc.DrawRectangle(e.x-3, e.y-4, 8, 8);
			}
			else
			{
				e.x = XPOS - 25, e.y = YPOS + 25;
				dc.DrawRectangle(XPOS-4, YPOS-3, 8, 8);
				dc.DrawRectangle(e.x-3, e.y-4, 8, 8);
			}
			center.x = XPOS;
			center.y = e.y;
			break;
	}
	dc.SetPen(wxPen(TP.GetColour(), 8));
	dc.SetBrush(wxBrush(wxTransparentColour, wxBRUSHSTYLE_TRANSPARENT));
	if((From == LEFT && To == UP) || (From == UP && To == RIGHT) || (From == RIGHT && To == DOWN) || (From == DOWN && To == LEFT)){ dc.DrawArc(XPOS, YPOS, e.x, e.y, center.x, center.y); }
	else{ dc.DrawArc(e.x, e.y, XPOS, YPOS, center.x, center.y); }
	XPOS = e.x, YPOS = e.y;
	dc.SetPen(TP);
	dc.SetBrush(TB);
	return;
}

/*
void ResearchTreeWindow::DrawLine(wxDC &dc, int &XPOS, int &YPOS, int orient, int units)
{
	if(orient)
	{
		dc.DrawLine(XPOS, YPOS, XPOS, YPOS+(units*25));
		dc.DrawPoint(XPOS+3, YPOS-3);
		dc.DrawPoint(XPOS-3, YPOS-3);
		dc.DrawPoint(XPOS-4, YPOS-3);
		dc.DrawPoint(XPOS-4, YPOS-2);
		dc.DrawPoint(XPOS-4, YPOS-1);
		YPOS += units*25;		
		dc.DrawPoint(XPOS+3, YPOS+3);
		dc.DrawPoint(XPOS-3, YPOS+3);
		dc.DrawPoint(XPOS-4, YPOS+3);
		dc.DrawPoint(XPOS-4, YPOS+2);
		dc.DrawPoint(XPOS-4, YPOS+1);
	}
	else
	{
		dc.DrawLine(XPOS, YPOS, XPOS+(units*25), YPOS);
		dc.DrawPoint(XPOS-5, YPOS+3);
		dc.DrawPoint(XPOS-5, YPOS-3);
		dc.DrawPoint(XPOS-5, YPOS-4);
		dc.DrawPoint(XPOS-4, YPOS-4);
		dc.DrawPoint(XPOS-3, YPOS-4);
		XPOS += units*25;
		dc.DrawPoint(XPOS+3, YPOS+3);
		dc.DrawPoint(XPOS+3, YPOS-3);
		dc.DrawPoint(XPOS+3, YPOS-4);
		dc.DrawPoint(XPOS+2, YPOS-4);
		dc.DrawPoint(XPOS+1, YPOS-4);
		dc.DrawPoint(XPOS, YPOS-4);
	}
	return;
}

void ResearchTreeWindow::DrawArc(wxDC &dc, int &XPOS, int &YPOS, Dir From, Dir To)
{
	//wxPen TP = dc.GetPen();
	//dc.SetPen(wxPen(wxColour(50,50,50), TP.GetWidth()));
	wxPoint e(XPOS,YPOS), center(XPOS,YPOS);
	switch(From)
	{
		case(UP):
			if(To == LEFT)
			{
				e.x = XPOS - 25, e.y = YPOS + 25;
				dc.DrawPoint(XPOS, YPOS);
			}
			else
			{
				XPOS -= 1, YPOS += 2;
				e.x = XPOS + 25, e.y = YPOS + 25;
				dc.DrawPoint(XPOS-3, YPOS-3);
				dc.DrawPoint(XPOS-3, YPOS-4);
				dc.DrawPoint(XPOS-2, YPOS-4);
				dc.DrawPoint(XPOS+2, YPOS-4);
				dc.DrawPoint(XPOS+3, YPOS-4);
				dc.DrawPoint(XPOS+3, YPOS-3);
				
				dc.DrawPoint(e.x+2, e.y+2);
				dc.DrawPoint(e.x+3, e.y+2);
				dc.DrawPoint(e.x+3, e.y+1);
				dc.DrawPoint(e.x+3, e.y-3);
				dc.DrawPoint(e.x+3, e.y-4);
				dc.DrawPoint(e.x+2, e.y-4);
				dc.DrawPoint(e.x+3, e.y-5);
				dc.DrawPoint(e.x+2, e.y-5);
				dc.DrawPoint(e.x+1, e.y-5);
				dc.DrawPoint(e.x, e.y-5);
			}
			center.x = e.x;
			center.y = YPOS;
			break;
		case(DOWN):
			if(To == LEFT)
			{
				e.x = XPOS - 25, e.y = YPOS - 25;
				dc.DrawPoint(XPOS, YPOS);
			}
			else
			{
				XPOS -= 1, YPOS -= 2;
				e.x = XPOS + 25, e.y = YPOS - 25;
				dc.DrawPoint(XPOS-3, YPOS+3);
				dc.DrawPoint(XPOS-2, YPOS+3);
				dc.DrawPoint(XPOS+4, YPOS);
				dc.DrawPoint(XPOS+4, YPOS+1);
				dc.DrawPoint(XPOS+4, YPOS+2);
				dc.DrawPoint(XPOS+4, YPOS+3);
				dc.DrawPoint(XPOS+3, YPOS+2);
				dc.DrawPoint(XPOS+3, YPOS+3);
				dc.DrawPoint(XPOS+2, YPOS+3);
				
				dc.DrawPoint(e.x+2, e.y-3);
				dc.DrawPoint(e.x+3, e.y-3);
				dc.DrawPoint(e.x+3, e.y-2);
				dc.DrawPoint(e.x+3, e.y+2);
				dc.DrawPoint(e.x+3, e.y+3);
				dc.DrawPoint(e.x+2, e.y+3);
				dc.DrawPoint(e.x+3, e.y+4);
				dc.DrawPoint(e.x+2, e.y+4);
				dc.DrawPoint(e.x+1, e.y+4);
				dc.DrawPoint(e.x, e.y+4);
			}
			center.x = e.x;
			center.y = YPOS;
			break;
		case(LEFT):
			if(To == UP)
			{
				XPOS += 1, YPOS += 1;
				e.x = XPOS + 25, e.y = YPOS - 25;
				dc.DrawPoint(XPOS-3, YPOS+2);
				dc.DrawPoint(XPOS-4, YPOS+2);
				dc.DrawPoint(XPOS-4, YPOS+1);
				dc.DrawPoint(XPOS-4, YPOS-3);
				dc.DrawPoint(XPOS-4, YPOS-4);
				dc.DrawPoint(XPOS-3, YPOS-4);
				dc.DrawPoint(XPOS-4, YPOS-5);
				dc.DrawPoint(XPOS-3, YPOS-5);
				dc.DrawPoint(XPOS-2, YPOS-5);
				dc.DrawPoint(XPOS-1, YPOS-5);
				
				dc.DrawPoint(e.x-5, e.y-1);
				dc.DrawPoint(e.x-5, e.y-2);
				dc.DrawPoint(e.x-5, e.y-3);
				dc.DrawPoint(e.x-5, e.y-4);
				dc.DrawPoint(e.x-4, e.y-3);
				dc.DrawPoint(e.x-4, e.y-4);
				dc.DrawPoint(e.x-3, e.y-4);
				dc.DrawPoint(e.x+1, e.y-4);
				dc.DrawPoint(e.x+2, e.y-4);
				dc.DrawPoint(e.x+2, e.y-3);
			}
			else
			{
				XPOS += 1, YPOS -= 1;
				e.x = XPOS + 25, e.y = YPOS + 25;
				dc.DrawPoint(XPOS-1, YPOS+4);
				dc.DrawPoint(XPOS-2, YPOS+4);
				dc.DrawPoint(XPOS-3, YPOS+4);
				dc.DrawPoint(XPOS-3, YPOS+3);
				dc.DrawPoint(XPOS-4, YPOS+4);
				dc.DrawPoint(XPOS-4, YPOS+3);
				dc.DrawPoint(XPOS-4, YPOS+2);
				dc.DrawPoint(XPOS-4, YPOS-2);
				dc.DrawPoint(XPOS-4, YPOS-3);
				dc.DrawPoint(XPOS-3, YPOS-3);
				
				dc.DrawPoint(e.x-5, e.y);
				dc.DrawPoint(e.x-5, e.y+1);
				dc.DrawPoint(e.x-5, e.y+2);
				dc.DrawPoint(e.x-5, e.y+3);
				dc.DrawPoint(e.x-4, e.y+3);
				dc.DrawPoint(e.x+1, e.y+3);
				dc.DrawPoint(e.x+2, e.y+3);
				dc.DrawPoint(e.x+2, e.y+2);
			}
			center.x = XPOS;
			center.y = e.y;
			break;
		case(RIGHT):
			if(To == UP)
			{
				e.x = XPOS - 25, e.y = YPOS - 25;
				dc.DrawPoint(XPOS, YPOS);
			}
			else
			{
				e.x = XPOS - 25, e.y = YPOS + 25;
				dc.DrawPoint(XPOS, YPOS);
			}
			center.x = XPOS;
			center.y = e.y;
			break;
	}
	if((From == LEFT && To == UP) || (From == UP && To == RIGHT)){ dc.DrawArc(XPOS, YPOS, e.x, e.y, center.x, center.y); }
	else{ dc.DrawArc(e.x, e.y, XPOS, YPOS, center.x, center.y); }
	//std::cout << XPOS << " | " << YPOS << endl << std::flush;
	//dc.SetPen(wxPen(wxColour(0,0,0), TP.GetWidth()));
	//dc.DrawPoint(XPOS, YPOS);
	//dc.DrawPoint(e.x, e.y);
	XPOS = e.x, YPOS = e.y;
	//std::cout << XPOS << " | " << YPOS << endl << std::flush;
	//dc.SetPen(TP);
	return;
}
*/

void ResearchTreeWindow::onLeftClick(wxMouseEvent& event)
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
					if(curr->branch->loc[0] == 0){ break; }
					if(curr->node->aquired)
					{
						curr->node->aquired = false;
						curr->node->level = 0;
						curr->branch->UpdateUnlocked();
					}
					else
					{
						if(curr->branch->unlocked)
						{
							curr->node->aquired = true, curr->node->level = 1;
							for(std::list<TreeBranch*>::const_iterator B = curr->branch->ChildBranches.begin(), L = curr->branch->ChildBranches.end(); B != L; ++B)
							{
								(*B)->UpdateUnlocked();
							}
						}
					}
					break;
				case(LEVEL):
					if(curr->node->nodetype != 1 && curr->node->aquired && curr->node->level < curr->node->maxlevel){ curr->node->level++; }
					break;
				case(DELEVEL):
					if(curr->node->nodetype != 1 && curr->node->aquired && curr->node->level > 1){ curr->node->level--; }
					break;
			}
			break;
		}
	}
	UpdateImage();
	Refresh();
	return;
}

void ResearchTreeWindow::onRightClick(wxMouseEvent& event)
{
	wxUnusedVar(event);
	if(!edit){ return; }
	wxMenu menu;
	menu.AppendRadioItem(0, "None");
	menu.AppendRadioItem(1, "Unlock");
 	menu.AppendRadioItem(2, "Level");
 	menu.AppendRadioItem(3, "Delevel");
	menu.Check(emode, true);
 	menu.Connect(wxEVT_COMMAND_MENU_SELECTED, (wxObjectEventFunction)&ResearchTreeWindow::OnPopupClick, NULL, this);
 	PopupMenu(&menu);
	return;
}

void ResearchTreeWindow::OnPopupClick(wxCommandEvent &evt)
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