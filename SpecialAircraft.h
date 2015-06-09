#ifndef SPECIALAIRCRAFT_H
#define SPECIALAIRCRAFT_H

#include "wxcrafter.h"
#include "DataStructs.h"
#include <wx/wx.h>
#include <wx/panel.h>
#include "SpecialAircraftWindow.h"

class SpecialAircraft : public SpecialAircraftBaseClass
{
public:
    SpecialAircraft(wxWindow* parent, list<TreeNode> *SA);
    //virtual ~SpecialAircraft();
	SpecialAircraftWindow *DisplayWindow;
	
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
#endif // SPECIALAIRCRAFT_H
