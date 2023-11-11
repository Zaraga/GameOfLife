#pragma once
#include "wx/wx.h"
#include <vector>
#include "GameSettings.h"
//#include "MainWindow.h"


class DrawingPanel : public wxPanel
{
private:
    
    std::vector<std::vector<bool>>& gameBoard; // Reference to the game board from MainWindow
    void OnPaint(wxPaintEvent& event);
    void OnSizeChanged(wxSizeEvent& event);
    void OnMouseUp(wxMouseEvent& event); // Mouse event handler method
    
    int gridSize;
    
    

public:
    DrawingPanel(wxFrame* MainWindow, wxSize size, int gridSize, std::vector<std::vector<bool>>& gameBoard);
    ~DrawingPanel();
    GameSettings* settings;
    void SetGridSize(int size);
    void SetSettings(GameSettings* settings);
    //int gridSize = settings.gridSize;
    wxColor currentLivingColor;
    wxColor currentDeadColor;
    bool isNeighborCount;
    void UpdateNeighborCounts(std::vector<std::vector<int>>& counts);
    std::vector<std::vector<int>> neighborCounts;
    wxDECLARE_EVENT_TABLE();
};

