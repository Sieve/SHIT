#include <wx/wx.h>

#include "PipBar.h"
#include <wx/msw/brush.h>
#include <wx/msw/colour.h>
#include <wx/dcbuffer.h>
#include "resources/icons/pips.xpm"
#include "resources/icons/pipbar.xpm"

///////////////////////////////////////////////////////////////////////////////////////////////////
/*PipBar::PipBar(wxWindow *parent, wxString path, int p) :
wxPanel(parent), img(path), bitmap(img) {*/
PipBar::PipBar(wxWindow *parent, int p): wxPanel(parent){
///////////////////////////////////////////////////////////////////////////////////////////////////
		wxImage::AddHandler( new wxXPMHandler );
		bitmap = wxBitmap(pips_xpm);
		// get the image size
        width  = bitmap.GetWidth();
        height = bitmap.GetHeight();
		progress = p;
		SetDoubleBuffered(true);
        // set the size of the panel accordingly
        SetSize(width, height);

        Connect(wxEVT_PAINT, wxPaintEventHandler(PipBar::OnPaint));
}

///////////////////////////////////////////////
void PipBar::OnPaint(wxPaintEvent& event) {
///////////////////////////////////////////////
        wxPaintDC dc(this);
        dc.DrawBitmap(bitmap,0,0,true);
		if(!progress){ return; }
		//wxBitmap pip(wxT("C:\\Users\\Spencer\\Documents\\CodeLiteProjects\\SHIT\\resources\\icons\\pipbar.png"), wxBITMAP_TYPE_PNG);
		wxImage::AddHandler( new wxXPMHandler );
		wxBitmap pip(pipbar_xpm);
		pip.RealizeResource();
		int bar = (40-progress)/2;
		if(progress%2){ dc.DrawBitmap(pip, -(9*(bar)), 0); }
		else{ dc.DrawBitmap(pip, -(9*(bar+1)), 0); }
		dc.DrawBitmap(pip, -(9*(bar+1)), 9);
} 

void PipBar::UpdateBar(int p)
{
	progress = p;
	Connect(wxEVT_PAINT, wxPaintEventHandler(PipBar::OnPaint));
}