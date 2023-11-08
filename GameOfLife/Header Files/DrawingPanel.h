#pragma once
#include "wx/wx.h"
#include <vector>
#include "GameSettings.h"

class DrawingPanel : public wxPanel
{
private:
    int gridSize;
    std::vector<std::vector<bool>>& gameBoard; // Reference to the game board from MainWindow
    void OnPaint(wxPaintEvent& event);
    void OnSizeChanged(wxSizeEvent& event);
    void OnMouseUp(wxMouseEvent& event); // Mouse event handler method
    GameSettings* settings;

public:
    DrawingPanel(wxFrame* MainWindow, wxSize size, int gridSize, std::vector<std::vector<bool>>& gameBoard);
    ~DrawingPanel();
    void SetGridSize(int size);
    void SetSettings(GameSettings* settings) {
        this->settings = settings;
    }
    wxDECLARE_EVENT_TABLE();
};

