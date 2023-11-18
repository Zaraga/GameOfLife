#include "SettingsDialog.h"
#include "MainWindow.h"
#include <wx/textfile.h>

wxBEGIN_EVENT_TABLE(SettingsDialog, wxDialog)
EVT_BUTTON(wxID_OK, SettingsDialog::OnOk)
EVT_BUTTON(wxID_CANCEL, SettingsDialog::OnCancel)
wxEND_EVENT_TABLE()

SettingsDialog::SettingsDialog(MainWindow* mainWin, wxWindowID id, const wxString& title, GameSettings settings)
    : wxDialog(mainWin, id, title), mainWin(mainWin), settings(settings) {

    wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);

    // Create child sizers and controls here...
    // grid size:
    wxBoxSizer* gridSizeSizer = new wxBoxSizer(wxHORIZONTAL);
    gridSizeSizer->Add(new wxStaticText(this, wxID_ANY, "Grid Size:"));
    gridSizeCtrl = new wxSpinCtrl(this, ID_GridSize);
    gridSizeSizer->Add(gridSizeCtrl);
    mainSizer->Add(gridSizeSizer);

    // Timer interval control
    wxBoxSizer* timerIntervalSizer = new wxBoxSizer(wxHORIZONTAL);
    timerIntervalSizer->Add(new wxStaticText(this, wxID_ANY, "Timer Interval:"));
    timerIntervalCtrl = new wxSpinCtrl(this, ID_TimerInterval);
    timerIntervalSizer->Add(timerIntervalCtrl);
    mainSizer->Add(timerIntervalSizer);

    // Living cell color picker
    wxBoxSizer* livingCellColourSizer = new wxBoxSizer(wxHORIZONTAL);
    livingCellColourSizer->Add(new wxStaticText(this, wxID_ANY, "Living Cell Color:"));
    livingCellColorPicker = new wxColourPickerCtrl(this, ID_LivingCellColor);
    livingCellColourSizer->Add(livingCellColorPicker);
    mainSizer->Add(livingCellColourSizer);

    // Dead cell color picker
    wxBoxSizer* deadCellColourSizer = new wxBoxSizer(wxHORIZONTAL);
    deadCellColourSizer->Add(new wxStaticText(this, wxID_ANY, "Dead Cell Color:"));
    deadCellColorPicker = new wxColourPickerCtrl(this, ID_DeadCellColor);
    deadCellColourSizer->Add(deadCellColorPicker);
    mainSizer->Add(deadCellColourSizer);

    // Show Neighbor Count CheckBox
    showNeighborCountCheckBox = new wxCheckBox(this, wxID_ANY, "Show Neighbor Count");
    mainSizer->Add(showNeighborCountCheckBox);

    // Set control values from settings
    if (&settings) {
        gridSizeCtrl->SetValue(settings.gridSize);
        timerIntervalCtrl->SetValue(settings.timerInterval);
        livingCellColorPicker->SetColour(settings.GetLivingCellColor());
        deadCellColorPicker->SetColour(settings.GetDeadCellColor());
        showNeighborCountCheckBox->SetValue(settings.showNeighborCount);
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
    if (&settings) {
        settings.gridSize = gridSizeCtrl->GetValue();
        int newGridSize = gridSizeCtrl->GetValue();
        
        
        settings.timerInterval = timerIntervalCtrl->GetValue();
        
        wxColor livingColor = livingCellColorPicker->GetColour();
        settings.SetLivingCellColor(livingColor);

        wxColor deadColor = deadCellColorPicker->GetColour();
        settings.SetDeadCellColor(deadColor); 

        settings.showNeighborCount = showNeighborCountCheckBox->IsChecked();

        mainWin->ReSetPanelSettings(&settings);
        mainWin->UpdateGameBoardSize(newGridSize);
    }
    mainWin->OnSave(event);
    //settings->Save();
    EndModal(wxID_OK); // Ends the dialog and returns wxID_OK
}

void SettingsDialog::OnCancel(wxCommandEvent& event) {
    //settings->Load();
    EndModal(wxID_CANCEL); // Ends the dialog and returns wxID_CANCEL
}
