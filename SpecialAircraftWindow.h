#ifndef SPECIALAIRCRAFTWINDOW_H
#define SPECIALAIRCRAFTWINDOW_H

#include "SHITScrolledWindow.h"


class SpecialAircraftWindow : public SHITScrolledWindow
{
public:
	//SpecialAircraftWindow(wxWindow *parent):wxScrolledWindow(parent){}
	SpecialAircraftWindow(wxWindow *parent, list<TreeNode> *D);
	~SpecialAircraftWindow();
	void OnDraw(wxDC &dc);
	void UpdateImage();
	void onRightClick(wxMouseEvent& event);
	void onLeftClick(wxMouseEvent& event);
	void OnPopupClick(wxCommandEvent &evt);

};

#endif // SPECIALAIRCRAFTWINDOW_H
