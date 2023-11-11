#pragma once
#include <wx/colour.h>
#include <iostream>
#include <fstream>
//#include "MainWindow.h"
//#include "DrawingPanel.h"

struct GameSettings {
    unsigned int livingCellRed = 128;
    unsigned int livingCellGreen = 128;
    unsigned int livingCellBlue = 128;
    unsigned int livingCellAlpha = 255;

    unsigned int deadCellRed = 255;
    unsigned int deadCellGreen = 255;
    unsigned int deadCellBlue = 255;
    unsigned int deadCellAlpha = 255;

    int gridSize = 15;
    int timerInterval = 50;
    
    bool showNeighborCount = false;
    
    void Save() const {
        std::ofstream file("settings.bin", std::ios::out | std::ios::binary);
        if (file.is_open()) {
            file.write((const char*)this, sizeof(GameSettings));
            file.close();
        }
    }
    
    void Load() {
        std::ifstream file("settings.bin", std::ios::binary | std::ios::in);
        if (file.is_open()) {
            file.read((char*)this, sizeof(GameSettings));
            file.close();
        }
    }

    wxColor GetLivingCellColor() const {
        return wxColor(livingCellRed, livingCellGreen, livingCellBlue, livingCellAlpha);
    }

    wxColor GetDeadCellColor() const {
        return wxColor(deadCellRed, deadCellGreen, deadCellBlue, deadCellAlpha);
    }

    void SetLivingCellColor(const wxColor& color) {
        livingCellRed = color.Red();
        livingCellGreen = color.Green();
        livingCellBlue = color.Blue();
        livingCellAlpha = color.Alpha();
       /* std::cout << "Living Cell Red: " << livingCellRed << std::endl;
        std::cout << "Living Cell Green: " << livingCellGreen << std::endl;
        std::cout << "Living Cell Blue: " << livingCellBlue << std::endl;
        std::cout << "Living Cell Alpha: " << livingCellAlpha << std::endl;*/
    }

    void SetDeadCellColor(const wxColor& color) {
        deadCellRed = color.Red();
        deadCellGreen = color.Green();
        deadCellBlue = color.Blue();
        deadCellAlpha = color.Alpha();
    }

    GameSettings() = default;
};

extern GameSettings settings;

