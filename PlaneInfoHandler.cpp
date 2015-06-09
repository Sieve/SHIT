#include "PlaneInfoHandler.h"
#include <wx/wfstream.h>
#include <wx/txtstrm.h>
#include <wx/string.h>
#include <wx/list.h>
#include <wx/tokenzr.h>
#include <wx/textfile.h>
#include <iostream>

PlaneInfoHandler::PlaneInfoHandler()
{
	SortEvent = true, SortNonEvent = true, SortDescending = true;
	PlaneData.push_front(PlaneInfo());	
	
	wxTextFile File(wxT("C:\\Users\\Spencer\\Documents\\CodeLiteProjects\\SHIT\\resources\\PlaneText.txt"));
	File.Open();
	//wxFileInputStream input(wxT("C:\\Users\\Spencer\\Documents\\CodeLiteProjects\\SHIT\\resources\\PlaneText.txt"));
	//wxTextInputStream text(input, wxT("\x09"), wxConvUTF8 );
	wxString line;
	for ( line = File.GetFirstLine(); !File.Eof(); line = File.GetNextLine() )
	{
		if(!line.StartsWith("#"))
		{
			File.GetNextLine(), line = File.GetNextLine();
			PlaneInfo PI;
			
			PI.AircraftName = line.ToStdString(), File.GetNextLine();// std::cout << PI.AircraftName << "\n" << std::flush;
			PI.AircraftFamily = File.GetNextLine().ToStdString(), File.GetNextLine();
			PI.CoO = File.GetNextLine().ToStdString(), File.GetNextLine();
			PI.Manufacturer = File.GetNextLine().ToStdString(), File.GetNextLine();
			wxString Role = File.GetNextLine();
			if(Role == "ATTACKER"){ PI.Role = ATTACKER; }
			else if(Role == "FIGHTER"){ PI.Role = FIGHTER; }
			else if(Role == "MULTIROLE"){ PI.Role = MULTIROLE; }
			else{ PI.Role = DEBUG; }
			File.GetNextLine();
			PI.isEvent = File.GetNextLine().StartsWith("1"), File.GetNextLine();
			PI.MaxLevel = wxAtoi(File.GetNextLine()), File.GetNextLine();
		
			wxStringTokenizer tokenizer("T E S T", " ");
			for(int l = 0; l < 6; l++)//Set stats
			{
				tokenizer.Reinit(File.GetNextLine()), File.GetNextLine();
				for(int i =0; i < PI.MaxLevel; i++){ PI.Stats[l][i] = wxAtoi(tokenizer.GetNextToken()); }
				tokenizer.Reinit(File.GetNextLine()), File.GetNextLine();
				for(int i =0; i < PI.MaxLevel; i++){ PI.StatGrades[l][i] = tokenizer.GetNextToken().ToStdString(); }
			}
			
			tokenizer.Reinit(File.GetNextLine()), File.GetNextLine();//GUN
			for(int i =0; i < PI.MaxLevel; i++){ PI.Ammo[0][i] = wxAtoi(tokenizer.GetNextToken()); }
			tokenizer.Reinit(File.GetNextLine()), File.GetNextLine();//MSL
			for(int i =0; i < PI.MaxLevel; i++){ PI.Ammo[1][i] = wxAtoi(tokenizer.GetNextToken()); }
			PI.SP1Name = File.GetNextLine().ToStdString(), File.GetNextLine();
			tokenizer.Reinit(File.GetNextLine()), File.GetNextLine();//SPW1
			for(int i =0; i < PI.MaxLevel; i++){ PI.Ammo[2][i] = wxAtoi(tokenizer.GetNextToken()); }
			PI.SP2Name = File.GetNextLine().ToStdString(), File.GetNextLine();
			tokenizer.Reinit(File.GetNextLine()), File.GetNextLine();//SPW2
			for(int i =0; i < PI.MaxLevel; i++){ PI.Ammo[3][i] = wxAtoi(tokenizer.GetNextToken()); }
			PI.SP3Name = File.GetNextLine().ToStdString(), File.GetNextLine();
			tokenizer.Reinit(File.GetNextLine()), File.GetNextLine();//SPW3
			for(int i =0; i < PI.MaxLevel; i++){ PI.Ammo[4][i] = wxAtoi(tokenizer.GetNextToken()); }
			
			for(int l = 0; l < 3; l++)//Set slots
			{
				tokenizer.Reinit(File.GetNextLine()), File.GetNextLine();
				int T = wxAtoi(tokenizer.GetNextToken());
				for(int i = 0; i < PI.MaxLevel; i++)
				{
					if(i == 6){ T = wxAtoi(tokenizer.GetNextToken()); }
					if(i == 15){ T = wxAtoi(tokenizer.GetNextToken()); }
					PI.SLOTS[l][i] = T;
				}
			}
			tokenizer.Reinit(File.GetNextLine()), File.GetNextLine();//Cst
			for(int i =0; i < PI.MaxLevel; i++){ PI.Cost[0][i] = wxAtoi(tokenizer.GetNextToken()); }
			tokenizer.Reinit(File.GetNextLine()), File.GetNextLine();//Cost
			for(int i =0; i < PI.MaxLevel; i++){ PI.Cost[1][i] = wxAtoi(tokenizer.GetNextToken()); }
			PlaneData.push_back(PI);
		}
	}

	/*while(input.IsOk() && !input.Eof() )
	{
		wxString line = text.ReadLine();
		while(line.StartsWith("#")){ line = text.ReadLine(); }
		
		PlaneInfo PI;
		
		PI.AircraftName = line.ToStdString(), text.ReadLine();
		PI.AircraftFamily = text.ReadLine().ToStdString(), text.ReadLine();
        PI.CoO = text.ReadLine().ToStdString(), text.ReadLine();
        PI.Manufacturer = text.ReadLine().ToStdString(), text.ReadLine();
        PI.Role = text.ReadLine().ToStdString(), text.ReadLine();
        PI.isEvent = text.ReadLine().StartsWith("1"), text.ReadLine();
        PI.MaxLevel = wxAtoi(text.ReadLine()), text.ReadLine();
	
		wxStringTokenizer tokenizer("T E S T", " ");
		for(int l = 0; l < 6; l++)//Set stats
		{
			tokenizer.Reinit(text.ReadLine()), text.ReadLine();
			for(int i =0; i < PI.MaxLevel; i++){ PI.Stats[l][i] = wxAtoi(tokenizer.GetNextToken()); }
			tokenizer.Reinit(text.ReadLine()), text.ReadLine();
			for(int i =0; i < PI.MaxLevel; i++){ PI.StatGrades[l][i] = tokenizer.GetNextToken().ToStdString(); }
		}
		
		tokenizer.Reinit(text.ReadLine()), text.ReadLine();//GUN
		for(int i =0; i < PI.MaxLevel; i++){ PI.Ammo[0][i] = wxAtoi(tokenizer.GetNextToken()); }
		tokenizer.Reinit(text.ReadLine()), text.ReadLine();//MSL
		for(int i =0; i < PI.MaxLevel; i++){ PI.Ammo[1][i] = wxAtoi(tokenizer.GetNextToken()); }
		PI.SP1Name = text.ReadLine().ToStdString(), text.ReadLine();
		tokenizer.Reinit(text.ReadLine()), text.ReadLine();//SPW1
		for(int i =0; i < PI.MaxLevel; i++){ PI.Ammo[2][i] = wxAtoi(tokenizer.GetNextToken()); }
		PI.SP2Name = text.ReadLine().ToStdString(), text.ReadLine();
		tokenizer.Reinit(text.ReadLine()), text.ReadLine();//SPW2
		for(int i =0; i < PI.MaxLevel; i++){ PI.Ammo[3][i] = wxAtoi(tokenizer.GetNextToken()); }
		PI.SP3Name = text.ReadLine().ToStdString(), text.ReadLine();
		tokenizer.Reinit(text.ReadLine()), text.ReadLine();//SPW3
		for(int i =0; i < PI.MaxLevel; i++){ PI.Ammo[4][i] = wxAtoi(tokenizer.GetNextToken()); }
		
		for(int l = 0; l < 3; l++)//Set slots
		{
			tokenizer.Reinit(text.ReadLine()), text.ReadLine();
			int T = wxAtoi(tokenizer.GetNextToken());
			for(int i = 0; i < PI.MaxLevel; i++)
			{
				if(i == 6){ T = wxAtoi(tokenizer.GetNextToken()); }
				if(i == 15){ T = wxAtoi(tokenizer.GetNextToken()); }
				PI.SLOTS[l][i] = T;
			}
		}
		tokenizer.Reinit(text.ReadLine()), text.ReadLine();//Cst
		for(int i =0; i < PI.MaxLevel; i++){ PI.Cost[0][i] = wxAtoi(tokenizer.GetNextToken()); }
		tokenizer.Reinit(text.ReadLine()), text.ReadLine();//Cost
		for(int i =0; i < PI.MaxLevel; i++){ PI.Cost[1][i] = wxAtoi(tokenizer.GetNextToken()); }
	}*/
	std::cout << "Load Finished\n" << std::flush;
}

void PlaneInfoHandler::updatePlaneData(){}
void PlaneInfoHandler::updateFilterList(){}
void PlaneInfoHandler::SetEvent(bool Event)
{
		if(SortEvent != Event)
		{
			SortEvent = Event;
			updateFilterList();
		}
}

void PlaneInfoHandler::SetNonEvent(bool NonEvent)
{
		if(SortNonEvent != NonEvent)
		{
			SortNonEvent = NonEvent;
			updateFilterList();
		}
}

void PlaneInfoHandler::SetSorting(bool sorting)
{
	if(SortDescending != sorting)
	{
		SortDescending = sorting;
		updateFilterList();
	}
}

PlaneInfoHandler::~PlaneInfoHandler()
{
}

