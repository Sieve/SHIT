#include <wx/wx.h>
#include <wx/image.h>

// application class
class wxMiniApp : public wxApp
{
public:
	// function called at the application initialization
	virtual bool OnInit();

	// event handler for button click
	void OnClick(wxCommandEvent& event) 
	{
		wxImage Tree("Tree.png");
		
		GetTopWindow()->Close();
	}
};

IMPLEMENT_APP(wxMiniApp);

bool wxMiniApp::OnInit()
{
	// create a new frame and set it as the top most application window
	SetTopWindow( new wxFrame( NULL, -1, wxT(""), wxDefaultPosition, wxSize( 100, 50) ) );
	wxImage::AddHandler( new wxPNGHandler );

	// create new button and assign it to the main frame
	new wxButton( GetTopWindow(), wxID_EXIT, wxT("Click!") );

	// connect button click event with event handler
	Connect(wxID_EXIT, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(wxMiniApp::OnClick) );

	// show main frame
	GetTopWindow()->Show();

	// enter the application's main loop
	return true;
}
