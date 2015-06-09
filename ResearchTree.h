#ifndef RESEARCHTREE_H
#define RESEARCHTREE_H
#include "wxcrafter.h"
#include "DataStructs.h"
#include "ResearchTreeWindow.h"

class ResearchTree : public ResearchTreeBaseClass
{
public:
    ResearchTree(wxWindow* parent, TreeBase *B);
    //~ResearchTree();
	
	ResearchTreeWindow *DisplayWindow;
	//wxSizer *Sizer;
	
	int ZoomLevel;
	float ZoomLevels[3];
	
protected:
    virtual void onClose(wxCloseEvent& event);
    virtual void onEdit(wxCommandEvent& event);
    virtual void onSaveData(wxCommandEvent& event);
    virtual void onSavePNG(wxCommandEvent& event);
    //virtual void onClose(wxCloseEvent& event);
    virtual void onZoomIn(wxCommandEvent& event);
    virtual void onZoomOut(wxCommandEvent& event);
    //virtual void onPaint(wxPaintEvent& event);
};
#endif // RESEARCHTREE_H
