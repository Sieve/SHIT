#ifndef DATASTRUCTS_H
#define DATASTRUCTS_H
#include <wx/list.h>
#include <string>
using namespace std;
#include <wx/arrstr.h>
#include <wx/treebase.h>
#include <vector>
using namespace std;
#include <list>
using namespace std;

enum ObjectType
{
	DEBUG,
	ATTACKER,
	BOMBER,
	FIGHTER,
	MULTIROLE,
	PART,
	ATTACKERSPW,
	FIGHTERSPW,
	SPECIALSPW,
	SPECIALSPECIALSPW,
};

enum PartType
{
	NONE,
	ENGINE,
	WING,
	HULL,
	GUN,
	MISSILE,
	SPMISSILE,
	SPBOMB,
};

enum Dir
{
	UP,
	DOWN,
	LEFT,
	RIGHT,
};

struct TreeNode;
struct PlaneInfo
{
	TreeNode *TNode;
	string AircraftName;    //Species
    string AircraftFamily;  //Genus
    string CoO;             //Family
    string Manufacturer;
    //string Role;
	ObjectType Role;
    bool isEvent;
    int MaxLevel;
	int Stats[6][15];				//0 - Speed, 1 - Mobility, 2 - Stability, 3 - AA, 4 - AG, 5 - Defense
	string StatGrades[6][15];
	int Ammo[5][15];				//0 - GUN, 1 - MSL, 2 - SPW1, 3 - SPW2, 4 - SPW3
    string SP1Name;
    string SP2Name;
    string SP3Name;
	int SLOTS[3][15];				//0 - BODY, 1 - ARMS, 2 - MISC
	string Cost[2][15];				//0 - Cst, 1 - Cost
    int Tier;

    PlaneInfo(){ AircraftName = "None", AircraftFamily = "N/A", CoO = "N/A", Manufacturer = "N/A", Role = DEBUG, isEvent = false, MaxLevel = 1, SP1Name = "N/A", SP2Name = "N/A", SP3Name = "N/A", Tier = 0; }
};

struct WeaponInfo
{
	string WeaponName;
	string Abbreviation;
	int weapontype;
	int Stats[6][5];				//0 - Speed, 1 - Mobility, 2 - Stability, 3 - AA, 4 - AG, 5 - Defense
	string StatGrades[6][5];
	string Cost[2][5];
	std::list<PlaneInfo*> Compatible;
	TreeNode *WeaponNode;
	int invisopoints;
	PartType ValidPart;
	
	WeaponInfo(){ WeaponName = "", Abbreviation = "", weapontype = 0; }
	
	/*void CheckAquired()
	{
		if(!Compatible.empty()){ WeaponNode->aquired = true; }
		else{ WeaponNode->aquired = false; }
		return;
	}*/
};

struct TempData//For list sorting and whatnot
{
	string Name;
	float Value;
	string Info;
	
	bool operator<(TempData const &other)  { return Value < other.Value; }
	
	TempData(string N, float V){ Name = N, Value = V, Info = ""; }
	TempData(string N, string I){ Name = N, Value = 0, Info = I; }
};

struct TreeData//For list sorting and whatnot
{
	string Name;
	wxTreeItemId ID;
	
	TreeData(string N, wxTreeItemId I){ Name = N, ID = I; }
};

struct TempList
{
	string Label;
	std::list<string> Values;
	
	TempList(string L){ Label = L; }
};

struct Localization
{
	wxString Language;
	wxString None;
    wxArrayString Roles;
    wxArrayString SPWs;
    wxArrayString Countries;
	wxArrayString Manufacturers;
	wxArrayString Stats;
	wxArrayString Misc;
	wxArrayString Labels;
	
	Localization()
	{
		Language = "English", None = "None";
		Roles.Add("ATTACKER"), Roles.Add("BOMBER"), Roles.Add("FIGHTER"), Roles.Add("MULTIROLE");
		//SPWs.Add("4AAM"), SPWs.Add("4AGM"), SPWs.Add("6AAM"), SPWs.Add("ECM"), SPWs.Add("ESM"), SPWs.Add("FAEB"), SPWs.Add("GPB"), SPWs.Add("HCAA"), SPWs.Add("HVAA"), SPWs.Add("LAGM"), SPWs.Add("LASM"), SPWs.Add("MGP"), SPWs.Add("MPBM"), SPWs.Add("QAAM"), SPWs.Add("RKTL"), SPWs.Add("SAAM"), SPWs.Add("SFFS"), SPWs.Add("SOD"), SPWs.Add("TLS"), SPWs.Add("UGB");
		//Manufacturers.Add("Boeing"), Manufacturers.Add("Dassault Aviation"), Manufacturers.Add("Lockheed Martin"), Manufacturers.Add("Mikoyan OKB"), Manufacturers.Add("Sukoi OKB");
		//Countries.Add("France"), Countries.Add("Japan"), Countries.Add("Russia"), Countries.Add("Sweden"), Countries.Add("United Kingdom"), Countries.Add("United States of America");
		Stats.Add("Speed"), Stats.Add("Mobility"), Stats.Add("Stability"), Stats.Add("Atk Dmg (AIR)"), Stats.Add("Atk Dmg (GND)"), Stats.Add("Defense"), Stats.Add("Part Slots");
		Misc.Add("GUN"), Misc.Add("MSL"), Misc.Add("BODY"), Misc.Add("ARMS"), Misc.Add("MISC"), Misc.Add("Cost"), Misc.Add("Cst"), Misc.Add("Level"), Misc.Add("Toggle Filter");
		Labels.Add("STATISTICS"), Labels.Add("PARTS"), Labels.Add("WEAPONS"), Labels.Add("Event Planes"), Labels.Add("Non-Event Planes"), Labels.Add("Descending"), Labels.Add("Ascending");
	}
	
	Localization(wxString Lang)
	{
		if(Lang == "English"){ Localization(); }
	}
};

struct TreeNode
{
	PlaneInfo *PI;
	WeaponInfo *WI;
	int nodetype;
		//0 - Debug
		//1 - Part
		//2 - Attacker
		//3 - Fighter
		//4 - Multirole
		//5 - Bomber
		//5 - Attcker SPW
		//6 - Fighter SPW
		//7 - Other SPW
	string name;
	string abbreviation;
	bool aquired;
	bool valid;
	//Not valid for parts
	int level;
	int maxlevel;
	int stars;
	int cst;
	PartType Type;
	string cost[15];
	string partsize;
	//invisible xp values, 1 point == 0.01%
	int invisopoints;	
	vector<int> SlotCosts;
	
	bool altered;
	
	TreeNode() : SlotCosts(3)
	{
		nodetype = 0, name = "", aquired = false, valid = false, level = 0, maxlevel = 0, stars = 0, cst = 0, partsize = "", invisopoints = 0, altered = true;
		Type = NONE;
		PI = nullptr, WI = nullptr;
	}
	
	TreeNode(TreeNode* N) : SlotCosts(3)
	{
		nodetype = N->nodetype, name = N->name, aquired = N->aquired, level = N->level, partsize = N->partsize, invisopoints = N->invisopoints, altered = N->altered;
		PI = N->PI, WI = N->WI;
		for(int i = 0; i < 15; i++){ cost[i] = N->cost[i]; }
	}
	
	TreeNode(WeaponInfo* W)
	{
		nodetype = W->weapontype, name = W->Abbreviation, level = 0, maxlevel = 5, aquired = false, invisopoints = 0;
		cost[0] = W->Cost[1][0], cost[1] = W->Cost[1][1], cost[2] = W->Cost[1][2], cost[3] = W->Cost[1][3], cost[4] = W->Cost[1][4], cost[5] = W->Cost[1][5];
		valid = true;
		WI = W;
	}
	
	bool operator<(TreeNode const &other)
	{
		int len = std::min(name.length(), other.name.length());
		for(int i = 0; i < len; i++)
		{
			if(name[i] != other.name[i]){ return name[i] < other.name[i]; }
		}
		if(nodetype == 1 && other.nodetype == 1)
		{
			if(partsize == "Lt" || (partsize == "S" && other.partsize != "Lt") || (partsize == "M" && !(partsize == "Lt" || partsize == "S")) || (partsize == "L" && other.partsize == "LL")){ return true; }
			else{ return false; }
		}
		return name.length() < other.name.length();
	}
};

struct TreeNode_Comparator
{
	bool operator()(TreeNode* lhs, TreeNode* rhs) const
	{
		return *lhs < *rhs;
	}
};

struct TreeBranch
{
	std::list<vector<int> > Parents;
	std::list<vector<int> > Children;
	std::list<TreeBranch*> ChildBranches;
	std::list<TreeBranch*> ParentBranches;
	std::list<TreeNode*> Nodes;
	std::vector<int> loc;
	std::string RankBlock;//Valid if it is FOLLOWED by a rank block
	std::vector<int> RankBlockOffset;
	bool valid;
	bool unlocked;
	
	TreeBranch() : loc(2), RankBlockOffset(2)
	{ RankBlock = "", valid = false, unlocked = false; }
	
	void LockChildBranches()
	{
		for(list<TreeNode*>::const_iterator curr = Nodes.begin(), last = Nodes.end(); curr != last; ++curr){ (*curr)->aquired = false; }
		for(list<TreeBranch*>::const_iterator curr = ChildBranches.begin(), last = ChildBranches.end(); curr != last; ++curr)
		{
			(*curr)->unlocked = false;
			(*curr)->LockChildBranches();
		}
		return;
	}
	
	void UpdateUnlocked()
	{
		for(list<TreeBranch*>::const_iterator B = ParentBranches.begin(), E = ParentBranches.end(); B != E; ++B)
		{
			unlocked = false;
			if((*B)->unlocked)
			{
				bool nodesunlocked = true;
				for(list<TreeNode*>::const_iterator N = (*B)->Nodes.begin(), E = (*B)->Nodes.end(); N != E; ++N)
				{
					if(!(*N)->aquired){ nodesunlocked = false; }
				}
				if(nodesunlocked)
				{
					unlocked = true;
					break;
				}
			}
		}
		for(list<TreeBranch*>::const_iterator B = ChildBranches.begin(), E = ChildBranches.end(); B != E; ++B){ (*B)->UpdateUnlocked(); }		
		if(!unlocked){ for(list<TreeNode*>::const_iterator N = Nodes.begin(), E = Nodes.end(); N != E; ++N){ (*N)->aquired = false; } }

		return;
	}
};

struct TreeBase
{
	//TreeBranch *ResearchTree[15][15];
	std::list<TreeBranch*> TreeBranches;
	
	TreeBase(){}
};

struct HitZone
{
	TreeNode* node;
	TreeBranch* branch;
	wxPoint Corner;
	int width;
	int height;
	
	HitZone(TreeNode* N, TreeBranch *B, int x, int y, int w, int h)
	{
		node = N;
		branch = B;
		Corner = wxPoint(x,y);
		width = w, height = h;
	}
	
	HitZone(TreeNode* N, int x, int y, int w, int h)
	{
		node = N;
		Corner = wxPoint(x,y);
		width = w, height = h;
	}
};

#endif // DATASTRUCTS_H
