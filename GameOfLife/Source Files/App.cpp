#include "App.h"
#include "MainWindow.h"
#include "DrawingPanel.h"

wxIMPLEMENT_APP(App);

App::App() {

}

App::~App() {

}

bool App::OnInit() {
	//GameSettings settings;
	//settings.Load();
	MainWindow* mainWindow = new MainWindow();	
	mainWindow->Show();

	return true;
}