#include "MainWindow.h"
#include "play.xpm"
#include "trash.xpm"
#include "pause.xpm"

//wxBitmap playBitmap("play.xpm", wxBITMAP_TYPE_XPM);
//wxBitmap pauseBitmap("pause.xpm", wxBITMAP_TYPE_XPM);

enum {
	playToolId = 10001, //  unique ID for play tool
	clearToolId = 10002, // unique ID for clear tool
	pauseToolId = 10003 // unique ID for pause tool
};

wxBEGIN_EVENT_TABLE(MainWindow, wxFrame)
EVT_SIZE(MainWindow::OnSizeChanged)
EVT_TOOL(clearToolId, MainWindow::OnClear)
EVT_TOOL(playToolId, MainWindow::OnPlay)
EVT_TOOL(pauseToolId, MainWindow::OnPause)
EVT_TIMER(wxID_ANY, MainWindow::OnTimer)
wxEND_EVENT_TABLE()

MainWindow::MainWindow() : wxFrame(nullptr, wxID_ANY, "Game of Life", wxPoint(750, 300), wxSize(500, 500)) {
	InitializeGameBoard();

	gameTimer = new wxTimer(this, wxID_ANY); // Initialize the timer
	timerInterval = 50; // Set the timer interval to 50ms

	_drawingPanel = new DrawingPanel(this, wxDefaultSize, gridSize, gameBoard);
	_drawingPanel->SetGridSize(gridSize);
	//Show(true);
	
	_sizer = new wxBoxSizer(wxVERTICAL);
	_sizer->Add(_drawingPanel, 1, wxEXPAND | wxALL);	
	//_sizer->Add(statusBar, 0, wxEXPAND);
	SetSizer(_sizer);

	toolBar = CreateToolBar();
	
	wxBitmap clearIcon(trash_xpm);
	playBitmap = wxBitmap(play_xpm);
	pauseBitmap = wxBitmap(pause_xpm);
	toolBar->AddTool(playToolId, "Play", playBitmap);
	toolBar->AddTool(clearToolId, "Clear", clearIcon);
	toolBar->Realize();

	statusBar = CreateStatusBar(); // Create the status bar
	UpdateStatusBar();			   // Initialize the status bar text

	this->Layout(); // Ensure the layout is refreshed
}

MainWindow::~MainWindow() {
	if (gameTimer->IsRunning())
		gameTimer->Stop();

	delete gameTimer; // Clean up the timer
}

void MainWindow::OnSizeChanged(wxSizeEvent& event) {
	_drawingPanel->SetSize(event.GetSize());
	_drawingPanel->Refresh();
	//this->Layout();
	event.Skip();
}

void MainWindow::InitializeGameBoard() {
	gameBoard.resize(gridSize, std::vector<bool>(gridSize, false)); // Resize with default value of false
}

void MainWindow::UpdateStatusBar() {
	wxString statusText = wxString::Format("Generation: %d - Living Cells: %d", generation, livingCells);
	statusBar->SetStatusText(statusText);
}

void MainWindow::OnPlay(wxCommandEvent& event) {
	gameTimer->Start(timerInterval); // Start the timer with the set interval
	wxToolBarToolBase *playTool = toolBar->FindById(playToolId);
	int pos = toolBar->GetToolPos(playToolId);
	toolBar->DeleteTool(playToolId);
	toolBar->InsertTool(pos, pauseToolId,"Pause", pauseBitmap);
	toolBar->Realize();
}

void MainWindow::OnPause(wxCommandEvent& event) {
	gameTimer->Stop(); // Stop the timer
	wxToolBarToolBase *pauseTool = toolBar->FindById(pauseToolId);
	int pos = toolBar->GetToolPos(pauseToolId);
	toolBar->DeleteTool(pauseToolId);
	toolBar->InsertTool(pos, playToolId, "Play", playBitmap);
	toolBar->Realize();
}

int MainWindow::CalculateNeighborCount(int row, int column) {
	int count = 0;

	// Check the eight possible neighbors
	for (int i = -1; i <= 1; ++i) {
		for (int j = -1; j <= 1; ++j) {
			// Skip the cell itself
			if (i == 0 && j == 0) continue;

			int neighborRow = row + i;
			int neighborColumn = column + j;

			// Check if the neighbor indices are within the bounds of the grid
			if (neighborRow >= 0 && neighborRow < gridSize &&
				neighborColumn >= 0 && neighborColumn < gridSize) {
				// Increment count if the neighbor is alive
				if (gameBoard[neighborRow][neighborColumn]) {
					++count;
				}
			}
		}
	}

	return count;
}

void MainWindow::AdvanceToNextGeneration() {
	std::vector<std::vector<bool>> sandbox(gridSize, std::vector<bool>(gridSize, false));
	int newLivingCells = 0;

	// Iterate through the entire board
	for (int row = 0; row < gridSize; ++row) {
		for (int column = 0; column < gridSize; ++column) {
			int liveNeighbors = CalculateNeighborCount(row, column);
			bool cellCurrentlyAlive = gameBoard[row][column];

			// Apply the Game of Life rules
			if (cellCurrentlyAlive && (liveNeighbors < 2 || liveNeighbors > 3)) {
				// Living cell dies
				sandbox[row][column] = false;
			}
			else if (!cellCurrentlyAlive && liveNeighbors == 3) {
				// Dead cell becomes alive
				sandbox[row][column] = true;
				++newLivingCells;
			}
			else if (cellCurrentlyAlive) {
				// Living cell stays alive
				sandbox[row][column] = true;
				++newLivingCells;
			}
			// If the cell is dead and doesn't have three living neighbors, it remains dead (false),
			// which is the default value when the sandbox was initialized, so no else clause is required.
		}
	}

	// Update the game board with the new generation
	gameBoard.swap(sandbox);

	// Update the living cells count and generation
	livingCells = newLivingCells;
	++generation;

	// Update the status bar and refresh the drawing panel
	UpdateStatusBar();
	_drawingPanel->Refresh();
}

void MainWindow::OnClear(wxCommandEvent& event) {
	// Reset the game board
	for (auto& row : gameBoard) {
		std::fill(row.begin(), row.end(), false);
	}

	// Reset the living cell count and generation count
	livingCells = 0;
	generation = 0;

	// Update the status bar text
	UpdateStatusBar();

	// Refresh the drawing panel
	_drawingPanel->Refresh();
}

void MainWindow::OnTimer(wxTimerEvent& event) {
	AdvanceToNextGeneration(); // Call your method to advance the game
}
 