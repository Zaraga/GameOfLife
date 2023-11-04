#include "MainWindow.h"



MainWindow::MainWindow() : wxFrame(nullptr, wxID_ANY, "Game of Life", wxPoint(750, 300), wxSize(500, 500)) {
	_drawingPanel = new DrawingPanel(this, wxSize(100, 100), gridSize);
	Show(true);

	_sizer = new wxBoxSizer(wxVERTICAL);
	_sizer->Add(_drawingPanel, 1, wxEXPAND | wxALL);

	void InitializeGameBoard();

	Bind(wxEVT_SIZE, &MainWindow::OnSizeChanged, this);

	SetSizer(_sizer);
}

MainWindow::~MainWindow() {

}

void MainWindow::OnSizeChanged(wxSizeEvent& event) {
	_drawingPanel->SetSize(event.GetSize());
	_drawingPanel->Refresh();
	event.Skip();
}

void MainWindow::InitializeGameBoard() {
	gameBoard.resize(gridSize);
	for (int i = 0; i < gridSize; i++) {
		gameBoard[i].resize(gridSize);
	}
}