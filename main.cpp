#include <wx/app.h>
#include <wx/event.h>
#include "MainFrame.h"
#include "wxcrafter.h"
#include <wx/image.h>
#include <wx/gdicmn.h>
#include <wx/icon.h>

// Define the MainApp
class MainApp : public wxApp
{
public:
    MainApp() {}
    virtual ~MainApp() {}

    virtual bool OnInit()
	{
        // Add the common image handlers
        wxImage::AddHandler( new wxPNGHandler );

        MainFrame *mainFrame = new MainFrame(NULL);
        SetTopWindow(mainFrame);
        return GetTopWindow()->Show();
    }
};

DECLARE_APP(MainApp)
IMPLEMENT_APP(MainApp)
