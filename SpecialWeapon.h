#ifndef SPECIALWEAPON_H
#define SPECIALWEAPON_H

#include "wxcrafter.h"
#include "SpecialWeaponWindow.h"

class SpecialWeapon : public SpecialWeaponBaseClass
{
public:
    SpecialWeapon(wxWindow* parent, list<TreeNode> *D);
    //virtual ~SpecialWeapon();
	
	SpecialWeaponWindow *DisplayWindow;
	int ZoomLevel;
	float ZoomLevels[3];
	
protected:
    virtual void onClose(wxCloseEvent& event);
    virtual void onEdit(wxCommandEvent& event);
    virtual void onSaveData(wxCommandEvent& event);
    virtual void onSavePNG(wxCommandEvent& event);
    virtual void onZoomIn(wxCommandEvent& event);
    virtual void onZoomOut(wxCommandEvent& event);
};
#endif // SPECIALWEAPON_H
