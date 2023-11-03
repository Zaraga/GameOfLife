#pragma once
#include "wx/wx.h"
class DrawingPanel : public wxPanel
{
private:
	int gridSize;
	int cellSize;
	void OnPaint(wxPaintEvent& event);
public:
	DrawingPanel(wxFrame* Mainwindow, wxSize size);
	~DrawingPanel();
	
	
};

