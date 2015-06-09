#ifndef RESEARCHTREEWINDOW_H
#define RESEARCHTREEWINDOW_H

#include "SHITScrolledWindow.h"
#include "wxcrafter.h"
#include "DataStructs.h"
#include <wx/scrolwin.h>
#include <wx/colour.h>

class ResearchTreeWindow : public wxScrolledWindow
{
public:
	ResearchTreeWindow(wxWindow *parent, TreeBase *B);
	~ResearchTreeWindow();
	wxColour GetNodeColor(TreeNode *Node);
	void UpdateImage();
	void OnDraw(wxDC &dc);
	wxFontInfo MakePanelFont(int size);
	//Length = Units * 25, 0 orient == horizontal
	void DrawLine(wxDC &dc, int &XPOS, int &YPOS, bool horizontal = true, int dist = 0);
	void DrawArc(wxDC &dc, int &XPOS, int &YPOS, Dir From, Dir To);
	//void DrawLine(wxDC &dc, int &XPOS, int &YPOS, int orient = 0, int units = 1);
	//void DrawArc(wxDC &dc, int &XPOS, int &YPOS, Dir From, Dir To);
	void OnPopupClick(wxCommandEvent &evt);
	
	virtual void onLeftClick(wxMouseEvent& event);
	virtual void onRightClick(wxMouseEvent& event);
	
	
	wxBitmap Image;
	TreeBase *RTree;
	std::list<HitZone> HitZones;
	bool first;
	bool update;
	bool edit;
	editmode emode;
	int width;
	int height;
	int fontsize;
	float scale;
	float lastscale;
	
protected:
    //virtual void onPaint(wxPaintEvent& event);
	

};

#endif // RESEARCHTREEWINDOW_H
