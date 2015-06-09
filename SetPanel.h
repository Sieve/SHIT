#ifndef SETPANEL_H
#define SETPANEL_H

#include "wx/panel.h"
#include "DataStructs.h"
#include <list>
#include <wx/wx.h>

class SetPanel : public wxPanel
{
public:
	SetPanel(wxWindow *parent, wxWindowID id=wxID_ANY, const wxPoint &pos=wxDefaultPosition, const wxSize &size=wxDefaultSize, long style=wxTAB_TRAVERSAL, const wxString &name=wxPanelNameStr);
	~SetPanel();
	void SetNode();
	void UpdateImage();
	void UpdateNode(TreeNode* N = nullptr);
	void UpdateWeapon(TreeNode* W = nullptr);
	
	wxBitmap Image;
	TreeNode *Plane;
	TreeNode *SPW;
	//std::list<TreeNode> *SPWs;
	//std::list<TreeNode*> ValidSPWs;
	std::list<TreeNode*> Parts;

protected:
	void OnPaint(wxPaintEvent& event);

};

#endif // SETPANEL_H