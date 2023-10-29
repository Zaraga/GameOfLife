#pragma once
#include "wx/wx.h"
class DrawingPanel : public wxPanel
{
private:
	int gridSize;
	int cellSize;
public:
	DrawingPanel(wxFrame* Mainwindow);
	~DrawingPanel();
	
	void OnPaint(wxPaintEvent& event);
};

