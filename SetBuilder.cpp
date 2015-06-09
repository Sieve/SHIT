#include "SetBuilder.h"
#include <wx/msw/brush.h>
#include <wx/msw/colour.h>
#include <wx/dcclient.h>
#include <wx/dcmemory.h>
#include <wx/gdicmn.h>
#include "resources/icons/pips.xpm"
#include "resources/icons/Attacker.xpm"
#include "resources/icons/Bomber.xpm"
#include "resources/icons/Fighter.xpm"
#include "resources/icons/Multirole.xpm"

SetBuilder::SetBuilder(wxWindow* parent, TreeBase* TB, std::list<TreeNode> *SA, std::list<TreeNode> *SPW)
    : SetBuilderBaseClass(parent)
{
	selected = 0;
	wxImage::AddHandler( new wxXPMHandler );
	m_CustomSet1->Bind(wxEVT_LEFT_UP, &SetBuilder::onSetBuilder1Click, this);
	m_CustomSet2->Bind(wxEVT_LEFT_UP, &SetBuilder::onSetBuilder2Click, this);
	m_CustomSet3->Bind(wxEVT_LEFT_UP, &SetBuilder::onSetBuilder3Click, this);
	m_CustomSet4->Bind(wxEVT_LEFT_UP, &SetBuilder::onSetBuilder4Click, this);
	for(std::list<TreeBranch*>::const_iterator B = TB->TreeBranches.begin(), E = TB->TreeBranches.end(); B != E; ++B)
	{
		for(std::list<TreeNode*>::const_iterator curr = (*B)->Nodes.begin(), last = (*B)->Nodes.end(); curr != last; ++curr)
		{
			if((*curr)->nodetype == 1){ PartData.push_back((*curr)); }
			else{ PlaneData.push_back((*curr)); }
		}
	}
	for(std::list<TreeNode>::iterator curr = SA->begin(), last = SA->end(); curr != last; ++curr){ PlaneData.push_back(&(*curr)); }
	for(std::list<TreeNode>::iterator curr = SPW->begin(), last = SPW->end(); curr != last; ++curr){ WeaponData.push_back(&(*curr)); }
	PlaneData.sort(TreeNode_Comparator());
	WeaponData.sort(TreeNode_Comparator());
	PartData.sort(TreeNode_Comparator());
	
	//for(std::list<TreeNode*>::const_iterator curr = PlaneData.begin(), last = PlaneData.end(); curr != last; ++curr){ std::cout << (*curr)->name << endl << std::flush; }
	//std::cout << endl << std::flush;
	//for(std::list<TreeNode*>::const_iterator curr = WeaponData.begin(), last = WeaponData.end(); curr != last; ++curr){ std::cout << (*curr)->name << endl << std::flush; }
	//std::cout << endl << std::flush;
	//for(std::list<TreeNode*>::const_iterator curr = PartData.begin(), last = PartData.end(); curr != last; ++curr){ std::cout << (*curr)->name << endl << std::flush; }
	Select();
	SetFocus();
}

SetBuilder::~SetBuilder()
{
	m_CustomSet1->Unbind(wxEVT_LEFT_UP, &SetBuilder::onSetBuilder1Click, this);
	m_CustomSet2->Unbind(wxEVT_LEFT_UP, &SetBuilder::onSetBuilder2Click, this);
	m_CustomSet3->Unbind(wxEVT_LEFT_UP, &SetBuilder::onSetBuilder3Click, this);
	m_CustomSet4->Unbind(wxEVT_LEFT_UP, &SetBuilder::onSetBuilder4Click, this);
}

void SetBuilder::Select(int set)
{
	if(set < 0){ set = 4; }
	while(set > 4){ set -= 4; }
	ActivePanel = nullptr;
	if(set != 1){ m_CustomSet1Border->SetBackgroundColour(wxColour("ACI-DarkBlue")); }
	else{ m_CustomSet1Border->SetBackgroundColour(wxColour("ACI-Selected")), ActivePanel = m_CustomSet1; }
	if(set != 2){ m_CustomSet2Border->SetBackgroundColour(wxColour("ACI-DarkBlue")); }
	else{ m_CustomSet2Border->SetBackgroundColour(wxColour("ACI-Selected")), ActivePanel = m_CustomSet2; }
	if(set != 3){ m_CustomSet3Border->SetBackgroundColour(wxColour("ACI-DarkBlue")); }
	else{ m_CustomSet3Border->SetBackgroundColour(wxColour("ACI-Selected")), ActivePanel = m_CustomSet3; }
	if(set != 4){ m_CustomSet4Border->SetBackgroundColour(wxColour("ACI-DarkBlue")); }
	else{ m_CustomSet4Border->SetBackgroundColour(wxColour("ACI-Selected")), ActivePanel = m_CustomSet4; }
	selected = set;
	Refresh();
	return;
}

void SetBuilder::UpdatePanels()
{
	if(ActivePanel == nullptr)
	{
		m_PlaneName->SetLabel("[ N/A ]");
		m_Cst->SetLabel("0");
		m_Level->SetLabel("Lv. 0");
		//m_PlaneIcon->SetBitmap(wxBitmap(20, 20)));
		for(int i = 0; i < 6; i++){ DrawBar(i, "F-"); }//, 0); }
		for(int i= 0; i < 3; i++){ DrawSlots(i, 0); }
		m_SPWAmmo->SetLabel("0");
		m_SPWType->SetLabel("N/A");
		m_TDMScore->SetLabel("0");
		m_InstallCost->SetLabel("0");
	}
	else
	{
		wxString Temp = "[ ";
		Temp << ActivePanel->Plane->name << " ]";
		m_PlaneName->SetLabel(Temp);
		Temp = "Cst: ";
		Temp << ActivePanel->Plane->PI->Cost[0][ActivePanel->Plane->level];
		m_Cst->SetLabel(Temp);
		Temp = "Lv. ";
		Temp << ActivePanel->Plane->level;
		m_Level->SetLabel(Temp);
		switch(ActivePanel->Plane->PI->Role)
		{
			case(ATTACKER):
				m_PlaneIcon->SetBitmap(wxBitmap(ATTACKER_xpm));
				break;
			case(BOMBER):
				m_PlaneIcon->SetBitmap(wxBitmap(BOMBER_xpm));
				break;
			case(FIGHTER):
				m_PlaneIcon->SetBitmap(wxBitmap(FIGHTER_xpm));
				break;
			case(MULTIROLE):
				m_PlaneIcon->SetBitmap(wxBitmap(MULTIROLE_xpm));
				break;
		}
		for(int i = 0; i < 6; i++){ DrawBar(i, ActivePanel->Plane->PI->StatGrades[i][ActivePanel->Plane->level-1]); }//, ActivePanel->Plane->PI->Stats[i][ActivePanel->Plane->level-1]); }
		for(int i = 0; i < 3; i++){ DrawSlots(i, ActivePanel->Plane->PI->SLOTS[i][ActivePanel->Plane->level-1]); }
		//if(ActivePanel->SPW->name == ActivePanel->Plane->PI->SP2Name){ m_SPWAmmo->SetLabel(ActivePanel->Plane->PI->Ammo[3][ActivePanel->Plane->level]); }
		//else if(ActivePanel->SPW->name == ActivePanel->Plane->PI->SP3Name){ m_SPWAmmo->SetLabel(ActivePanel->Plane->PI->Ammo[4][ActivePanel->Plane->level]); }
		//else{ m_SPWAmmo->SetLabel(ActivePanel->Plane->PI->Ammo[2][ActivePanel->Plane->level]); }
		m_SPWType->SetLabel(ActivePanel->SPW->WI->WeaponName);
		m_TDMScore->SetLabel("0");
		m_InstallCost->SetLabel("0");
	}
	return;
}

void SetBuilder::DrawBar(int bar, wxString grade)//, int value)
{
	wxBitmap Image(150, 18);
	wxMemoryDC dc(Image);
	if(!dc.IsOk()){ return; }
	
	dc.SetBackground(wxBrush(wxColour(35,51,67)));
	dc.SetPen(wxPen(wxColour(81,90,107), 1));
	for(int i = 1; i < 15; i++){ dc.DrawLine(10*i, 0, 10*i, 18); }
	dc.SetBrush(wxBrush(wxColour("ACI-LightBlue")));
	dc.SetPen((*wxTRANSPARENT_PEN));
	int value = 0;
	if(grade == "S++"){ value = 140; }
	else if(grade == "S+"){ value = 130; }
	else if(grade == "S"){ value = 120; }
	else if(grade == "A+"){ value = 110; }
	else if(grade == "A"){ value = 100; }
	else if(grade == "B+"){ value = 90; }
	else if(grade == "B"){ value = 80; }
	else if(grade == "C+"){ value = 70; }
	else if(grade == "C"){ value = 60; }
	else if(grade == "D+"){ value = 50; }
	else if(grade == "D"){ value = 40; }
	else if(grade == "E+"){ value = 30; }
	else if(grade == "E"){ value = 20; }
	else if(grade == "F+"){ value = 10; }
	dc.DrawRectangle(0, 0, value, 18);
	
	switch(bar)
	{
		case(0):
			m_SpeedGrade->SetLabel(grade);
			m_SpeedBar->SetBitmap(Image);
			break;
		case(1):
			m_MobilityGrade->SetLabel(grade);
			m_MobilityBar->SetBitmap(Image);
			break;
		case(2):
			m_StabilityGrade->SetLabel(grade);
			m_StabilityBar->SetBitmap(Image);
			break;
		case(3):
			m_AAGrade->SetLabel(grade);
			m_AABar->SetBitmap(Image);
			break;
		case(4):
			m_AGGrade->SetLabel(grade);
			m_AGBar->SetBitmap(Image);
			break;
		case(5):
			m_DefenseGrade->SetLabel(grade);
			m_DefenseBar->SetBitmap(Image);
			break;
	}
	
	return;
}

void SetBuilder::DrawSlots(int bar, int value)
{
	wxBitmap Image(pips_xpm);
	wxMemoryDC dc(Image);
	if(!dc.IsOk()){ return; }
	
	dc.SetBrush(wxBrush(wxColor("ACI-DarkBlue")));
	dc.SetPen(wxPen(wxColour("ACI-LightBlue"),1));
	int x = 0, y = 0;
	for(int i = 0; i < value; i++)
	{
		dc.DrawRectangle((10*x)+1, (10*y)+1, 8, 8);
		y++;
		if(y > 1){ y = 0, x++; }
	}
	
	int used = 0;
	for(std::list<TreeNode*>::const_iterator curr = ActivePanel->Parts.begin(), last = ActivePanel->Parts.end(); curr != last; ++curr){ used += (*curr)->SlotCosts[bar]; }
	dc.SetPen((*wxTRANSPARENT_PEN));
	if(used > value){ dc.SetBrush(wxBrush("RED")); }
	else if(bar == 0){ dc.SetBrush(wxBrush("LIGHT BLUE")); }
	else if(bar == 1){ dc.SetBrush(wxBrush("LIME GREEN")); }
	else{ dc.SetBrush(wxBrush("PURPLE")); }
	for(int i = 0; i < used; i++)
	{
		dc.DrawRectangle((10*x)+1, (10*y)+1, 8, 8);
		y++;
		if(y > 1){ y = 0, x++; }
	}
	
	wxString Temp = "";
	Temp << used << "\/" << value;
	switch(bar)
	{
		case(0):
			m_BODY->SetLabel(Temp);
			m_BODYSlots->SetBitmap(Image);
			break;
		case(1):
			m_ARMS->SetLabel(Temp);
			m_ARMSSlots->SetBitmap(Image);
			break;
		case(2):
			m_MISC->SetLabel(Temp);
			m_MISCSlots->SetBitmap(Image);
			break;
	}
	
	return;
}

void SetBuilder::onClose(wxCloseEvent& event)
{
	Freeze();
	Hide();
	return;
}

void SetBuilder::onSaveDefault(wxCommandEvent& event)
{
	return;
}

void SetBuilder::onClearSets(wxCommandEvent& event)
{
	ActivePanel = nullptr;
	m_CustomSet1->UpdateNode(nullptr);
	m_CustomSet2->UpdateNode(nullptr);
	m_CustomSet3->UpdateNode(nullptr);
	m_CustomSet4->UpdateNode(nullptr);
	return;
}

void SetBuilder::onSavePNG(wxCommandEvent& event)
{
	wxUnusedVar(event);
	//Image.SaveFile("SetBuilder.PNG", wxBITMAP_TYPE_PNG);
	return;
}

void SetBuilder::onPlaneSelect(wxCommandEvent& event)
{
	wxUnusedVar(event);
	if(selected == 0){ return; }
	wxMenu menu;
	menu.AppendRadioItem(-1, "None");
	int i = 0;
	for(std::list<TreeNode*>::const_iterator curr = PlaneData.begin(), last = PlaneData.end(); curr != last; ++curr, i++)
	{
		if((*curr)->aquired){ menu.AppendRadioItem(i, (*curr)->name); }
		if(ActivePanel != nullptr && ActivePanel->Plane != nullptr && ActivePanel->Plane->name == (*curr)->name){ menu.Check(i, true); }
	}
 	menu.Connect(wxEVT_COMMAND_MENU_SELECTED, (wxObjectEventFunction)&SetBuilder::OnPopupClick, NULL, this);
 	PopupMenu(&menu, m_PlaneSelect->GetRect().GetTopRight());
	return;
}

void SetBuilder::onSPWSelect(wxCommandEvent& event)
{
	wxUnusedVar(event);
	if(selected == 0){ return; }
	wxMenu menu;
	int i = 201;
	if(ActivePanel != nullptr && ActivePanel->Plane != nullptr)
	{
		for(std::list<TreeNode*>::const_iterator curr = WeaponData.begin(), last = WeaponData.end(); curr != last; ++curr, i++)
		{
			if(ActivePanel->Plane->level >= 4 && ActivePanel->Plane->PI->SP2Name == (*curr)->name){ menu.AppendRadioItem(i, (*curr)->name); }
		}
		i = 201;
		for(std::list<TreeNode*>::const_iterator curr = WeaponData.begin(), last = WeaponData.end(); curr != last; ++curr, i++)
		{
			if(ActivePanel->Plane->PI->SP1Name == (*curr)->name){ menu.PrependRadioItem(i, (*curr)->name); }
			else if(ActivePanel->Plane->level >= 7 && ActivePanel->Plane->PI->SP3Name == (*curr)->name){ menu.AppendRadioItem(i, (*curr)->name); }
		}
	}
 	menu.Connect(wxEVT_COMMAND_MENU_SELECTED, (wxObjectEventFunction)&SetBuilder::OnPopupClick, NULL, this);
 	PopupMenu(&menu, m_WeaponSelect->GetRect().GetTopRight());
	return;
}

void SetBuilder::onPartSelect(wxCommandEvent& event)
{
}

void SetBuilder::OnPopupClick(wxCommandEvent &evt)
{
	if(evt.GetId() < 0)
	{
		if(ActivePanel != nullptr)
		{
			ActivePanel->UpdateNode(nullptr);
			ActivePanel->UpdateWeapon(nullptr);
		}
	}
	else if(evt.GetId() < 201)//Planes
	{
		std::list<TreeNode*>::iterator P = PlaneData.begin();
		int i = evt.GetId();
		while(i > 0){ P++, i--; }
		if(ActivePanel != nullptr)
		{
			ActivePanel->UpdateNode((*P));
			for(std::list<TreeNode*>::iterator curr = WeaponData.begin(), last = WeaponData.end(); curr != last; ++curr)
			{
				if((*curr)->name == (*P)->PI->SP1Name)
				{
					ActivePanel->UpdateWeapon((*curr));
					break;
				}
			}
		}
	}
	else if(evt.GetId() < 251)//SPWs
	{
		std::list<TreeNode*>::iterator W = WeaponData.begin();
		int i = evt.GetId() - 201;
		while(i > 0){ W++, i--; }
		if(ActivePanel != nullptr){ ActivePanel->UpdateWeapon((*W)); }
	}
	else if(evt.GetId() < 401)//Parts
	{
		std::list<TreeNode*>::iterator P = PartData.begin();
		int i = evt.GetId() - 204;
		while(i > 0){ P++, i--; }
	}
	return;
}

void SetBuilder::onKeyDown(wxKeyEvent& event)
{
	if(event.GetKeyCode() == WXK_TAB || event.GetKeyCode() == WXK_DOWN){ Select(selected+1); }
	else if(event.GetKeyCode() == WXK_UP){ Select(selected-1); }
	return;
}
