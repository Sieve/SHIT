#ifndef SPECIALWEAPONWINDOW_H
#define SPECIALWEAPONWINDOW_H

#include "SHITScrolledWindow.h"


class SpecialWeaponWindow : public SHITScrolledWindow
{
public:
	SpecialWeaponWindow(wxWindow *parent, list<TreeNode> *D);
	~SpecialWeaponWindow();
	void OnDraw(wxDC &dc);
	void UpdateImage();
	void onRightClick(wxMouseEvent& event);
	void onLeftClick(wxMouseEvent& event);
	void OnPopupClick(wxCommandEvent &evt);

};

#endif // SPECIALWEAPONWINDOW_H
