#include "MainWindow.h"
#include "DrawingPanel.h"



MainWindow::MainWindow() : wxFrame(nullptr, wxID_ANY, "Game of Life", wxPoint(750, 300), wxSize(500, 500)) {
	DrawingPanel* drawingPanel = new DrawingPanel(this);
	Show(true);
}

MainWindow::~MainWindow() {

}