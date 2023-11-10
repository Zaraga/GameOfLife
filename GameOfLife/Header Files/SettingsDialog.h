
#pragma once
#include "wx/wx.h"
#include "wx/spinctrl.h"
#include "wx/clrpicker.h"
#include "GameSettings.h"

class SettingsDialog : public wxDialog {
public:
    SettingsDialog(wxWindow* MainWindow, wxWindowID id, const wxString& title, GameSettings* settings);
    ~SettingsDialog();
    // Event handlers for OK and Cancel buttons
    void OnOk(wxCommandEvent& event);
    void OnCancel(wxCommandEvent& event);

private:
    // Pointers to controls for settings
    wxSpinCtrl* gridSizeCtrl;
    wxSpinCtrl* timerIntervalCtrl;
    wxColourPickerCtrl* livingCellColourPicker;
    wxColourPickerCtrl* deadCellColourPicker;

    // Pointer to the settings object
    GameSettings* settings;

    // Declare the event table
    wxDECLARE_EVENT_TABLE();
};

// IDs for the controls
enum {
    ID_GridSize = 11000,
    ID_TimerInterval,
    ID_LivingCellColour,
    ID_DeadCellColour
};
