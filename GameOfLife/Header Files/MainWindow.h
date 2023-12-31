#pragma once
#include "wx/wx.h"
#include "DrawingPanel.h"
#include <vector>
#include "GameSettings.h"
#include "SettingsDialog.h"
#include <cstdlib>
#include <ctime>
#include <wx/numdlg.h>
#include <wx/textfile.h>


class MainWindow : public wxFrame
{
private:
	wxString currentFilePath;
	wxToolBar* toolBar = nullptr;
	wxBoxSizer* _sizer = nullptr;
	std::vector<std::vector<bool>> gameBoard;
	std::vector<std::vector<int>> neighborCounts;
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
	DrawingPanel* _drawingPanel = nullptr;
	SettingsDialog* _settingsDialog = nullptr;
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
	void ReSetPanelSettings(GameSettings& settings);
	std::vector<std::vector<int>> CalculateAllNeighborCounts();
	void OnRandomize(wxCommandEvent& event);
	void OnRandomizeWithSeed(wxCommandEvent& event);
	void OnNew(wxCommandEvent& event);
	void OnOpen(wxCommandEvent& event);
	void OnSave(wxCommandEvent& event);
	void OnSaveAs(wxCommandEvent& event);
	void OnExit(wxCommandEvent& event);
	void RandomizeGrid(int seed);
	void ReadCellsFile(const wxString& filePath);
	void SaveToFile(const wxString& filePath);	
	wxDECLARE_EVENT_TABLE();
};

