#include "DrawingPanel.h"
#include "wx/graphics.h"
#include "wx/dcbuffer.h"
#include <MainWindow.h>

wxBEGIN_EVENT_TABLE(DrawingPanel, wxPanel)
EVT_PAINT(DrawingPanel::OnPaint)
EVT_LEFT_UP(DrawingPanel::OnMouseUp)
wxEND_EVENT_TABLE()

DrawingPanel::DrawingPanel(wxFrame* parent, wxSize size, int gridSize, std::vector<std::vector<bool>>&gameBoard) 
	: wxPanel(parent, wxID_ANY, wxPoint(0, 0), size), gridSize(gridSize), gameBoard(gameBoard) {
	SetBackgroundStyle(wxBG_STYLE_PAINT);
	SetDoubleBuffered(true);
	
	
}
DrawingPanel::~DrawingPanel() {

}

void DrawingPanel::SetSettings(GameSettings* settings) {
	this->settings = settings;
	if (settings != nullptr) {
		this->gridSize = settings->gridSize;
		this->currentLivingColor = settings->GetLivingCellColor();
		this->currentDeadColor = settings->GetDeadCellColor();
	}
}

void DrawingPanel::OnPaint(wxPaintEvent& event) {
	wxAutoBufferedPaintDC dc(this);
	dc.Clear();

	wxGraphicsContext* context = wxGraphicsContext::Create(dc);
	if (!context) { return; }

	context->SetPen(*wxBLACK);
	context->SetBrush(*wxWHITE);

	//context->ClearRectangle(0, 0, GetSize().x, GetSize().y);
		
	float cellWidth = GetSize().x / (float)gridSize;
	float cellHeight = GetSize().y / (float)gridSize;
	for (int i = 0; i < gridSize; i++) {
		for (int j = 0; j < gridSize; j++) {
			// Set the brush depending on the cell's state
			context->SetBrush(gameBoard[j][i] ? currentLivingColor : currentDeadColor);
			context->DrawRectangle(cellWidth * i, cellHeight * j, cellWidth, cellHeight);
		}
	}
	delete context;  // Clean up the context to prevent memory leaks
}

void DrawingPanel::OnSizeChanged(wxSizeEvent& event) {
	Refresh();
	//event.Skip();
}

void DrawingPanel::SetGridSize(int size) {
	gridSize = size;
	Refresh();
}

void DrawingPanel::OnMouseUp(wxMouseEvent& event) {
	int x = event.GetX();
	int y = event.GetY();

	float cellWidth = static_cast<float>(GetSize().x) / gridSize;
	float cellHeight = static_cast<float>(GetSize().y) / gridSize;

	int column = static_cast<int>(x / cellWidth);
	int row = static_cast<int>(y / cellHeight);

	// Add boundary checking here
	if (row >= 0 && row < gridSize && column >= 0 && column < gridSize) {
		// Toggle the state of the cell within the bounds of the vector
		gameBoard[row][column] = !gameBoard[row][column];
		Refresh(); // Will trigger the OnPaint event to redraw the panel		
	}
}



