#include "SetPanel.h"
#include <wx/msw/brush.h>
#include <wx/msw/colour.h>
#include <wx/dcclient.h>
#include <wx/dcmemory.h>
#include <wx/gdicmn.h>
#include "resources/icons/Attacker.xpm"
#include "resources/icons/Bomber.xpm"
#include "resources/icons/Fighter.xpm"
#include "resources/icons/Multirole.xpm"
#include "resources/icons/SPW.xpm"

SetPanel::SetPanel(wxWindow *parent, wxWindowID id, const wxPoint &pos, const wxSize &size, long style, const wxString &name)
	: wxPanel(parent, id, pos, size, style, name)
{
	wxImage::AddHandler( new wxXPMHandler );
	Plane = nullptr;
	Image.Create(size);
	Bind(wxEVT_PAINT, &SetPanel::OnPaint, this);
	UpdateImage();
}

SetPanel::~SetPanel()
{
	Unbind(wxEVT_PAINT, &SetPanel::OnPaint, this);
}

void SetPanel::OnPaint(wxPaintEvent& event)
{
	wxPaintDC dc(this);
	dc.DrawBitmap(Image,0,0,false);
	return;
}

void SetPanel::UpdateNode(TreeNode* N)
{
	Plane = N;
	//for(std::list<TreeNode*>::iterator curr = Parts.begin(); curr != Parts.end(); curr++)
	//{
		//Parts.remove(curr);
	//}
	if(N == nullptr){ SPW = nullptr; }
	/*else
	{
		wxString SP1(N->PI->SP1Name);
		wxString SP2(N->PI->SP2Name);
		wxString SP3(N->PI->SP3Name);
		for(std::list<TreeNode>::iterator curr = SPWs->begin(), last = SPWs->end(); curr != last; ++curr)
		{
			if(SP1.IsSameAs(curr->name))
			{
				SPW = &(*curr);
				SPWs->push_back(&(*curr));
			}
		}
		for(std::list<TreeNode>::iterator curr = SPWs->begin(), last = SPWs->end(); curr != last; ++curr)
		{
			if(SP2.IsSameAs(curr->name)){ SPWs->push_back(&(*curr)); }
		}
		for(std::list<TreeNode>::iterator curr = SPWs->begin(), last = SPWs->end(); curr != last; ++curr)
		{
			if(SP3.IsSameAs(curr->name)){ SPWs->push_back(&(*curr)); }
		}
		
	}*/
	return;
}

void SetPanel::UpdateWeapon(TreeNode* W)
{
	SPW = W;
	return UpdateImage();
}

void SetPanel::UpdateImage()
{
	wxMemoryDC dc(Image);
	if(!dc.IsOk()){ return; }
	dc.SetBrush(wxColour("ACI-DarkBlue"));
	dc.SetPen((*wxTRANSPARENT_PEN));
	dc.SetFont(wxFontInfo(16).Family(wxFONTFAMILY_MODERN).Bold(true));
	dc.SetTextForeground(wxColour("ACI-LightBlue"));
	dc.DrawRectangle(0, 0, Image.GetWidth(), Image.GetHeight());
	
	int XPOS = 1 + 10, YPOS = 1 + 7;
	//dc.DrawText("[Custom Set]", XPOS, YPOS);
	
	//YPOS += 25;
	if(Plane != nullptr)
	{
		//dc.DrawBitmap();
		wxString T(Plane->name);
		switch(Plane->nodetype)
		{
			case(ATTACKER):
				dc.DrawBitmap(wxBitmap(ATTACKER_xpm), XPOS-3-2, YPOS);
				T << " / ATTACKER";
				break;
			case(FIGHTER):
				dc.DrawBitmap(wxBitmap(FIGHTER_xpm), XPOS-3-2, YPOS);
				T << "/FIGHTER";
				break;
			case(MULTIROLE):
				dc.DrawBitmap(wxBitmap(MULTIROLE_xpm), XPOS-3-2, YPOS);
				T << "/MULTIROLE";
				break;
			case(BOMBER):
				T << "/BOMBER";
				break;
		}
		dc.DrawText(T, XPOS + 16 + 4, YPOS);
		T = "Lv.";
		T << Plane->level;
		dc.DrawText(T, Image.GetWidth() - 4 - dc.GetTextExtent(T).GetWidth(), YPOS);
	}
	
	//YPOS += 22;
	YPOS = 40;
	if(Plane != nullptr)
	{
		dc.DrawBitmap(wxBitmap(SPW_xpm), XPOS - 5, YPOS);
		dc.DrawText(SPW->name, XPOS + 16, YPOS);
		wxString T = "Lv.";
		T << SPW->level;
		dc.DrawText(T, Image.GetWidth() - 4 - dc.GetTextExtent(T).GetWidth(), YPOS);
	}
	
	//YPOS += 20;
	YPOS = 75;
	dc.SetPen(wxPen(wxColour(56,75,101), 1));
	dc.SetBrush(wxColour("ACI-DarkBlue"));
	std::list<TreeNode*>::const_iterator curr = Parts.begin();
	for(int i = 0; i < 7; i++)
	{
		dc.DrawRectangle(XPOS+(41*i)-3, YPOS, 42, 42);
		if(curr != Parts.end())
		{
			//dc.DrawIcon()
			curr++;
		}
	}
	
	Refresh();
	return;
}
