#include "DrawingPanel.h"
#include "wx/graphics.h"
#include "wx/dcbuffer.h"
#include <MainWindow.h>

DrawingPanel::DrawingPanel(wxFrame* parent, wxSize size, int gridSize) : wxPanel(parent, wxID_ANY, wxPoint(0, 0), size), gridSize(gridSize) {
	SetBackgroundStyle(wxBG_STYLE_PAINT);
	SetDoubleBuffered(true);

	
	

	this->Bind(wxEVT_PAINT, &DrawingPanel::OnPaint, this);

	this->Bind(wxEVT_SIZE, &DrawingPanel::OnSizeChanged, this);
}
DrawingPanel::~DrawingPanel() {

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
			context->DrawRectangle(cellWidth * i, cellHeight * j, cellWidth, cellHeight);
		}
	}
}

void DrawingPanel::OnSizeChanged(wxSizeEvent& event) {
	Refresh();
	event.Skip();
}


