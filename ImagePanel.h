
#ifndef __IMAGE_PANEL_H__
#define __IMAGE_PANEL_H__

#include <wx/wx.h>

class ImagePanel : public wxPanel {

        // a panel with just an image on it - use for displaying logos

        public:
				//ImagePanel(wxWindow *parent, wxString path, int p);
				ImagePanel(wxWindow *parent, int p);
				~ImagePanel();
                void OnPaint(wxPaintEvent& event);
				void Layer(wxBitmap Layer);
				void DrawProgress(int width);

        private:
                //wxImage img;
                wxBitmap bitmap;
                int width;
                int height;
				
				int progress;
};

#endif 