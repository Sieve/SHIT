#ifndef SHITFRAME_H
#define SHITFRAME_H

#include <wx/frame.h> // Base class: wxFrameBase

class SHITFrame : public wxFrameBase
{
public:
	SHITFrame();
	~SHITFrame(){}
	
	int ZoomLevel;
	float ZoomLevels[3];

	

};

#endif // SHITFRAME_H
