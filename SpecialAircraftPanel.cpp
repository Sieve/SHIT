/*#include "SpecialAircraftPanel.h"
#include <wx/colour>
#include <wx/msw/brush.h>

SpecialAircraftPanel::SpecialAircraftPanel(wxWindow *parent, list<*PlaneInfo> PI):wxPanel(parent)
{
	width = 0;
	height = 0;
	SetBackgroundColour(wxColour(2,13,33));
	SetDoubleBuffered(true);
	SetSize(width, height);
	
	Connect(wxEVT_PAINT, wxPaintEventHandler(SpecialAircraftPanel::OnPaint));
}

void SpecialAircraftPanel::OnPaint(wxPaintEvent& event)
{
	wxPaintDC dc(this);
	dc.SetTextForeground(wxColour(204,211,229));
	dc.SetBrush(wxColour(213,208,202));
	dc.DrawRectangle(wxRect(5,5,98,98))
}

wxColour SpecialAircraftPanel::GetNodeColor(PlaneInfo *PI)
{
	if(PI->Role == wxT("ATTACKER")){ return wxColour(185,69,54); }
	else if(PI->Role == wxT("FIGHTER")){ return wxColour(38,111,190); }
	else if(PI->Role == wxT("MULTIROLE")){ return wxColour(163,89,184); }
	return wxColour(0,0,0);
}*/