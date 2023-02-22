#pragma once
#include <wx/wx.h>
#include <wx/spinctrl.h>

class MainFrame : public wxFrame
{
public:
	MainFrame(const wxString& title);

private:
	wxBoxSizer* sizer;
	wxStaticText* staticText1;
	wxStaticText* staticText2;
	wxStaticText* staticText3;
	wxTextCtrl* textDescript;
	wxSpinCtrl* spinPrice;
	wxButton* btn;
	wxPanel* panel_top;
	wxPanel* panel_bottom;
	wxPanel* panel_bottom_right;
	void OnButtonClicked(wxCommandEvent& evt);
};

