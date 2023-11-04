#pragma once
#include "wx/wx.h"
#include "DrawingPanel.h"
#include <vector>

class MainWindow : public wxFrame
{
private:
	DrawingPanel* _drawingPanel = nullptr;
	wxToolBar* toolBar = nullptr;
	wxBoxSizer* _sizer = nullptr;
	std::vector<std::vector<bool>> gameBoard;
	int gridSize = 15;

public:
	MainWindow();
	~MainWindow();
	void OnSizeChanged(wxSizeEvent& event);
	void InitializeGameBoard();
	

};

