/*#ifndef __TREEPANEL_H__
#define __TREEPANEL_H__

#include <wx/panel.h> // Base class: wxPanel
#include <wx/wx.h>
#include <wx/msw/colour.h>
#include "DataStructs.h"

class TreePanel : public wxPanel
{
public:
	TreePanel(wxWindow *parent, TreeBase *B);
	~TreePanel(){}
	
	void OnPaint(wxPaintEvent& event);
	wxColour GetNodeColor(TreeNode *Node);
	
	int width;
	int height;
	TreeBase *Tree;

};

#endif // TREEPANEL_H
*/