#ifndef SETBUILDER_H
#define SETBUILDER_H
#include "wxcrafter.h"
#include "SetPanel.h"
#include "DataStructs.h"
#include <wx/event.h>

class SetBuilder : public SetBuilderBaseClass
{
public:
    SetBuilder(wxWindow* parent, TreeBase* TB, std::list<TreeNode> *SA, std::list<TreeNode> *SPW);
    virtual ~SetBuilder();
	void Select(int set = 0);
	void UpdatePanels();
	void DrawBar(int bar, wxString grade);//, int value);
	void DrawSlots(int bar, int value);
	
private:
	void onSetBuilder1Click(wxMouseEvent& event){ return Select(1); }
	void onSetBuilder2Click(wxMouseEvent& event){ return Select(2); }
	void onSetBuilder3Click(wxMouseEvent& event){ return Select(3); }
	void onSetBuilder4Click(wxMouseEvent& event){ return Select(4); }

	std::list<TreeNode*> PlaneData;
	std::list<TreeNode*> WeaponData;
	std::list<TreeNode*> PartData;
	
	int selected;
	SetPanel *ActivePanel;
	
	
protected:
	void OnPopupClick(wxCommandEvent &evt);
	void onPlaneSelect(wxCommandEvent& event);
    virtual void onKeyDown(wxKeyEvent& event);
    virtual void onPartSelect(wxCommandEvent& event);
    virtual void onSPWSelect(wxCommandEvent& event);
    virtual void onSavePNG(wxCommandEvent& event);
    virtual void onClearSets(wxCommandEvent& event);
    virtual void onSaveDefault(wxCommandEvent& event);
    virtual void onClose(wxCloseEvent& event);
};
#endif // SETBUILDER_H
