#include "DrawingPanel.h"
#include "wx/graphics.h"
#include "wx/dcbuffer.h"

DrawingPanel::DrawingPanel(wxFrame* parent, wxSize size) : wxPanel(parent, wxID_ANY, wxPoint(0, 0), size) {
	SetBackgroundStyle(wxBG_STYLE_PAINT);
	SetDoubleBuffered(true);

	gridSize = 15;
	cellSize = 20;

	this->Bind(wxEVT_PAINT, &DrawingPanel::OnPaint, this);
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

	//context->DrawRectangle(10, 10, 100, 100);
		
	float cellWidth = GetSize().x / (float)gridSize;
	float cellHeight = GetSize().y / (float)gridSize;
	for (int i = 0; i < gridSize; i++) {
		for (int j = 0; j < gridSize; j++) {
			context->DrawRectangle(cellWidth * i, cellHeight * j, cellWidth, cellHeight);
		}
	}


}

