#include <wx/wx.h>

#include "ImagePanel.h"
#include <wx/msw/brush.h>
#include <wx/msw/colour.h>
#include "resources/icons/progress_under.xpm"

///////////////////////////////////////////////////////////////////////////////////////////////////
//ImagePanel::ImagePanel(wxWindow *parent, wxString path, int p) :
//wxPanel(parent), img(path), bitmap(img) {
ImagePanel::ImagePanel(wxWindow *parent, int p):wxPanel(parent){
///////////////////////////////////////////////////////////////////////////////////////////////////
        wxImage::AddHandler( new wxXPMHandler );
		bitmap = wxBitmap(progress_under_xpm);
		// get the image size
        width  = bitmap.GetWidth();
        height = bitmap.GetHeight();
		progress = p;
		SetDoubleBuffered(true);

        // set the size of the panel accordingly
        SetSize(width, height);

        Connect(wxEVT_PAINT, wxPaintEventHandler(ImagePanel::OnPaint));
}

ImagePanel::~ImagePanel()
{
	Disconnect(wxEVT_PAINT, wxPaintEventHandler(ImagePanel::OnPaint));
}

///////////////////////////////////////////////
void ImagePanel::OnPaint(wxPaintEvent& event) {
///////////////////////////////////////////////
        wxPaintDC dc(this);
        dc.DrawBitmap(bitmap,0,0,true);
		dc.SetBrush(wxBrush(wxColour(153,172,202)));
		dc.SetPen(wxPen(wxColour(153,172,202), 0));
		dc.DrawRectangle(wxRect(wxSize(progress, 15)));
} 

///////////////////////////////////////////////
void ImagePanel::DrawProgress(int p) {
///////////////////////////////////////////////
        progress = p;
		Connect(wxEVT_PAINT, wxPaintEventHandler(ImagePanel::OnPaint));
} 