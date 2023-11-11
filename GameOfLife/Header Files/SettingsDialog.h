
#pragma once
#include "wx/wx.h"
#include "wx/spinctrl.h"
#include "wx/clrpicker.h"
#include "GameSettings.h"

class MainWindow;
class DrawingPanel;

class SettingsDialog : public wxDialog {
    MainWindow* mainWin;
    DrawingPanel* drawPan;
public:
    SettingsDialog(MainWindow* mainWin, wxWindowID id, const wxString& title, GameSettings* settings);
    ~SettingsDialog();
    // Event handlers for OK and Cancel buttons
    void OnOk(wxCommandEvent& event);
    void OnCancel(wxCommandEvent& event);

private:
    // Pointers to controls for settings
    wxSpinCtrl* gridSizeCtrl;
    wxSpinCtrl* timerIntervalCtrl;
    wxColourPickerCtrl* livingCellColorPicker;
    wxColourPickerCtrl* deadCellColorPicker;

    // Pointer to the settings object
    GameSettings* settings;

    // Declare the event table
    wxDECLARE_EVENT_TABLE();
};

// IDs for the controls
enum {
    ID_GridSize = 11000,
    ID_TimerInterval = 11100,
    ID_LivingCellColor = 12000,
    ID_DeadCellColor = 12001
};
