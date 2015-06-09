#include "MainFrame.h"
#include <wx/aboutdlg.h>
#include <iostream>
#include <algorithm>
#include <vector>
#include <wx/tokenzr.h>
#include <wx/textfile.h>
#include <wx/arrstr.h>
#include "patch.h"
#include <wx/list.h>
#include <wx/filefn.h>
#include <wx/txtstrm.h>
#include <wx/filesys.h>
#include <wx/treebase.h>
//#include "resources/icons/pips.xpm"
#include <wx/sstream.h>
//#include <resources/PlaneText_txt.h>
#include <cstdio>
#include "resource.h"


class wxTreeItemId;
MainFrame::MainFrame(wxWindow* parent)
    : MainFrameBaseClass(parent), SpecialAircraftData(3)
{
	SortEvent = true, SortNonEvent = true, SortDescending = true;
	wxImage::AddHandler( new wxXPMHandler );
	SpeedBar = new ImagePanel(m_SpeedBar, 0);//, wxT("C:\\Users\\Spencer\\Documents\\CodeLiteProjects\\SHIT\\resources\\icons\\progress_under.png")
	MobilityBar = new ImagePanel(m_MobilityBar, 0);
	StabilityBar = new ImagePanel(m_StabilityBar, 0);
	AABar = new ImagePanel(m_AABar, 0);
	AGBar = new ImagePanel(m_AGBar, 0);
	DefenseBar = new ImagePanel(m_DefenseBar, 0);
	
	BODYBar = new PipBar(m_BODYBar, 0);//, wxT("C:\\Users\\Spencer\\Documents\\CodeLiteProjects\\SHIT\\resources\\icons\\pips.png")
	ARMSBar = new PipBar(m_ARMSBar, 0);
	MISCBar = new PipBar(m_MISCBar, 0);
	
	RTree = nullptr, SA = nullptr, SW = nullptr, SB = nullptr;
	
	DWORD size = 0;
	const char* data = NULL;
	LoadFileInResource(IDR_MYTEXTFILE, TEXTFILE, size, data);
	char* buffer = new char[size+1];
	::memcpy(buffer, data, size);
	buffer[size] = 0; // NULL terminator
	//::printf("Contents of text file: %s\n", buffer); // Print as ASCII text
	
	wxStringInputStream Sin(wxString::FromUTF8(buffer));
	wxTextInputStream File(Sin, "\\n");
	
	wxString line = File.ReadLine();
	while(!line.StartsWith("%"))
	{
		if(!line.StartsWith("#"))
		{
			PlaneInfo PI;
			
			//std::cout << line.ToStdString() << "\n" << std::flush;
			PI.AircraftName = line.ToStdString(), File.ReadLine();// std::cout << PI.AircraftName << "\n" << std::flush;
			PI.AircraftFamily = File.ReadLine().ToStdString(), File.ReadLine();
			PI.CoO = File.ReadLine().ToStdString(), File.ReadLine();
			Countries.push_back(PI.CoO);
			PI.Manufacturer = File.ReadLine().ToStdString(), File.ReadLine();
			Manufacturers.push_back(PI.Manufacturer);
			wxString Role = File.ReadLine();
			if(Role == "ATTACKER"){ PI.Role = ATTACKER; }
			else if(Role == "BOMBER"){ PI.Role = BOMBER; }
			else if(Role == "FIGHTER"){ PI.Role = FIGHTER; }
			else if(Role == "MULTIROLE"){ PI.Role = MULTIROLE; }
			else{ PI.Role = DEBUG; }
			File.ReadLine();
			PI.isEvent = File.ReadLine().StartsWith("1"), File.ReadLine();
			PI.MaxLevel = wxAtoi(File.ReadLine()), File.ReadLine();
		
			wxStringTokenizer tokenizer("T E S T", " \t");
			for(int l = 0; l < 6; l++)//Set stats
			{
				tokenizer.Reinit(File.ReadLine()), File.ReadLine();
				for(int i =0; i < PI.MaxLevel; i++){ PI.Stats[l][i] = wxAtoi(tokenizer.GetNextToken()); }
				tokenizer.Reinit(File.ReadLine()), File.ReadLine();
				for(int i =0; i < PI.MaxLevel; i++){ PI.StatGrades[l][i] = tokenizer.GetNextToken().ToStdString(); }
			}
			
			tokenizer.Reinit(File.ReadLine()), File.ReadLine();//GUN
			for(int i =0; i < PI.MaxLevel; i++){ PI.Ammo[0][i] = wxAtoi(tokenizer.GetNextToken()); }
			tokenizer.Reinit(File.ReadLine()), File.ReadLine();//MSL
			for(int i =0; i < PI.MaxLevel; i++){ PI.Ammo[1][i] = wxAtoi(tokenizer.GetNextToken()); }
			PI.SP1Name = File.ReadLine().ToStdString(), File.ReadLine();
			SPWs.push_back(PI.SP1Name);
			tokenizer.Reinit(File.ReadLine()), File.ReadLine();//SPW1
			for(int i =0; i < PI.MaxLevel; i++){ PI.Ammo[2][i] = wxAtoi(tokenizer.GetNextToken()); }
			PI.SP2Name = File.ReadLine().ToStdString(), File.ReadLine();
			SPWs.push_back(PI.SP2Name);
			tokenizer.Reinit(File.ReadLine()), File.ReadLine();//SPW2
			for(int i =0; i < PI.MaxLevel; i++){ PI.Ammo[3][i] = wxAtoi(tokenizer.GetNextToken()); }
			PI.SP3Name = File.ReadLine().ToStdString(), File.ReadLine();
			SPWs.push_back(PI.SP3Name);
			tokenizer.Reinit(File.ReadLine()), File.ReadLine();//SPW3
			for(int i =0; i < PI.MaxLevel; i++){ PI.Ammo[4][i] = wxAtoi(tokenizer.GetNextToken()); }
			
			for(int l = 0; l < 3; l++)//Set slots
			{
				tokenizer.Reinit(File.ReadLine()), File.ReadLine();
				int T = wxAtoi(tokenizer.GetNextToken());
				for(int i = 0; i < PI.MaxLevel; i++)
				{
					if(i == 9){ T = wxAtoi(tokenizer.GetNextToken()); }
					if(i == 14){ T = wxAtoi(tokenizer.GetNextToken()); }
					PI.SLOTS[l][i] = T;
				}
			}
			tokenizer.Reinit(File.ReadLine()), File.ReadLine();//Cst
			for(int i =0; i < PI.MaxLevel; i++){ PI.Cost[0][i] = tokenizer.GetNextToken(); }
			tokenizer.Reinit(File.ReadLine()), File.ReadLine();//Cost
			for(int i =0; i < PI.MaxLevel; i++){ PI.Cost[1][i] = tokenizer.GetNextToken(); }
			line = File.ReadLine();
			PlaneData.push_back(PI);
		}
		else
		{
			line = File.ReadLine();
		}
	}
	m_FilterOptionSelector->Append(wxT("Role")), m_FilterOptionSelector->Append(wxT("SP Weapons")), m_FilterOptionSelector->Append(wxT("Country")), m_FilterOptionSelector->Append(wxT("Manufacturer")), m_FilterOptionSelector->Append(wxT("Stat"));
	delete[] buffer;
	Countries.sort(), Countries.unique();
	Manufacturers.sort(), Manufacturers.unique();
	SPWs.sort(), SPWs.unique();
	for(std::list<string>::const_iterator curr = Countries.begin(), last = Countries.end(); curr != last; ++curr){ Locale.Countries.Add(*curr); }
	for(std::list<string>::const_iterator curr = Manufacturers.begin(), last = Manufacturers.end(); curr != last; ++curr){ Locale.Manufacturers.Add(*curr); }
	for(std::list<string>::const_iterator curr = SPWs.begin(), last = SPWs.end(); curr != last; ++curr){ Locale.SPWs.Add(*curr); }
	
	wxTreeItemId root = m_TreeSelector->AddRoot("Planes");
	wxTreeItemId node, child;
	std::list<TreeData> Tree;
	
	node = m_TreeSelector->AppendItem(root, "Eastern Block Aircraft");
	child = m_TreeSelector->AppendItem(node, "Sukoi Aircraft");
	Tree.push_back(TreeData("Su-24",m_TreeSelector->AppendItem(child, "Su-24")));
	Tree.push_back(TreeData("Su-25",m_TreeSelector->AppendItem(child, "Su-25")));
	Tree.push_back(TreeData("Su-33",m_TreeSelector->AppendItem(child, "Su-33")));
	Tree.push_back(TreeData("Su-34",m_TreeSelector->AppendItem(child, "Su-34")));
	Tree.push_back(TreeData("Su-37",m_TreeSelector->AppendItem(child, "Su-37")));
	Tree.push_back(TreeData("Su-47",m_TreeSelector->AppendItem(child, "Su-47")));
	Tree.push_back(TreeData("-50",m_TreeSelector->AppendItem(child, "Su-50")));
	
	child = m_TreeSelector->AppendItem(node, "Mikoyan Aircraft");
	Tree.push_back(TreeData("MiG-21",m_TreeSelector->AppendItem(child, "MiG-21")));
	Tree.push_back(TreeData("MiG-29",m_TreeSelector->AppendItem(child, "MiG-29")));
	
	node = m_TreeSelector->AppendItem(root, "American Aircraft");
	child = m_TreeSelector->AppendItem(node, "American Fighters");
	Tree.push_back(TreeData("F-2A",m_TreeSelector->AppendItem(child, "F-2")));
	Tree.push_back(TreeData("F-4",m_TreeSelector->AppendItem(child, "F-4")));
	Tree.push_back(TreeData("F-5",m_TreeSelector->AppendItem(child, "F-5")));
	Tree.push_back(TreeData("F-14",m_TreeSelector->AppendItem(child, "F-14")));
	Tree.push_back(TreeData("F-15",m_TreeSelector->AppendItem(child, "F-15")));
	Tree.push_back(TreeData("F-16",m_TreeSelector->AppendItem(child, "F-16")));
	Tree.push_back(TreeData("-18",m_TreeSelector->AppendItem(child, "F-18")));
	Tree.push_back(TreeData("F-20",m_TreeSelector->AppendItem(child, "F-20")));
	Tree.push_back(TreeData("F-22",m_TreeSelector->AppendItem(child, "F-22")));
	Tree.push_back(TreeData("F-23",m_TreeSelector->AppendItem(child, "F-23")));
	Tree.push_back(TreeData("X-29",m_TreeSelector->AppendItem(child, "F-29")));
	Tree.push_back(TreeData("F-35",m_TreeSelector->AppendItem(child, "F-35")));
	
	
	child = m_TreeSelector->AppendItem(node, "American Attackers");
	Tree.push_back(TreeData("A-10",m_TreeSelector->AppendItem(child, "A-10")));
	Tree.push_back(TreeData("F-117",m_TreeSelector->AppendItem(child, "F-117")));
	
	child = m_TreeSelector->AppendItem(node, "American Bombers");
	Tree.push_back(TreeData("B-1B",m_TreeSelector->AppendItem(child, "B-1")));
	Tree.push_back(TreeData("B-2A",m_TreeSelector->AppendItem(child, "B-2")));
	
	node = m_TreeSelector->AppendItem(root, "European Aircraft");
	Tree.push_back(TreeData("AV-8B",m_TreeSelector->AppendItem(node, "AV-8B")));
	Tree.push_back(TreeData("JAS 39",m_TreeSelector->AppendItem(node, "JAS 39")));
	Tree.push_back(TreeData("Mirage 2000-5",m_TreeSelector->AppendItem(node, "Mirage 2000-5")));
	Tree.push_back(TreeData("Rafale M",m_TreeSelector->AppendItem(node, "Rafale M")));
	Tree.push_back(TreeData("Typhoon",m_TreeSelector->AppendItem(node, "Typhoon")));
	
	node = m_TreeSelector->AppendItem(root, "Project ACES Aircraft");
	Tree.push_back(TreeData("ADF",m_TreeSelector->AppendItem(node, "ADF")));
	Tree.push_back(TreeData("ASF-X",m_TreeSelector->AppendItem(node, "ASF-X")));
	Tree.push_back(TreeData("ATD-0",m_TreeSelector->AppendItem(node, "ATD-0")));
	Tree.push_back(TreeData("R-101",m_TreeSelector->AppendItem(node, "R-101")));
	Tree.push_back(TreeData("X-02",m_TreeSelector->AppendItem(node, "X-02")));
	Tree.push_back(TreeData("XFA-27",m_TreeSelector->AppendItem(node, "XFA-27")));
	
	for(std::list<PlaneInfo>::const_iterator curr = PlaneData.begin(), last = PlaneData.end(); curr != last; ++curr)
	{
		for(std::list<TreeData>::const_iterator iter = Tree.begin(), iend = Tree.end(); iter != iend; ++iter)
		{
			if(curr->AircraftName.find(iter->Name) != std::string::npos)
			{
				if(curr->AircraftName.find_last_of('-') > curr->AircraftName.find_first_of('-')){ m_TreeSelector->AppendItem(iter->ID, curr->AircraftName); }
				else{ m_TreeSelector->PrependItem(iter->ID, curr->AircraftName); }
			}
		}
	}
	
	wxTheColourDatabase->AddColour("ACI-DarkBlue", wxColour(2,11,26));
	wxTheColourDatabase->AddColour("ACI-Blue", wxColour(32,47,67));
	wxTheColourDatabase->AddColour("ACI-LightBlue", wxColour(204,211,229));
	wxTheColourDatabase->AddColour("ACI-Selected", wxColour(43,134,219));
	
	SetupTree();
	SetupSpecialAircraft();
	SetupSpecialWeapons();
	LoadSaveData();
	
	UpdatePlaneSelector();
}

MainFrame::~MainFrame()
{
	delete SpeedBar, delete MobilityBar, delete StabilityBar, delete AABar, delete AGBar, delete DefenseBar;
	delete BODYBar, delete ARMSBar, delete MISCBar;
}

void MainFrame::OnExit(wxCommandEvent& event)
{
    wxUnusedVar(event);
	if(RTree != nullptr){ RTree->Destroy(); }
	if(SA != nullptr){ SA->Destroy(); }
	if(SW != nullptr){ SW->Destroy(); }
	if(SB != nullptr){ SB->Destroy(); }
	Freeze();
    Destroy();
}

void MainFrame::OnAbout(wxCommandEvent& event)
{
    wxUnusedVar(event);
    wxAboutDialogInfo info;
    info.SetCopyright(_("Send questions/comments/insults/translation requests to: sieve32@gmail.com"));
    info.SetLicence(_("GPL v2 or later"));
    info.SetDescription(_("\tv1.1.3-15\nMade using wxWidgets"));
    ::wxAboutBox(info);
}

void MainFrame::onSelectionUpdated(wxCommandEvent& event)
{
	wxObject * O = event.GetEventObject();
	wxObject * Temp = m_PlaneSelector;
	if(O->IsSameAs(*Temp))
	{
		std::cout << "Combobox update\n" << std::flush;		
		return;
	}
}
void MainFrame::onFilterToggle(wxCommandEvent& event)
{
	wxUnusedVar(event);
	UpdatePlaneSelector();
	return;
}

void MainFrame::UpdatePlaneSelector()
{
	wxArrayString TList;
	if( !m_FilterToggle->GetValue() )
	{
		for(std::list<PlaneInfo>::const_iterator iter = PlaneData.begin(), end = PlaneData.end(); iter != end; ++iter)
		{
			TList.Add(wxString(iter->AircraftName));
		}
		TList.Sort(!SortDescending);
	}
	else
	{
		switch(m_FilterOptionSelector->GetSelection())
		{
			case(0):			//No Filter
				for(std::list<PlaneInfo>::const_iterator iter = PlaneData.begin(), end = PlaneData.end(); iter != end; ++iter)
				{
					if( (iter->isEvent && SortEvent) || (!iter->isEvent && SortNonEvent) ){ TList.Add(wxString(iter->AircraftName)); }
				}
				TList.Sort(!SortDescending);
				break;
			case(1):			//Role
				switch(m_FilterOptionSubSelector->GetSelection())
				{
					case(0):		//None
						for(std::list<PlaneInfo>::const_iterator iter = PlaneData.begin(), end = PlaneData.end(); iter != end; ++iter)
						{
							if( (iter->Role == ATTACKER) && ( (iter->isEvent && SortEvent) || (!iter->isEvent && SortNonEvent) ) ){ TList.Add(wxString(iter->AircraftName)); }
						}
						TList.Sort(!SortDescending);
						m_PlaneSelector->Append(TList);
						TList.Clear();
						for(std::list<PlaneInfo>::const_iterator iter = PlaneData.begin(), end = PlaneData.end(); iter != end; ++iter)
						{
							if( (iter->Role == BOMBER) && ( (iter->isEvent && SortEvent) || (!iter->isEvent && SortNonEvent) ) ){ TList.Add(wxString(iter->AircraftName)); }
						}
						TList.Sort(!SortDescending);
						m_PlaneSelector->Append(TList);
						TList.Clear();
						for(std::list<PlaneInfo>::const_iterator iter = PlaneData.begin(), end = PlaneData.end(); iter != end; ++iter)
						{
							if( (iter->Role == FIGHTER) && ( (iter->isEvent && SortEvent) || (!iter->isEvent && SortNonEvent) ) ){ TList.Add(wxString(iter->AircraftName)); }
						}
						TList.Sort(!SortDescending);
						m_PlaneSelector->Append(TList);
						TList.Clear();
						for(std::list<PlaneInfo>::const_iterator iter = PlaneData.begin(), end = PlaneData.end(); iter != end; ++iter)
						{
							if( (iter->Role == MULTIROLE) && ( (iter->isEvent && SortEvent) || (!iter->isEvent && SortNonEvent) ) ){ TList.Add(wxString(iter->AircraftName)); }
						}
						TList.Sort(!SortDescending);
						break;
					case(1):		//ATTACKER
						for(std::list<PlaneInfo>::const_iterator iter = PlaneData.begin(), end = PlaneData.end(); iter != end; ++iter)
						{
							if( (iter->Role == ATTACKER) && ( (iter->isEvent && SortEvent) || (!iter->isEvent && SortNonEvent) ) ){ TList.Add(wxString(iter->AircraftName)); }
						}
						TList.Sort(!SortDescending);
						break;
					case(2):		//BOMBER
						for(std::list<PlaneInfo>::const_iterator iter = PlaneData.begin(), end = PlaneData.end(); iter != end; ++iter)
						{
							if( (iter->Role == BOMBER) && ( (iter->isEvent && SortEvent) || (!iter->isEvent && SortNonEvent) ) ){ TList.Add(wxString(iter->AircraftName)); }
						}
						TList.Sort(!SortDescending);
						break;
					case(3):		//FIGHTER
						for(std::list<PlaneInfo>::const_iterator iter = PlaneData.begin(), end = PlaneData.end(); iter != end; ++iter)
						{
							if( (iter->Role == FIGHTER) && ( (iter->isEvent && SortEvent) || (!iter->isEvent && SortNonEvent) ) ){ TList.Add(wxString(iter->AircraftName)); }
						}
						TList.Sort(!SortDescending);
						break;
					case(4):		//MULTIROLE
						for(std::list<PlaneInfo>::const_iterator iter = PlaneData.begin(), end = PlaneData.end(); iter != end; ++iter)
						{
							if( (iter->Role == MULTIROLE) && ( (iter->isEvent && SortEvent) || (!iter->isEvent && SortNonEvent) ) ){ TList.Add(wxString(iter->AircraftName)); }
						}
						TList.Sort(!SortDescending);
						break;
				}
				
				break;
			case(2):			//SP Weapons
				if(m_FilterOptionSubSelector->GetSelection())
				{
					std::list<string> TEMPList;
					for(std::list<PlaneInfo>::const_iterator iter = PlaneData.begin(), end = PlaneData.end(); iter != end; ++iter)
					{
						if( (iter->SP1Name == m_FilterOptionSubSelector->GetStringSelection()) && ( (iter->isEvent && SortEvent) || (!iter->isEvent && SortNonEvent) ) ){ TEMPList.push_back(iter->AircraftName); }
					}
					TEMPList.sort();
					if(!SortDescending){ TEMPList.reverse(); }
					for(std::list<string>::const_iterator curr = TEMPList.begin(), last = TEMPList.end(); curr != last; ++curr){ TList.Add(wxString(*curr)); }
					if(m_FilterLevel->GetValue() >= 4)
					{
						TEMPList.clear();
						for(std::list<PlaneInfo>::const_iterator iter = PlaneData.begin(), end = PlaneData.end(); iter != end; ++iter)
						{
							if( (iter->SP2Name == m_FilterOptionSubSelector->GetStringSelection()) && ( (iter->isEvent && SortEvent) || (!iter->isEvent && SortNonEvent) ) ){ TEMPList.push_back(iter->AircraftName); }
						}
						TEMPList.sort();
						if(!SortDescending){ TEMPList.reverse(); }
						for(std::list<string>::const_iterator curr = TEMPList.begin(), last = TEMPList.end(); curr != last; ++curr){ TList.Add(wxString(*curr)); }
						if(m_FilterLevel->GetValue() >= 7)
						{
							m_PlaneSelector->Append(TList);
							TEMPList.clear();
							for(std::list<PlaneInfo>::const_iterator iter = PlaneData.begin(), end = PlaneData.end(); iter != end; ++iter)
							{
								if( (iter->SP3Name == m_FilterOptionSubSelector->GetStringSelection()) && ( (iter->isEvent && SortEvent) || (!iter->isEvent && SortNonEvent) ) ){ TEMPList.push_back(iter->AircraftName); }
							}
							TEMPList.sort();
							if(!SortDescending){ TEMPList.reverse(); }
							for(std::list<string>::const_iterator curr = TEMPList.begin(), last = TEMPList.end(); curr != last; ++curr){ TList.Add(wxString(*curr)); }
						}
					}
				}
				break;
			case(3):			//Country
				if(m_FilterOptionSubSelector->GetSelection() == 0)	//None
				{
					std::list<TempList> Sort;
					for(std::list<string>::const_iterator I = Countries.begin(), end = Countries.end(); I != end; ++I){ Sort.push_back(TempList(*I)); }
					for(std::list<PlaneInfo>::const_iterator iter = PlaneData.begin(), end = PlaneData.end(); iter != end; ++iter)
					{
						if( (iter->isEvent && SortEvent) || (!iter->isEvent && SortNonEvent) )
						{
							for(std::list<TempList>::iterator curr = Sort.begin(), last = Sort.end(); curr != last; ++curr)
							{
								if(iter->CoO == curr->Label){ curr->Values.push_back(iter->AircraftName); }
							}
						}
					}
					for(std::list<TempList>::iterator curr = Sort.begin(), last = Sort.end(); curr != last; ++curr)
					{
						curr->Values.sort();
						if(!SortDescending){ curr->Values.reverse(); }
						for(std::list<string>::const_iterator TI = curr->Values.begin(), TE = curr->Values.end(); TI != TE; ++TI){ TList.Add(*TI); }
					}
					
				}
				else
				{
					std::list<string>::const_iterator C = Countries.begin();
					for(int i = m_FilterOptionSubSelector->GetSelection(); i > 1; i--){ C++; }
					for(std::list<PlaneInfo>::const_iterator iter = PlaneData.begin(), end = PlaneData.end(); iter != end; ++iter)
					{
						if( (iter->CoO == (*C)) && ( (iter->isEvent && SortEvent) || (!iter->isEvent && SortNonEvent) ) ){ TList.Add(wxString(iter->AircraftName)); }
					}
					TList.Sort(!SortDescending);
				}
				break;
			case(4):			//Manufacturer
				if(m_FilterOptionSubSelector->GetSelection() == 0)	//None
				{
					std::list<TempList> Sort;
					for(std::list<string>::const_iterator I = Manufacturers.begin(), end = Manufacturers.end(); I != end; ++I){ Sort.push_back(TempList(*I)); }
					for(std::list<PlaneInfo>::const_iterator iter = PlaneData.begin(), end = PlaneData.end(); iter != end; ++iter)
					{
						if( (iter->isEvent && SortEvent) || (!iter->isEvent && SortNonEvent) )
						{
							for(std::list<TempList>::iterator curr = Sort.begin(), last = Sort.end(); curr != last; ++curr)
							{
								if(iter->Manufacturer == curr->Label){ curr->Values.push_back(iter->AircraftName); }
							}
						}
					}
					for(std::list<TempList>::iterator curr = Sort.begin(), last = Sort.end(); curr != last; ++curr)
					{
						curr->Values.sort();
						if(!SortDescending){ curr->Values.reverse(); }
						for(std::list<string>::const_iterator TI = curr->Values.begin(), TE = curr->Values.end(); TI != TE; ++TI){ TList.Add(*TI); }
					}
					
				}
				else
				{
					std::list<string>::const_iterator M = Manufacturers.begin();
					for(int i = m_FilterOptionSubSelector->GetSelection(); i > 1; i--){ M++; }
					for(std::list<PlaneInfo>::const_iterator iter = PlaneData.begin(), end = PlaneData.end(); iter != end; ++iter)
					{
						if( (iter->Manufacturer == (*M)) && ( (iter->isEvent && SortEvent) || (!iter->isEvent && SortNonEvent) ) ){ TList.Add(wxString(iter->AircraftName)); }
					}
					TList.Sort(!SortDescending);
				}
				break;
			case(5):			//Stats
				std::list<TempData> TData;
				if(!m_FilterOptionSubSelector->GetSelection())
				{
					for(std::list<PlaneInfo>::const_iterator iter = PlaneData.begin(), end = PlaneData.end(); iter != end; ++iter)
					{
						float T = 0;
						for(int i = 0; i < 6; i++)
						{//Forgive me for what I must do
							string G = iter->StatGrades[i][std::min(iter->MaxLevel, m_FilterLevel->GetValue())-1];
							if(G == "F+"){ T += 0.5; }
							else if(G == "E"){ T += 1; }
							else if(G == "E+"){ T += 1.5; }
							else if(G == "D"){ T += 2; }
							else if(G == "D+"){ T += 2.5; }
							else if(G == "C"){ T += 3; }
							else if(G == "C+"){ T += 3.5; }
							else if(G == "B"){ T += 4; }
							else if(G == "B+"){ T += 4.5; }
							else if(G == "A"){ T += 5; }
							else if(G == "A+"){ T += 5.5; }
							else if(G == "S"){ T += 6; }
							else if(G == "S+"){ T += 6.5; }
							else if(G == "S++"){ T += 7; }
							else if(G == "S+++"){ T += 7.5; }
						}
						TData.push_back(TempData(iter->AircraftName, T));
					}
				}
				
				else if(m_FilterOptionSubSelector->GetSelection() > 0 && m_FilterOptionSubSelector->GetSelection() < 6)
				{
					for(std::list<PlaneInfo>::const_iterator iter = PlaneData.begin(), end = PlaneData.end(); iter != end; ++iter)
					{
						float T = 0;
						//Forgive me for what I must do
						string G = iter->StatGrades[m_FilterOptionSubSelector->GetSelection()][std::min(iter->MaxLevel, m_FilterLevel->GetValue())-1];
						if(G == "F+"){ T += 0.5; }
						else if(G == "E"){ T += 1; }
						else if(G == "E+"){ T += 1.5; }
						else if(G == "D"){ T += 2; }
						else if(G == "D+"){ T += 2.5; }
						else if(G == "C"){ T += 3; }
						else if(G == "C+"){ T += 3.5; }
						else if(G == "B"){ T += 4; }
						else if(G == "B+"){ T += 4.5; }
						else if(G == "A"){ T += 5; }
						else if(G == "A+"){ T += 5.5; }
						else if(G == "S"){ T += 6; }
						else if(G == "S+"){ T += 6.5; }
						else if(G == "S++"){ T += 7; }
						else if(G == "S+++"){ T += 7.5; }
						
						TData.push_back(TempData(iter->AircraftName, T));
					}
				}
				else
				{
					for(std::list<PlaneInfo>::const_iterator iter = PlaneData.begin(), end = PlaneData.end(); iter != end; ++iter)
					{
						float T = 0;
						//Forgive me for what I must do
						for(int i = 0; i < 3; i++){ T += iter->SLOTS[i][std::min(iter->MaxLevel, m_FilterLevel->GetValue())-1]; }
						
						TData.push_back(TempData(iter->AircraftName, T));
					}
				}
				TData.sort();
				for(std::list<TempData>::const_iterator TD = TData.begin(), end = TData.end(); TD != end; ++TD)
				{
					if(SortDescending){ TList.Insert(TD->Name, 0); }
					else{ TList.Add(TD->Name); }
				}
				break;
		}
	}
	m_PlaneSelector->Set(TList);
	return;
}
void MainFrame::onAscendingClicked(wxCommandEvent& event)
{
	wxUnusedVar(event);
	if(m_Ascending->GetValue() && m_Descending->GetValue())
	{
		SortDescending = false;
		m_Descending->SetValue(false);
		UpdatePlaneSelector();
	}
	return;
}
void MainFrame::onDescendingClicked(wxCommandEvent& event)
{
	wxUnusedVar(event);
	if(m_Descending->GetValue() && m_Ascending->GetValue())
	{
		SortDescending = true;
		m_Ascending->SetValue(false);
		UpdatePlaneSelector();
	}
	return;
}
void MainFrame::onEventSort(wxCommandEvent& event)
{
	wxUnusedVar(event);
	if(m_ShowEvent->IsChecked() != SortEvent)
	{
		SortEvent = m_ShowEvent->IsChecked();
		UpdatePlaneSelector();
	}
	return;
}
void MainFrame::onFilterOptionChanged(wxCommandEvent& event)
{
	wxUnusedVar(event);
	switch(m_FilterOptionSelector->GetSelection())
	{
		case (0):
			m_FilterOptionSubSelector->Clear();
			break;
		case (1):		//Role
			m_FilterOptionSubSelector->Set(Locale.Roles);
			break;
		case (2):		//SP Weapon
			m_FilterOptionSubSelector->Set(Locale.SPWs);
			break;
		case (3):		//Country
			m_FilterOptionSubSelector->Set(Locale.Countries);
			break;
		case (4):		//Manufacturer
			m_FilterOptionSubSelector->Set(Locale.Manufacturers);
			break;
		case (5):		//Stat
			m_FilterOptionSubSelector->Set(Locale.Stats);
			break;
	}
	m_FilterOptionSubSelector->Insert(Locale.None, 0);
	m_FilterOptionSubSelector->SetSelection(0);
	UpdatePlaneSelector();
	return;
}
void MainFrame::onFilterSubOptionChanged(wxCommandEvent& event)
{
	wxUnusedVar(event);
	UpdatePlaneSelector();
	return;
}

void MainFrame::onNonEventSort(wxCommandEvent& event)
{
	wxUnusedVar(event);
	if(m_ShowNonEvent->IsChecked() != SortNonEvent)
	{
		SortNonEvent = m_ShowNonEvent->IsChecked();
		UpdatePlaneSelector();
	}
	return;
}

void MainFrame::onLevelChanged(wxSpinEvent& event)
{
	wxUnusedVar(event);
	UpdatePlaneData();
	return;
}

void MainFrame::onPlaneSelected(wxCommandEvent& event)
{
	wxUnusedVar(event);
	if(m_PlaneSelector->GetSelection() == wxNOT_FOUND){ return; }
	m_TreeSelector->Unselect();
	UpdatePlaneData();
	return;
}

void MainFrame::UpdatePlaneData()
{
	const PlaneInfo * PI;
	string CurrName;
	if(m_PlaneSelector->GetSelection() != wxNOT_FOUND){ CurrName = m_PlaneSelector->GetStringSelection().ToStdString(); }
	else{ CurrName = m_TreeSelector->GetItemText(m_TreeSelector->GetSelection()).ToStdString(); }
	for(std::list<PlaneInfo>::const_iterator iter = PlaneData.begin(), end = PlaneData.end(); iter != end; ++iter)
	{
		if(iter->AircraftName == CurrName)
		{
			PI = &(*iter);
			break;
		}
	}
	if(!PI){ return; }
	m_PlaneName->SetLabel("[ " + PI->AircraftName + " ]");
	m_LevelSelector->SetMax(PI->MaxLevel);
	if(m_LevelSelector->GetValue() > m_LevelSelector->GetMax()){ m_LevelSelector->SetValue(m_LevelSelector->GetMax()); }
	//if(m_LevelSelector->GetValue() == 10){ m_LevelSelector->SetValue(m_LevelSelector->GetMax()); }
	m_Cst->SetLabel(PI->Cost[0][m_LevelSelector->GetValue()-1]);
	m_Cost->SetLabel(PI->Cost[1][m_LevelSelector->GetValue()-1]);
	
	m_SpeedGrade->SetLabel(PI->StatGrades[0][m_LevelSelector->GetValue()-1]);
	if(PI->Stats[0][m_LevelSelector->GetValue()-1]){SpeedBar->DrawProgress(PI->Stats[0][m_LevelSelector->GetValue()-1]);}
	else{SpeedBar->DrawProgress(ApproximateValue("Speed", PI->StatGrades[0][m_LevelSelector->GetValue()-1]));}
	m_MobilityGrade->SetLabel(PI->StatGrades[1][m_LevelSelector->GetValue()-1]);
	if(PI->Stats[1][m_LevelSelector->GetValue()-1]){MobilityBar->DrawProgress(PI->Stats[1][m_LevelSelector->GetValue()-1]);}
	else{MobilityBar->DrawProgress(ApproximateValue("Mobility", PI->StatGrades[1][m_LevelSelector->GetValue()-1]));}
	m_StabilityGrade->SetLabel(PI->StatGrades[2][m_LevelSelector->GetValue()-1]);
	if(PI->Stats[2][m_LevelSelector->GetValue()-1]){StabilityBar->DrawProgress(PI->Stats[2][m_LevelSelector->GetValue()-1]);}
	else{StabilityBar->DrawProgress(ApproximateValue("Stability", PI->StatGrades[2][m_LevelSelector->GetValue()-1]));}
	m_AAGrade->SetLabel(PI->StatGrades[3][m_LevelSelector->GetValue()-1]);
	if(PI->Stats[3][m_LevelSelector->GetValue()-1]){AABar->DrawProgress(PI->Stats[3][m_LevelSelector->GetValue()-1]);}
	else{AABar->DrawProgress(ApproximateValue("AA", PI->StatGrades[3][m_LevelSelector->GetValue()-1]));}
	m_AGGrade->SetLabel(PI->StatGrades[4][m_LevelSelector->GetValue()-1]);
	if(PI->Stats[4][m_LevelSelector->GetValue()-1]){AGBar->DrawProgress(PI->Stats[4][m_LevelSelector->GetValue()-1]);}
	else{AGBar->DrawProgress(ApproximateValue("AG", PI->StatGrades[4][m_LevelSelector->GetValue()-1]));}
	m_DefenseGrade->SetLabel(PI->StatGrades[5][m_LevelSelector->GetValue()-1]);
	if(PI->Stats[5][m_LevelSelector->GetValue()-1]){DefenseBar->DrawProgress(PI->Stats[5][m_LevelSelector->GetValue()-1]);}
	else{DefenseBar->DrawProgress(ApproximateValue("Defense", PI->StatGrades[5][m_LevelSelector->GetValue()-1]));}
	SpeedBar->Refresh(), MobilityBar->Refresh(), StabilityBar->Refresh(), AABar->Refresh(), AGBar->Refresh(), DefenseBar->Refresh();
	
	m_BODYSlots->SetLabel(patch::to_string(PI->SLOTS[0][m_LevelSelector->GetValue()-1]));
	BODYBar->UpdateBar(PI->SLOTS[0][m_LevelSelector->GetValue()-1]);
	BODYBar->Refresh();
	m_ARMSSlots->SetLabel(patch::to_string(PI->SLOTS[1][m_LevelSelector->GetValue()-1]));
	ARMSBar->UpdateBar(PI->SLOTS[1][m_LevelSelector->GetValue()-1]);
	ARMSBar->Refresh();
	m_MISCSlots->SetLabel(patch::to_string(PI->SLOTS[2][m_LevelSelector->GetValue()-1]));
	MISCBar->UpdateBar(PI->SLOTS[2][m_LevelSelector->GetValue()-1]);
	MISCBar->Refresh();

	m_GUNAmmo->SetLabel(patch::to_string(PI->Ammo[0][m_LevelSelector->GetValue()-1]));
	m_MSLAmmo->SetLabel(patch::to_string(PI->Ammo[1][m_LevelSelector->GetValue()-1]));
	m_SPW1Name->SetLabel(PI->SP1Name);
	m_SPW1Ammo->SetLabel(patch::to_string(PI->Ammo[2][m_LevelSelector->GetValue()-1]));
	m_SPW2Name->SetLabel(PI->SP2Name);
	m_SPW2Ammo->SetLabel(patch::to_string(PI->Ammo[3][m_LevelSelector->GetValue()-1]));
	m_SPW3Name->SetLabel(PI->SP3Name);
	m_SPW3Ammo->SetLabel(patch::to_string(PI->Ammo[4][m_LevelSelector->GetValue()-1]));
}

int MainFrame::ApproximateValue(string Stat, string Grade)//Super fucking arbitrary approximation, goddamnit Bamco
{
	int StatHolder = 0;
	if(Stat == "Speed"){StatHolder = 1;}
	else if(Stat == "Mobility"){StatHolder = 2;}
	else if(Stat == "Stability"){StatHolder = 3;}
	else if(Stat == "AA"){StatHolder = 4;}
	else if(Stat == "AG"){StatHolder = 5;}
	else if(Stat == "Defense"){StatHolder = 6;}
	else{return 0;}
	int GradeHolder = 0;
	if(Grade == "F"){GradeHolder = 1;}
	else if(Grade == "F+"){GradeHolder = 2;}
	else if(Grade == "E"){GradeHolder = 3;}
	else if(Grade == "E+"){GradeHolder = 4;}
	else if(Grade == "D"){GradeHolder = 5;}
	else if(Grade == "D+"){GradeHolder = 6;}
	else if(Grade == "C"){GradeHolder = 7;}
	else if(Grade == "C+"){GradeHolder = 8;}
	else if(Grade == "B"){GradeHolder = 9;}
	else if(Grade == "B+"){GradeHolder = 10;}
	else if(Grade == "A"){GradeHolder = 11;}
	else if(Grade == "A+"){GradeHolder = 12;}
	else if(Grade == "S"){GradeHolder = 13;}
	else if(Grade == "S+"){GradeHolder = 14;}
	else if(Grade == "S++"){GradeHolder = 15;}
	else if(Grade == "S+++"){GradeHolder = 15;}
	else if(Grade == "F-"){return 0;}
	else{return 0;}
	switch(GradeHolder)
	{
		case(1):
			switch(StatHolder)
			{
				case(1): return 3;// 0 to 6
				case(2): return 5;// 0 to 9
				case(3): return 5;// 0 to 10?
				case(4): return 4;// 0 to 8?
				case(5): return 5;// 0 to 10?
				case(6): return 5;// 0 to 10?
			}
			break;
		case(2):
			switch(StatHolder)
			{
				case(1): return 12;// 6? to 18?
				case(2): return 15;// 10 to 20?
				case(3): return 15;// 11? to 20?
				case(4): return 15;// 10? to 20?
				case(5): return 15;// 10? to 20?
				case(6): return 15;// 10? to 20?
			}
			break;
		case(3):
			switch(StatHolder)
			{
				case(1): return 27;//27?
				case(2): return 25;//21 to 30?
				case(3): return 25;// 21 to 30
				case(4): return 25;// 21? to 30?
				case(5): return 25;// 21? to 30?
				case(6): return 25;// 21? to 30?
			}
			break;
		case(4):
			switch(StatHolder)
			{
				case(1): return 34;//34?
				case(2): return 35;// 31 to 40?
				case(3): return 35;// 31 to 40
				case(4): return 35;// 31? to 40?
				case(5): return 35;// 31? to 40?
				case(6): return 35;// 31? to 40?
			}
			break;
		case(5):
			switch(StatHolder)
			{
				case(1): return 43;//43?
				case(2): return 45;//41? to 50?
				case(3): return 46;// 42? to 51?
				case(4): return 46;// 41? to 51?
				case(5): return 46;// 41? to 51?
				case(6): return 46;// 41? to 51?
			}
			break;
		case(6):
			switch(StatHolder)
			{
				case(1): return 56;//52? to 60?
				case(2): return 55;//51? to 60?
				case(3): return 55;// 51? to 60?
				case(4): return 55;// 51? to 60?
				case(5): return 55;// 51? to 60?
				case(6): return 55;// 51? to 60?
			}
			break;
		case(7):
			switch(StatHolder)
			{
				case(1): return 65;//?
				case(2): return 65;// 61? to 70?
				case(3): return 66;//61? to 71?
				case(4): return 66;// 61? to 71?
				case(5): return 65;//?
				case(6): return 65;//?
			}
			break;
		case(8):
			switch(StatHolder)
			{
				case(1): return 76;//76?
				case(2): return 78;// 71? to 85?
				case(3): return 75;//?
				case(4): return 76;// 71? to 81?
				case(5): return 75;//?
				case(6): return 75;//?
			}
			break;
		case(9):
			switch(StatHolder)
			{
				case(1): return 85;//85?
				case(2): return 85;//?
				case(3): return 85;//?
				case(4): return 85;//80? to 90?
				case(5): return 85;//?
				case(6): return 85;//?
			}
			break;
		case(10):
			switch(StatHolder)
			{
				case(1): return 95;//?
				case(2): return 95;//?
				case(3): return 95;//?
				case(4): return 96;//96?
				case(5): return 95;//?
				case(6): return 95;//?
			}
			break;
		case(11):
			switch(StatHolder)
			{
				case(1): return 105;//?
				case(2): return 105;//?
				case(3): return 105;//?
				case(4): return 105;//?
				case(5): return 105;//?
				case(6): return 105;//?
			}
			break;
		case(12):
			switch(StatHolder)
			{
				case(1): return 125;//?
				case(2): return 125;//?
				case(3): return 125;//?
				case(4): return 125;//?
				case(5): return 125;//?
				case(6): return 125;//?
			}
			break;
		case(13):
			switch(StatHolder)
			{
				case(1): return 135;//?
				case(2): return 135;//?
				case(3): return 135;//?
				case(4): return 135;//?
				case(5): return 135;//?
				case(6): return 135;//?
			}
			break;
		case(14):
			switch(StatHolder)
			{
				case(1): return 150;//?
				case(2): return 150;//?
				case(3): return 150;//?
				case(4): return 150;//?
				case(5): return 150;//?
				case(6): return 150;//?
			}
			break;
		case(15):
			switch(StatHolder)
			{
				case(1): return 150;//?
				case(2): return 150;//?
				case(3): return 150;//?
				case(4): return 150;//?
				case(5): return 150;//?
				case(6): return 150;//?
			}
			break;
	}
	return 0;
}
void MainFrame::onFilterLevelUpdated(wxSpinEvent& event)
{
	wxUnusedVar(event);
	UpdatePlaneSelector();
	return;
}

void MainFrame::Localize(wxString Lang)
{
	if(Lang == Locale.Language){ return; }
	Locale = Localization(Lang);
	
	
	m_level1->SetLabel(Locale.Misc[7]);
	m_ShowEvent->SetLabel(Locale.Labels[3]);
	m_ShowNonEvent->SetLabel(Locale.Labels[4]);
	m_Descending->SetLabel(Locale.Labels[5]);
	m_Ascending->SetLabel(Locale.Labels[6]);
	
	m_cost->SetLabel(Locale.Misc[5]);
	m_cst->SetLabel(Locale.Misc[6]);
	m_level2->SetLabel(Locale.Misc[7]);
	
	m_statistics->SetLabel("[ " + Locale.Labels[0] + " ]");
	m_speed->SetLabel(Locale.Stats[0]);
	m_mobility->SetLabel(Locale.Stats[1]);
	m_stability->SetLabel(Locale.Stats[2]);
	m_aa->SetLabel(Locale.Stats[3]);
	m_ag->SetLabel(Locale.Stats[4]);
	m_defense->SetLabel(Locale.Stats[5]);
	
	m_parts->SetLabel("[ " + Locale.Labels[1] + " ]");
	m_body->SetLabel(Locale.Misc[2]);
	m_arms->SetLabel(Locale.Misc[3]);
	m_misc->SetLabel(Locale.Misc[4]);
	
	m_weapons->SetLabel("[ " + Locale.Labels[2] + " ]");
	m_GUN->SetLabel(Locale.Misc[0]);
	m_MSL->SetLabel(Locale.Misc[1]);
	
	
	
	m_FilterToggle->SetLabel(Locale.Misc[8]);
}

void MainFrame::LoadFileInResource(int name, int type, DWORD& size, const char*& data)
{
    HMODULE handle = ::GetModuleHandle(NULL);
    HRSRC rc = ::FindResource(handle, MAKEINTRESOURCE(name), MAKEINTRESOURCE(type));
    HGLOBAL rcData = ::LoadResource(handle, rc);
    size = ::SizeofResource(handle, rc);
    data = static_cast<const char*>(::LockResource(rcData));
}
void MainFrame::TreeChanged(wxTreeEvent& event)
{
	if(m_TreeSelector->GetSelection() == NULL){ return; }
	if(m_TreeSelector->HasChildren(m_TreeSelector->GetSelection())){ return; }
	wxUnusedVar(event);
	if(m_PlaneSelector->GetSelection() != wxNOT_FOUND){ m_PlaneSelector->Deselect(m_PlaneSelector->GetSelection()); }
	//m_PlaneSelector->SetStringSelection(m_TreeSelector->GetItemText(m_TreeSelector->GetSelection()));
	UpdatePlaneData();
}

void MainFrame::TreeChanging(wxTreeEvent& event)
{
	if(m_TreeSelector->HasChildren(event.GetItem())){ event.Veto(); }
}
void MainFrame::CollapseNodes(wxTreeEvent& event)
{
	if(m_TreeSelector->GetSelection() == NULL){ return; }
	for(wxTreeItemId ID = m_TreeSelector->GetSelection(); ID != m_TreeSelector->GetRootItem(); ID = m_TreeSelector->GetItemParent(ID))
	{
		if(ID == event.GetItem()){ event.Veto(); }
	}
	return;
}

void MainFrame::SetupTree()
{
	DWORD size = 0;
	const char* data = NULL;
	LoadFileInResource(IDR_RESEARCHTREEDATA, TEXTFILE, size, data);
	char* buffer = new char[size+1];
	::memcpy(buffer, data, size);
	buffer[size] = 0; // NULL terminator
	//::printf("Contents of text file: %s\n", buffer); // Print as ASCII text
	
	wxStringInputStream Sin(wxString::FromUTF8(buffer));
	wxTextInputStream File(Sin, "\\n");
	
	wxString line = File.ReadLine();
	wxStringTokenizer tokenizer("T,E,S,T", ",");
	while(!line.StartsWith("%"))
	{
		if(!line.StartsWith("#"))
		{
			TreeBranch *NewBranch = new TreeBranch();
			vector<int> TempVector(2);
			wxString substr = line.BeforeFirst('[');
			tokenizer.SetString(substr, "<,>", wxTOKEN_STRTOK);
			while(tokenizer.HasMoreTokens())
			{
				TempVector[0] = wxAtoi(tokenizer.GetNextToken());
				TempVector[1] = wxAtoi(tokenizer.GetNextToken());
				NewBranch->Parents.push_back(TempVector);
			}
			
			substr = (line.AfterFirst('[')).BeforeFirst('<');
			tokenizer.SetString(substr, "[|&]", wxTOKEN_STRTOK);
			while(tokenizer.HasMoreTokens())
			{
				TreeNode *NewNode = new TreeNode();
				NewNode->nodetype = wxAtoi(tokenizer.GetNextToken());
				NewNode->name = tokenizer.GetNextToken().ToStdString();
				NewNode->invisopoints = wxAtoi(tokenizer.GetNextToken());
				if(NewNode->nodetype == 1)
				{
					NewNode->cost[0] = tokenizer.GetNextToken().ToStdString();
					NewNode->partsize = tokenizer.GetNextToken().ToStdString();
					NewNode->SlotCosts[0] = wxAtoi(tokenizer.GetNextToken());
					NewNode->SlotCosts[1] = wxAtoi(tokenizer.GetNextToken());
					NewNode->SlotCosts[2] = wxAtoi(tokenizer.GetNextToken());
					NewNode->cst = wxAtoi(tokenizer.GetNextToken());
					/*int i = wxAtoi(tokenizer.GetNextToken());
					switch(i)
					{
						case(1):
							NewNode->Type = ENGINE;
							break;
						case():
							break;
					}*/
					NewNode->PI = nullptr;
				}
				else if(NewNode->nodetype > 1 && NewNode->nodetype < 6)
				{
					for(std::list<PlaneInfo>::iterator curr = PlaneData.begin(), last = PlaneData.end(); curr != last; ++curr)
					{
						if(curr->AircraftName.find(NewNode->name) != wxString::npos)
						{
							for(int i = 0; i < 15; i++){ NewNode->cost[i] = curr->Cost[1][i]; }
							NewNode->maxlevel = curr->MaxLevel;
							NewNode->PI = &(*curr);
							curr->TNode = NewNode;
							break;
						}
					}
				}
				NewBranch->Nodes.push_back(NewNode);
				//Nodes.push_back(NewNode);
			}
			
			substr = (line.AfterFirst(']')).BeforeFirst('[');
			tokenizer.SetString(substr, "<,>", wxTOKEN_STRTOK);
			if(tokenizer.HasMoreTokens())
			{
				//ResearchTreeData.ResearchTree[wxAtoi(tokenizer.GetNextToken())][wxAtoi(tokenizer.GetNextToken())] = NewBranch;
				NewBranch->loc[0] = wxAtoi(tokenizer.GetNextToken());
				NewBranch->loc[1] = wxAtoi(tokenizer.GetNextToken());
				//std::cout << NewBranch->loc[0] << " : " << NewBranch->loc[1] << endl << std::flush;
			}
			
			substr = ((line.AfterFirst(']')).AfterFirst('>')).BeforeFirst('<');
			tokenizer.SetString(substr, "[|]", wxTOKEN_STRTOK);
			if(tokenizer.HasMoreTokens())
			{
				NewBranch->RankBlock = tokenizer.GetNextToken();
				NewBranch->RankBlockOffset[0] = wxAtoi(tokenizer.GetNextToken());
				NewBranch->RankBlockOffset[1] = wxAtoi(tokenizer.GetNextToken());
			}
			
			substr = line.AfterLast(']');
			tokenizer.SetString(substr, "<,>", wxTOKEN_STRTOK);
			while(tokenizer.HasMoreTokens())
			{
				TempVector[0] = wxAtoi(tokenizer.GetNextToken());
				TempVector[1] = wxAtoi(tokenizer.GetNextToken());
				NewBranch->Children.push_back(TempVector);
			}
			NewBranch->valid = true;
			ResearchTreeData.TreeBranches.push_back(NewBranch);
		}
		line = File.ReadLine();
	}
	delete[] buffer;
}

void MainFrame::SetupSpecialAircraft()
{
	DWORD size = 0;
	const char* data = NULL;
	LoadFileInResource(IDR_SPECIALAIRCRAFTDATA, TEXTFILE, size, data);
	char* buffer = new char[size+1];
	::memcpy(buffer, data, size);
	buffer[size] = 0; // NULL terminator
	//::printf("Contents of text file: %s\n", buffer); // Print as ASCII text
	
	wxStringInputStream Sin(wxString::FromUTF8(buffer));
	wxTextInputStream File(Sin, "\\n");
	
	wxString line = File.ReadLine();
	wxStringTokenizer tokenizer("T,E,S,T", ",");
	while(!line.StartsWith("%"))
	{
		if(!line.StartsWith("#"))
		{
			TreeNode NewNode;// = new TreeNode();
			tokenizer.SetString(line, "[|]", wxTOKEN_STRTOK);
			NewNode.nodetype = wxAtoi(tokenizer.GetNextToken());
			NewNode.name = tokenizer.GetNextToken().ToStdString();
			NewNode.invisopoints = wxAtoi(tokenizer.GetNextToken());
			NewNode.cost[0] = "0";
			for(std::list<PlaneInfo>::iterator curr = PlaneData.begin(), last = PlaneData.end(); curr != last; ++curr)
			{
				if(curr->AircraftName.find(NewNode.name) != wxString::npos)
				{
					NewNode.PI = &(*curr);
					curr->TNode = &NewNode;
					for(int i = 0; i < 15; i++){ NewNode.cost[i] = curr->Cost[1][i]; }
					NewNode.maxlevel = curr->MaxLevel;
					break;
				}
			}
			NewNode.stars = wxAtoi(tokenizer.GetNextToken());
			NewNode.abbreviation = tokenizer.GetNextToken();
			NewNode.valid = true;
			SpecialAircraftData.push_back(NewNode);
			//Nodes.push_back(&NewNode);
		}
		line = File.ReadLine();
	}
	delete[] buffer;
}

void MainFrame::SetupSpecialWeapons()
{
	DWORD size = 0;
	const char* data = NULL;
	LoadFileInResource(IDR_SPECIALWEAPONDATA, TEXTFILE, size, data);
	char* buffer = new char[size+1];
	::memcpy(buffer, data, size);
	buffer[size] = 0; // NULL terminator
	//::printf("Contents of text file: %s\n", buffer); // Print as ASCII text
	
	wxStringInputStream Sin(wxString::FromUTF8(buffer));
	wxTextInputStream File(Sin, "\\n");
	
	wxString line = File.ReadLine();
	wxStringTokenizer tokenizer("T,E,S,T", ",");
	while(!line.StartsWith("%"))
	{
		if(!line.StartsWith("#"))
		{
			WeaponInfo WI;
			WI.weapontype = wxAtoi(line);
			line = File.ReadLine();
			/*switch(wxAtoi(line))//Valid Part types
			{
				case():
					break;
			}*/
			WI.WeaponName = File.ReadLine().ToStdString();
			WI.Abbreviation = File.ReadLine().ToStdString();
			WI.invisopoints = wxAtoi(File.ReadLine());
			for(int i = 0; i < 6; i++)
			{
				tokenizer.SetString(File.ReadLine(), " \t", wxTOKEN_STRTOK);
				int j = 0;
				while(tokenizer.HasMoreTokens()){ WI.StatGrades[i][j] = tokenizer.GetNextToken().ToStdString(), j++; }
			}
			for(int i = 0; i < 2; i++)
			{
				tokenizer.SetString(File.ReadLine(), " \t", wxTOKEN_STRTOK);
				int j = 0;
				while(tokenizer.HasMoreTokens()){ WI.Cost[i][j] = tokenizer.GetNextToken().ToStdString(), j++; }
			}
			TreeNode NewNode(&WI);
			WI.WeaponNode = &NewNode;
			SpecialWeaponsData.push_back(NewNode);
			//Nodes.push_back(&NewNode);
		}
		line = File.ReadLine();
	}
	delete[] buffer;
}

void MainFrame::LoadSaveData()
{
	wxFile SaveData;
	if(!SaveData.Exists("SHIT.txt")){ return; }
	SaveData.Open("SHIT.txt", wxFile::read);
	if(!SaveData.IsOpened()){ return; }
	
	wxString Save;
	SaveData.ReadAll(&Save);
	wxStringTokenizer tokenizer(Save.AfterFirst('(').BeforeFirst(')'), "<|>", wxTOKEN_STRTOK);			//First set, Research Tree
	while(tokenizer.HasMoreTokens())
	{
		wxString name = tokenizer.GetNextToken();
		int T = wxAtoi(tokenizer.GetNextToken());
		for(std::list<TreeBranch*>::const_iterator B = ResearchTreeData.TreeBranches.begin(), L = ResearchTreeData.TreeBranches.end(); B != L; ++B)
		{
			for(std::list<TreeNode*>::const_iterator curr = (*B)->Nodes.begin(), last = (*B)->Nodes.end(); curr != last; ++curr)
			{
				if((*curr)->name == name)
				{
					(*curr)->aquired = true;
					(*B)->unlocked = true;
					if(T > 0){ (*curr)->level = T; }
					break;
				}
			}
			
		}
	}
	tokenizer.Reinit(Save.AfterFirst('[').BeforeFirst(']'));							//Second set, Special Aircraft
	while(tokenizer.HasMoreTokens())
	{
		wxString name = tokenizer.GetNextToken();
		int T = wxAtoi(tokenizer.GetNextToken());
		for(std::list<TreeNode>::iterator curr = SpecialAircraftData.begin(), last = SpecialAircraftData.end(); curr != last; ++curr)
		{
			if(curr->name == name)
			{
				curr->aquired = true;
				if(T > 0){ curr->level = T; }
				break;
			}
		}
	}
	tokenizer.Reinit(Save.AfterFirst('{').BeforeFirst('}'));							//Third set, Special Weapons
	while(tokenizer.HasMoreTokens())
	{
		wxString name = tokenizer.GetNextToken();
		int T = wxAtoi(tokenizer.GetNextToken());
		for(std::list<TreeNode>::iterator curr = SpecialWeaponsData.begin(), last = SpecialWeaponsData.end(); curr != last; ++curr)
		{
			if(curr->name == name)
			{
				curr->aquired = true;
				if(T > 0){ curr->level = T; }
				break;
			}
		}
	}
	return;
}

void MainFrame::onSpecialAircraftOpen(wxCommandEvent& event)
{
	if(SA == nullptr)
	{
		SA = new SpecialAircraft(this, &SpecialAircraftData); 
		SA->Show();
	}
	else
	{
		SA->Thaw();
		SA->Show();
	}
	return;
}

void MainFrame::onSpecialWeaponsOpen(wxCommandEvent& event)
{
	if(SW == nullptr)
	{
		SW = new SpecialWeapon(this, &SpecialWeaponsData); 
		SW->Show();
	}
	else
	{
		SW->Thaw();
		SW->Show();
	}
	return;	
}

void MainFrame::onTreeOpen(wxCommandEvent& event)
{
	//if(this->FindWindow(wxT("ResearchTreeBaseClass")) == NULL)
	if(RTree == nullptr)
	{
		RTree = new ResearchTree(this, &ResearchTreeData);
		RTree->Show();
	}
	else
	{
		RTree->Thaw();
		RTree->Show();
	}
	return;
}

void MainFrame::onSetBuilderOpen(wxCommandEvent& event)
{
	if(SB == nullptr)
	{
		SB = new SetBuilder(this, &ResearchTreeData, &SpecialAircraftData, &SpecialWeaponsData);
		SB->Show();
	}
	else
	{
		SB->Thaw();
		SB->Show();
	}
	return;
}

void MainFrame::onClose(wxCloseEvent& event)
{
	wxUnusedVar(event);
	if(RTree != nullptr){ RTree->Destroy(); }
	if(SA != nullptr){ SA->Destroy(); }
	if(SW != nullptr){ SW->Destroy(); }
	if(SB != nullptr){ SB->Destroy(); }
	Freeze();
    Destroy();
}
