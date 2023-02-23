#include "MainFrame.h"
#include <wx/wx.h>
#include <wx/stattext.h>
#include <wx/arrstr.h>
#include <iostream>
#include <fstream>

using namespace std;

wxInt16 y = 10;
wxArrayString age = {};
wxArrayInt speeding = {};
wxArrayString choices = {};

MainFrame::MainFrame(const wxString& title) : wxFrame(nullptr, wxID_ANY, title) {
	panel_top = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxSize(200, 50));
	panel_bottom = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxSize(200, 50));
	panel_bottom_right = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxSize(-1, 50));
	sizer = new wxBoxSizer(wxVERTICAL);
	sizer->Add(panel_top, 1, wxEXPAND | wxLEFT | wxTOP | wxRIGHT, 10);
	wxSizer* sizer_bottom = new wxBoxSizer(wxHORIZONTAL);
	sizer_bottom->Add(panel_bottom, 3, wxEXPAND | wxRIGHT, 10);
	sizer_bottom->Add(panel_bottom_right, 1, wxEXPAND, 0);
	sizer->Add(sizer_bottom, 1, wxEXPAND | wxALL, 10);

	staticText1 = new wxStaticText(panel_top, wxID_ANY, "Enter Age:", wxPoint(10, 7), wxDefaultSize);
	textDescript = new wxTextCtrl(panel_top, wxID_ANY, "", wxPoint(7, 27), wxSize(80, -1));

	choices.Add("True");
	choices.Add("False");
	radioBox = new wxRadioBox(panel_top, wxID_ANY, "Was the car speeding", wxPoint(100, 5), wxDefaultSize, choices);

	btn = new wxButton(panel_bottom_right, wxID_ANY, "Submit", wxPoint(0, 8), wxDefaultSize);
	this->SetSizerAndFit(sizer);
	btn->Bind(wxEVT_BUTTON, &MainFrame::OnButtonClicked, this);

	CreateStatusBar();
}

void MainFrame::OnButtonClicked(wxCommandEvent& evt) {
	staticText2 = new wxStaticText(panel_bottom, wxID_ANY, "", wxPoint(10, y), wxDefaultSize);

	// Opens file
	ofstream outfile("output.txt");

	if (textDescript->GetValue() == "999")
	{
	}
	else {
		wxString str = textDescript->GetValue() + ", " << radioBox->GetSelection();
		staticText2->SetLabelText(str);
		wxLogStatus("// Submitted //");
		y += 15;
		textDescript->SetValue("");
		radioBox->SetSelection(0);

		// write to file
		for (int i = 0; i < age.GetCount(); i++) {
			outfile << age[i] << ", " << speeding[i] << endl;
		}
	}
	outfile.close();
}