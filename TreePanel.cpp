/*#include "TreePanel.h"
#include <wx/msw/brush.h>
#include <wx/font.h>

TreePanel::TreePanel(wxWindow *parent, TreeBase *B):wxPanel(parent)
{
	//wxImage::AddHandler( new wxXPMHandler );
	//bitmap = wxBitmap(progress_under_xpm);
	// get the image size
	//width  = bitmap.GetWidth();
	//height = bitmap.GetHeight();
	Tree = B;
	width = 50 + (15*108);
	height = 50 + (15*182);
	this->SetBackgroundColour(wxColour(2,13,33));
	SetDoubleBuffered(true);
	SetSize(width, height);
	//parent->SetSize(width, height);
	Connect(wxEVT_PAINT, wxPaintEventHandler(TreePanel::OnPaint));
}

void TreePanel::OnPaint(wxPaintEvent& event)
{
	wxPaintDC dc(this);
	dc.SetTextForeground(wxColour(204,211,229));
	dc.SetBrush(wxColour(213,208,202));
	dc.SetPen(wxPen(wxColour(213,208,202), 0));
	for(int x = 0; x < 16; x++)
	{
		for(int y = 0; y < 16; y++)
		{
			if(Tree->ResearchTree[x][y] != NULL)
			{
				TreeBranch *TB = Tree->ResearchTree[x][y];
				if(TB->Nodes.size() == 1){ dc.DrawRectangle(wxRect(25 + (x*108), 25 + (y*182), 72, 72)); }
				else{ dc.DrawRectangle(wxRect(25 + (x*108), 25 + (y*182) - 45, 72, 162)); }
				
			}
		}
	}
	return;
}

wxColour TreePanel::GetNodeColor(TreeNode *Node)
{
	switch(Node->nodetype)
	{
		case(0):
			return wxColour(0,0,0);
		case(1):
			return wxColour(211,160,53);
		case(2):
			return wxColour(185,69,54);
		case(3):
			return wxColour(38,111,190);
		case(4):
			return wxColour(163,89,184);
		case(5):
			return wxColour(185,69,54);
		case(6):
			return wxColour(38,111,190);
		case(7):
			return wxColour(134,187,109);
		case(8):
			return wxColour(163,89,184);
	}
	return wxColour(0,0,0);
}*/