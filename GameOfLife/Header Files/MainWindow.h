#pragma once
#include "wx/wx.h"
#include "DrawingPanel.h"
#include <vector>
#include "GameSettings.h"
#include "SettingsDialog.h"

class MainWindow : public wxFrame
{
private:
	DrawingPanel* _drawingPanel = nullptr;
	wxToolBar* toolBar = nullptr;
	wxBoxSizer* _sizer = nullptr;
	std::vector<std::vector<bool>> gameBoard;
	
	int generation = 0; // Add this to track the generation count
	int livingCells = 0; // Add this to track the living cells count
	wxStatusBar* statusBar = nullptr; // Add this to reference the status bar
	wxTimer* gameTimer; // Pointer to the wxTimer	
	void UpdateStatusBar(); // Method to update the status bar text
	wxBitmap playBitmap;
	wxBitmap pauseBitmap;
	bool isGameRunning = false;

public:
	MainWindow();
	~MainWindow();	
	GameSettings settings;
	void OnSizeChanged(wxSizeEvent& event);
	void InitializeGameBoard();
	void OnPlay(wxCommandEvent& event);
	void OnPause(wxCommandEvent& event);
	int CalculateNeighborCount(int row, int column);
	void AdvanceToNextGeneration();
	void OnClear(wxCommandEvent& event);
	void OnTimer(wxTimerEvent& event);
	void SetTimerInterval(GameSettings* timerInterval);//GameSettings timerInterval;  // Interval for the timer in milliseconds	
	void OnOpenSettings(wxCommandEvent& event);
	void UpdateGameBoardSize(int gridSize);
	wxDECLARE_EVENT_TABLE();
};

