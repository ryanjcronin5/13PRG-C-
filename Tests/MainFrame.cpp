#include "MainFrame.h"
#include <wx/wx.h>
#include <wx/stattext.h>
#include <wx/arrstr.h>
#include <wx/spinctrl.h>
#include <iostream>
#include <fstream>

using namespace std;

const long ID_STATICTEXT1 = wxNewId();
wxInt16 y = 10;
wxArrayString descript = {};
wxArrayInt price = {};

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

	staticText1 = new wxStaticText(panel_top, ID_STATICTEXT1, "Enter Description:", wxPoint(10, 7), wxDefaultSize);
	textDescript = new wxTextCtrl(panel_top, wxID_ANY, "", wxPoint(105, 5), wxSize(180, -1));
	staticText3 = new wxStaticText(panel_top, wxID_ANY, "Enter Price:", wxPoint(10, 30), wxDefaultSize);
	spinPrice = new wxSpinCtrl(panel_top, wxID_ANY, "", wxPoint(75, 27), wxSize(210, -1));

	btn = new wxButton(panel_bottom_right, wxID_ANY, "Submit", wxPoint(0, 8), wxDefaultSize);
	this->SetSizerAndFit(sizer);
	btn->Bind(wxEVT_BUTTON, &MainFrame::OnButtonClicked, this);

	CreateStatusBar();
}

void MainFrame::OnButtonClicked(wxCommandEvent& evt) {
	staticText2 = new wxStaticText(panel_bottom, wxID_ANY, "", wxPoint(10, y), wxDefaultSize);

	wxString str = textDescript->GetValue() + " $" << spinPrice->GetValue();
	descript.Add(textDescript->GetValue());
	price.Add(spinPrice->GetValue());

	staticText2->SetLabelText(str);

	wxLogStatus("// Submitted //");

	y += 15;
	textDescript->SetValue("");
	spinPrice->SetValue("");

	// write to file
	std::ofstream outfile("output.txt");

	for (int i = 0; i < descript.GetCount(); i++) {
		outfile << descript[i] << " $" << price[i] << endl;
	}

	outfile.close();
}