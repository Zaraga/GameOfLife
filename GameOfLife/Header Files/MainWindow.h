#pragma once
#include "wx/wx.h"
#include "DrawingPanel.h"

class MainWindow : public wxFrame
{
private:
	DrawingPanel* _drawingPanel = nullptr;
	wxToolBar* toolBar = nullptr;
	wxBoxSizer* _sizer = nullptr;

public:
	MainWindow();
	~MainWindow();
	void OnSizeChanged(wxSizeEvent& event);

};

