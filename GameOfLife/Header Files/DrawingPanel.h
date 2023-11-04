#pragma once
#include "wx/wx.h"
class DrawingPanel : public wxPanel
{
private:
	int gridSize;
	void OnPaint(wxPaintEvent& event);
	void OnSizeChanged(wxSizeEvent& event);
public:
	DrawingPanel(wxFrame* Mainwindow, wxSize size, int gridSize);
	~DrawingPanel();
	void SetGridSize(int size);
	
	
};

