
#ifndef __PIP_BAR_H__
#define __PIP_BAR_H__

#include <wx/wx.h>

class PipBar : public wxPanel {

        // a panel with just an image on it - use for displaying logos

        public:
				//PipBar(wxWindow *parent, wxString path, int p);
				PipBar(wxWindow *parent, int p);
                void OnPaint(wxPaintEvent& event);
				void UpdateBar(int p);

        private:
                //wxImage img;
                wxBitmap bitmap;
                int width;
                int height;
				
				int progress;
};

#endif 