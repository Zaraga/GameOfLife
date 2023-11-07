#pragma once
#include "wx/wx.h"
#include <vector>

class DrawingPanel : public wxPanel
{
private:
    int gridSize;
    std::vector<std::vector<bool>>& gameBoard; // Reference to the game board from MainWindow
    void OnPaint(wxPaintEvent& event);
    void OnSizeChanged(wxSizeEvent& event);
    void OnMouseUp(wxMouseEvent& event); // Mouse event handler method

public:
    DrawingPanel(wxFrame* MainWindow, wxSize size, int gridSize, std::vector<std::vector<bool>>& gameBoard);
    ~DrawingPanel();
    void SetGridSize(int size);

    wxDECLARE_EVENT_TABLE();
};

