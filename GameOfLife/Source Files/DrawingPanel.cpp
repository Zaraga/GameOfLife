#include "DrawingPanel.h"
#include "wx/graphics.h"
#include "wx/dcbuffer.h"

DrawingPanel::DrawingPanel(wxFrame* parent) : wxPanel(parent, wxID_ANY, wxPoint(0, 0), wxSize(200, 200)) {

}

DrawingPanel::~DrawingPanel() {

}
