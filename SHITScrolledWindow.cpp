#include "SHITScrolledWindow.h"

SHITScrolledWindow::SHITScrolledWindow(wxWindow *parent, list<TreeNode> *D)
	: wxScrolledWindow(parent)
{
	data = D;
	fontsize = 10;
	first = true, update = false, edit = false;
	scale = 1.0, lastscale = 1.0;
	emode = NA;
}

/*void SHITScrolledWindow::OnDraw(wxDC &dc)
{
	if(update)
	{
		update = false;
		Image.Create(width*scale, height*scale);
		UpdateImage();
	}
	dc.DrawBitmap(Image,0,0,false);
	return;
}*/

wxFontInfo SHITScrolledWindow::MakePanelFont(int size)
{
	wxFontInfo TF(size);
	TF.Family(wxFONTFAMILY_MODERN);
	TF.Bold(true);
	return TF;
}

wxColour SHITScrolledWindow::GetNodeColor(const TreeNode *Node)
{
	switch(Node->nodetype)
	{
		case(0):
			return wxColour(0,0,0);
		case(1):
			if(Node->aquired){ return wxColour(211,160,53); }
			else{ return wxColour(98,75,33); }
		case(2):
			if(Node->aquired){ return wxColour(185,69,54); }
			else{ return wxColour(93,36,26); }
		case(3):
			if(Node->aquired){ return wxColour(38,111,190); }
			else{ return wxColour(0,49,112); }
		case(4):
			if(Node->aquired){ return wxColour(163,89,184); }
			else{ return wxColour(63,42,103); }
		case(5):
			if(Node->aquired){ return wxColour(47,161,49); }
			else{ return wxColour(23,80,24); }
		case(6):
			if(Node->aquired){ return wxColour(185,69,54); }
			else{ return wxColour(93,36,26);; }
		case(7):
			if(Node->aquired){ return wxColour(38,111,190); }
			else{ return wxColour(0,49,112); }
		case(8):
			if(Node->aquired){ return wxColour(134,187,109); }
			else{ return wxColour(134,187,109); }
		case(9):
			if(Node->aquired){ return wxColour(163,89,184); }
			else{ return wxColour(63,42,103); }
	}
	return wxColour(0,0,0);
}
