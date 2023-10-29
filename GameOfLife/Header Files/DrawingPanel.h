#pragma once
#include "wx/wx.h"
class DrawingPanel : public wxPanel
{
public:
	DrawingPanel(wxFrame* Mainwindow);
	~DrawingPanel();
	
	void OnPaint(wxPaintEvent& event);
};

