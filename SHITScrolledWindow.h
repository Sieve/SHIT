#ifndef SHITSCROLLEDWINDOW_H
#define SHITSCROLLEDWINDOW_H

#include "wxcrafter.h"
#include "DataStructs.h"
#include <wx/scrolwin.h> // Base class: wxScrolledWindow
#include <wx/colour.h>
#include <wx/brush.h>
#include <wx/dcclient.h>
#include <wx/dcmemory.h>
#include <wx/gdicmn.h>

enum editmode
{
	NA,
	UNLOCK,
	LEVEL,
	DELEVEL,
};

class SHITScrolledWindow : public wxScrolledWindow
{
public:
	SHITScrolledWindow(wxWindow *parent, list<TreeNode> *D);
	~SHITScrolledWindow(){}
	//void OnDraw(wxDC &dc);
	wxFontInfo MakePanelFont(int size);
	wxColour GetNodeColor(const TreeNode *Node);
	//void UpdateImage(){}
	
	wxBitmap Image;
	std::list<TreeNode> *data;
	std::list<HitZone> HitZones;
	editmode emode;
	int width;
	int height;
	int fontsize;
	bool update;
	bool first;
	bool edit;
	float scale;
	float lastscale;

};

#endif // SHITSCROLLEDWINDOW_H
