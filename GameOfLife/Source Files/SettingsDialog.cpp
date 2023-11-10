#include "SettingsDialog.h"
#include "MainWindow.h"

wxBEGIN_EVENT_TABLE(SettingsDialog, wxDialog)
EVT_BUTTON(wxID_OK, SettingsDialog::OnOk)
EVT_BUTTON(wxID_CANCEL, SettingsDialog::OnCancel)
wxEND_EVENT_TABLE()

SettingsDialog::SettingsDialog(wxWindow* parent, wxWindowID id, const wxString& title, GameSettings* settings)
    : wxDialog(parent, id, title), settings(settings) {

    wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);

    // Create child sizers and controls here...
    // Example for grid size:
    wxBoxSizer* gridSizeSizer = new wxBoxSizer(wxHORIZONTAL);
    gridSizeSizer->Add(new wxStaticText(this, wxID_ANY, "Grid Size:"));
    gridSizeCtrl = new wxSpinCtrl(this, ID_GridSize);
    gridSizeSizer->Add(gridSizeCtrl);
    mainSizer->Add(gridSizeSizer);

    // Similar for other settings...

    // Set control values from settings
    if (settings) {
        gridSizeCtrl->SetValue(settings->gridSize);
        // Similar for other settings...
    }

    // OK and Cancel buttons
    wxSizer* buttonSizer = CreateButtonSizer(wxOK | wxCANCEL);
    mainSizer->Add(buttonSizer, 0, wxEXPAND | wxALL, 10);

    SetSizer(mainSizer);
    mainSizer->Fit(this);
    mainSizer->SetSizeHints(this);
}
SettingsDialog::~SettingsDialog() {

}

void SettingsDialog::OnOk(wxCommandEvent& event) {
    // Validate and save settings
    if (settings) {
        settings->gridSize = gridSizeCtrl->GetValue();
        // Similar for other settings...
    }
    EndModal(wxID_OK); // Ends the dialog and returns wxID_OK
}

void SettingsDialog::OnCancel(wxCommandEvent& event) {
    EndModal(wxID_CANCEL); // Ends the dialog and returns wxID_CANCEL
}
