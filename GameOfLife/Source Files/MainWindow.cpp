#include "MainWindow.h"
#include "play.xpm"
#include "trash.xpm"
#include "pause.xpm"

//wxBitmap playBitmap("play.xpm", wxBITMAP_TYPE_XPM);
//wxBitmap pauseBitmap("pause.xpm", wxBITMAP_TYPE_XPM);

enum {
	playToolId = 10001, //  unique ID for play tool
	clearToolId = 10002, // unique ID for clear tool
	pauseToolId = 10003, // unique ID for pause tool
	ID_OpenSettings = 10004, // unique ID for Settings Menu
	ID_Randomize = 10005,
	ID_RandomizeWithSeed = 10006,
	ID_New = 10007,
	ID_Open = 10008,
	ID_Save = 10009,
	ID_SaveAs = 10010,
	ID_Exit = 10011,
};

wxBEGIN_EVENT_TABLE(MainWindow, wxFrame)
EVT_SIZE(MainWindow::OnSizeChanged)
EVT_TOOL(clearToolId, MainWindow::OnClear)
EVT_TOOL(playToolId, MainWindow::OnPlay)
EVT_TOOL(pauseToolId, MainWindow::OnPause)
EVT_TIMER(wxID_ANY, MainWindow::OnTimer)
EVT_MENU(ID_OpenSettings, MainWindow::OnOpenSettings)
EVT_MENU(ID_Randomize, MainWindow::OnRandomize)
EVT_MENU(ID_RandomizeWithSeed, MainWindow::OnRandomizeWithSeed)
EVT_MENU(ID_New, MainWindow::OnNew)
EVT_MENU(ID_Open, MainWindow::OnOpen)
EVT_MENU(ID_Save, MainWindow::OnSave)
EVT_MENU(ID_SaveAs, MainWindow::OnSaveAs)
EVT_MENU(ID_Exit, MainWindow::OnExit)
wxEND_EVENT_TABLE()

MainWindow::MainWindow() : wxFrame(nullptr, wxID_ANY, "Game of Life", wxPoint(750, 300), wxSize(500, 500)) {
	InitializeGameBoard();
	
	// Create Menu Bar
	wxMenuBar* menuBar = new wxMenuBar();
	wxMenu* fileMenu = new wxMenu();
	fileMenu->Append(ID_New, "&New");
	fileMenu->Append(ID_Open, "&Open");
	fileMenu->Append(ID_Save, "&Save");
	fileMenu->Append(ID_SaveAs, "Save &As");
	fileMenu->Append(ID_Exit, "E&xit");

	menuBar->Append(fileMenu, "&File");
	// Create the Options menu
	wxMenu* optionsMenu = new wxMenu();
	optionsMenu->Append(ID_OpenSettings, "&Settings");
	optionsMenu->Append(ID_Randomize, "&Randomize");
	optionsMenu->Append(ID_RandomizeWithSeed, "Randomize with &Seed");
	// Add the Options menu to the menu bar
	menuBar->Append(optionsMenu, "&Options");
	
	// Set the menu bar for the frame
	SetMenuBar(menuBar);

	
	gameTimer = new wxTimer(this, wxID_ANY); // Initialize the timer
	//gameTimer->SetTimerInterval(&settings);
	int gridSize = settings.gridSize;
	

	_drawingPanel = new DrawingPanel(this, wxDefaultSize, gridSize, gameBoard);
	_drawingPanel->SetSettings(&settings);
	_drawingPanel->SetGridSize(settings.gridSize);
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

void MainWindow::OnNew(wxCommandEvent& event) {
	
	ReadCellsFile("Default.cells");
	currentFilePath.Clear();
	gameBoard.clear();
}

void MainWindow::OnOpen(wxCommandEvent& event) {
	wxFileDialog openFileDialog(this, _("Open .cells file"), "", "",
		".cells files (*.cells)|*.cells", wxFD_OPEN | wxFD_FILE_MUST_EXIST);
	if (openFileDialog.ShowModal() == wxID_CANCEL) return; // User cancelled

	ReadCellsFile(openFileDialog.GetPath());
	wxString FilePath(openFileDialog.GetPath());
	currentFilePath = FilePath;
}

void MainWindow::OnSave(wxCommandEvent& event) {
	if (currentFilePath.IsEmpty()) {
		OnSaveAs(event);
	}
	else {
		SaveToFile(currentFilePath);
	}
}

void MainWindow::OnSaveAs(wxCommandEvent& event) {
	wxFileDialog saveFileDialog(this, _("Save .cells file"), "", "", ".cells files (*.cells)|*.cells", wxFD_SAVE | wxFD_OVERWRITE_PROMPT);
	if (saveFileDialog.ShowModal() == wxID_CANCEL) {
		return;
	}

	currentFilePath = saveFileDialog.GetPath();

	SaveToFile(currentFilePath);
}

void MainWindow::OnExit(wxCommandEvent& event) {
	Close(true); // Close the application
}

void MainWindow::ReadCellsFile(const wxString& filePath) {
	wxTextFile file(filePath);
	if (!file.Open()) return; // Handle file open error

	wxString fileContent;
	wxString line;
	for (line = file.GetFirstLine(); !file.Eof(); line = file.GetNextLine()) {
		fileContent += line + "\n";
	}

	wxString delimiter = "##Settings##";
	int delimiterPos = fileContent.find(delimiter);
	if (delimiterPos != wxNOT_FOUND) {
		wxString settingsData = fileContent.Mid(delimiterPos + delimiter.length());
		settings.Deserialize(settingsData);

		fileContent = fileContent.Left(delimiterPos);
	}


	gameBoard.clear();
	wxStringTokenizer tokenizer(fileContent, "\n");
	while (tokenizer.HasMoreTokens()) {
		line = tokenizer.GetNextToken();
		if (line.StartsWith("!")) continue; // Ignore comment lines

		std::vector<bool> row;
		for (auto ch : line) {
			row.push_back(ch == '*'); // '*' for alive, '.' for dead
		}
		gameBoard.push_back(row);
	}

	UpdateGameBoardSize(gameBoard[0].size()); // Adjust grid size
	_drawingPanel->Refresh();// Update the UI or game state as needed
}

void MainWindow::SaveToFile(const wxString& filePath) {
	// Implement the logic to save your game state to the file
   // This will depend on how your game state is stored and structured
	wxTextFile file(filePath);
	if (!file.Exists()) {
		file.Create();
	}
	else {
		file.Open();
		file.Clear();
	}

	// Example: Write each row of the game board to the file
	for (const auto& row : gameBoard) {
		wxString line;
		for (bool cell : row) {
			line += cell ? '*' : '.';
		}
		file.AddLine(line);
	}

	file.AddLine("##Settings##");
	file.AddLine(settings.Serialize());
	file.Write();
	file.Close();
}

void MainWindow::ReSetPanelSettings(GameSettings* settings) {
	if (_drawingPanel) {
		_drawingPanel->SetSettings(settings);
	}
}

void MainWindow::UpdateGameBoardSize(int gridSize) {
	if (isGameRunning) {
		wxCommandEvent event(wxEVT_TOOL, pauseToolId);
		wxPostEvent(this, event);
	}

	gameBoard.resize(gridSize);
	for (auto& row : gameBoard) {
		row.resize(gridSize, false);
	}

	_drawingPanel->SetGridSize(gridSize);
	_drawingPanel->Refresh();
}

void MainWindow::OnRandomize(wxCommandEvent& event) {
	RandomizeGrid(time(NULL));
}

void MainWindow::OnRandomizeWithSeed(wxCommandEvent& event) {
	long seed = wxGetNumberFromUser("Enter seed:", "Seed:", "Randomize with Seed", 0, 0, LONG_MAX, this);
	if (seed != -1) { // -1 is returned if the user cancels the dialog
		RandomizeGrid(seed);
	}
}

void MainWindow::OnOpenSettings(wxCommandEvent& event) {
	// Assume settingsDialog is a class that inherits from wxDialog and has a constructor that accepts a GameSettings pointer
	SettingsDialog settingsDialog(this, wxID_ANY, "Settings", &settings);
	if (settingsDialog.ShowModal() == wxID_OK) {
		// The user clicked OK, update your main window as needed
		InitializeGameBoard(); // Re-initialize the game board if needed
		_drawingPanel->Refresh(); // Refresh the drawing panel to reflect any changes
	}
	// No need to do anything if Cancel was clicked, as the dialog will have made no changes to settings
}

void MainWindow::OnSizeChanged(wxSizeEvent& event) {
	if (_drawingPanel) {
		_drawingPanel->SetSize(event.GetSize());
		_drawingPanel->Refresh();
	}
	//this->Layout();
	event.Skip();
}

void MainWindow::InitializeGameBoard() {
	gameBoard.resize(settings.gridSize, std::vector<bool>(settings.gridSize, false)); // Resize with default value of false
	neighborCounts.resize(settings.gridSize, std::vector<int>(settings.gridSize, 0));
}

void MainWindow::UpdateStatusBar() {
	wxString statusText = wxString::Format("Generation: %d - Living Cells: %d", generation, livingCells);
	statusBar->SetStatusText(statusText);
}

void MainWindow::OnPlay(wxCommandEvent& event) {
	gameTimer->Start(settings.timerInterval); // Start the timer with the set interval
	isGameRunning = true;
	wxToolBarToolBase *playTool = toolBar->FindById(playToolId);
	int pos = toolBar->GetToolPos(playToolId);
	toolBar->DeleteTool(playToolId);
	toolBar->InsertTool(pos, pauseToolId,"Pause", pauseBitmap);
	toolBar->Realize();	
	this->Layout(); // very important for post play status bar to stick around
}

void MainWindow::OnPause(wxCommandEvent& event) {
	gameTimer->Stop(); // Stop the timer
	isGameRunning = false;
	wxToolBarToolBase *pauseTool = toolBar->FindById(pauseToolId);
	int pos = toolBar->GetToolPos(pauseToolId);
	toolBar->DeleteTool(pauseToolId);
	toolBar->InsertTool(pos, playToolId, "Play", playBitmap);
	toolBar->Realize();
	this->Layout(); // very important for post pause status bar to stick around
}

void MainWindow::RandomizeGrid(int seed) {
	srand(seed);
	for (auto& row : gameBoard) {
		for (auto cell : row) {
			cell = rand() % 2; // 50% chance of being alive
			// For different probabilities, adjust the condition
			// e.g., for about 45% alive: cell = (rand() % 100) < 45;
		}
	}
	_drawingPanel->Refresh();
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
			if (neighborRow >= 0 && neighborRow < settings.gridSize &&
				neighborColumn >= 0 && neighborColumn < settings.gridSize) {
				// Increment count if the neighbor is alive
				if (gameBoard[neighborRow][neighborColumn]) {
					++count;
				}
			}
		}
	}

	return count;
}


std::vector<std::vector<int>> MainWindow::CalculateAllNeighborCounts() {
	std::vector<std::vector<int>> neighborCounts(settings.gridSize, std::vector<int>(settings.gridSize, 0));

	for (int row = 0; row < settings.gridSize; ++row) {
		for (int col = 0; col < settings.gridSize; ++col) {
			neighborCounts[row][col] = CalculateNeighborCount(row, col);
		}
	}

	return neighborCounts;
}

void MainWindow::AdvanceToNextGeneration() {
	std::vector<std::vector<bool>> sandbox(settings.gridSize, std::vector<bool>(settings.gridSize, false));	
	int newLivingCells = 0;

	// Iterate through the entire board
	for (int row = 0; row < settings.gridSize; ++row) {
		for (int column = 0; column < settings.gridSize; ++column) {
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
	auto neighborCounts = CalculateAllNeighborCounts();
	// Update the living cells count and generation
	livingCells = newLivingCells;
	++generation;

	// Update the status bar and refresh the drawing panel
	if (_drawingPanel) {
		_drawingPanel->UpdateNeighborCounts(neighborCounts);
	}
	_drawingPanel->Refresh();
	UpdateStatusBar();
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
 