#include "MainFrame.h"
#include <wx/wx.h>
#include <wx/stattext.h>
#include <wx/arrstr.h>
#include <iostream>
#include <fstream>

using namespace std;

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

	choices.Add("False");
	choices.Add("True");
	radioBox = new wxRadioBox(panel_top, wxID_ANY, "Was the car speeding", wxPoint(100, 5), wxDefaultSize, choices);

	btn = new wxButton(panel_bottom_right, wxID_ANY, "Submit", wxPoint(0, 8), wxDefaultSize);
	this->SetSizerAndFit(sizer);
	btn->Bind(wxEVT_BUTTON, &MainFrame::OnButtonClicked, this);

	CreateStatusBar();
}

void MainFrame::OnButtonClicked(wxCommandEvent& evt) {
	wxInt16 y = 10;
	staticText2 = new wxStaticText(panel_bottom, wxID_ANY, "", wxPoint(10, y), wxDefaultSize);

	// Opens file
	ifstream infile("output.txt");

	if (textDescript->GetValue() == "999")
	{
		int num_speeding = 0;
		int num_not_speeding = 0;
		string line;

		// Read through the file and count the number of speeding and not speeding cars
		while (getline(infile, line))
		{
			wxArrayString parts = wxSplit(line, ',');
			if (parts.GetCount() >= 2 && parts[1].Trim() == "1")
				num_speeding++;
			else
				num_not_speeding++;
		}

		// Calculate percentages and format the output string
		int total_cars = num_speeding + num_not_speeding;
		int percent_speeding = (total_cars > 0) ? (num_speeding * 100 / total_cars) : 0;
		int percent_not_speeding = 100 - percent_speeding;
		wxString output_str = wxString::Format("Speeding %d%%  Not Speeding %d%%", percent_speeding, percent_not_speeding);
		staticText2->SetLabelText(output_str);

		// Log status message
		wxLogStatus("// Speeding percentage calculated //");
	}
	else {
		wxString str = textDescript->GetValue() + ", " + wxString::Format("%d", radioBox->GetSelection());
		staticText2->SetLabelText(str);
		y += 15;

		// Add new data to arrays
		age.Add(textDescript->GetValue());
		speeding.Add(radioBox->GetSelection());

		// Write to file
		ofstream outfile("output.txt");
		for (int i = 0; i < static_cast<int>(age.GetCount()); i++) {
			outfile << age[i] << ", " << speeding[i] << endl;
		}
		outfile.close();

		// Log status message
		wxLogStatus("// File written successfully //");
		textDescript->SetValue("");
		radioBox->SetSelection(0);
	}
}