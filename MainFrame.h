#ifndef MAINFRAME_H
#define MAINFRAME_H

#include "wxcrafter.h"
#include "PlaneInfoHandler.h"
#include "DataStructs.h"
#include "ResearchTree.h"
#include "SpecialAircraft.h"
#include "SpecialWeapon.h"
#include "ImagePanel.h"
#include "SetBuilder.h"
#include "PipBar.h"
#include <wx/dcclient.h>
#include <wx/frame.h>
#include <string>
using namespace std;
#include <list>

class MainFrame : public MainFrameBaseClass
{
public:
    MainFrame(wxWindow* parent);
    virtual ~MainFrame();

    void OnExit(wxCommandEvent& event);
    void OnAbout(wxCommandEvent& event);
	
	void UpdatePlaneSelector();
	void UpdatePlaneData();
	
	int ApproximateValue(string Stat, string Grade);
	
	void LoadFileInResource(int name, int type, DWORD& size, const char*& data);
	
	void Localize(wxString Lang);
	void SetupTree();
	void SetupSpecialAircraft();
	void SetupSpecialWeapons();
	void LoadSaveData();
	
	//PlaneInfoHandler PIH;
	std::list<PlaneInfo> PlaneData;
	std::list<WeaponInfo> SPWData;
	bool SortEvent;
	bool SortNonEvent;
	bool SortDescending;
	
	ImagePanel *SpeedBar;
	ImagePanel *MobilityBar;
	ImagePanel *StabilityBar;
	ImagePanel *AABar;
	ImagePanel *AGBar;
	ImagePanel *DefenseBar;
	
	PipBar *BODYBar;
	PipBar *ARMSBar;
	PipBar *MISCBar;
	
	Localization Locale;
	//std::list<TreeNode*> Nodes;
	TreeBase ResearchTreeData;
	std::list<TreeNode> SpecialAircraftData;
	std::list<TreeNode> SpecialWeaponsData;
	
	std::list<string> Countries;
	std::list<string> Manufacturers;
	std::list<string> SPWs;
	
	ResearchTree *RTree;
	SpecialAircraft *SA;
	SpecialWeapon *SW;
	SetBuilder *SB;
	
protected:
    virtual void onClose(wxCloseEvent& event);
    virtual void onSetBuilderOpen(wxCommandEvent& event);
    virtual void onSpecialAircraftOpen(wxCommandEvent& event);
    virtual void onSpecialWeaponsOpen(wxCommandEvent& event);
    virtual void onTreeOpen(wxCommandEvent& event);
    virtual void CollapseNodes(wxTreeEvent& event);
    virtual void TreeChanged(wxTreeEvent& event);
    virtual void TreeChanging(wxTreeEvent& event);
    virtual void onFilterLevelUpdated(wxSpinEvent& event);
    virtual void onLevelChanged(wxSpinEvent& event);
    virtual void onPlaneSelected(wxCommandEvent& event);
    virtual void onEventSort(wxCommandEvent& event);
    virtual void onFilterOptionChanged(wxCommandEvent& event);
    virtual void onFilterSubOptionChanged(wxCommandEvent& event);
    virtual void onNonEventSort(wxCommandEvent& event);
    virtual void onAscendingClicked(wxCommandEvent& event);
    virtual void onDescendingClicked(wxCommandEvent& event);
    virtual void onFilterToggle(wxCommandEvent& event);
    virtual void onSelectionUpdated(wxCommandEvent& event);
};
#endif // MAINFRAME_H
