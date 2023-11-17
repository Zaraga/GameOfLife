#pragma once
#include <wx/colour.h>
#include <iostream>
#include <fstream>
#include <wx/tokenzr.h>



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

    
    
    
    
    wxString Serialize() const {
        wxString data;
        data << "GridSize=" << gridSize << "\n";
        data << "TimerInterval=" << timerInterval << "\n";
        data << "LivingCellRed=" << livingCellRed << "\n";
        data << "LivingCellGreen=" << livingCellGreen << "\n";
        data << "LivingCellBlue=" << livingCellBlue << "\n";
        data << "LivingCellAlpha=" << livingCellAlpha << "\n";
        data << "DeadCellRed=" << deadCellRed << "\n";
        data << "DeadCellGreen=" << deadCellGreen << "\n";
        data << "DeadCellBlue=" << deadCellBlue << "\n";
        data << "DeadCellAlpha=" << deadCellAlpha << "\n";
        data << "ShowNeighborCount=" << showNeighborCount << "\n";


        return data;
    }


    constexpr unsigned int hashStringToInt(const char* str) {
        unsigned int hash = 0;
        for (; *str; ++str) {
            hash = hash * 31 + static_cast<unsigned int>(*str);
        }
        return hash;
    }

    /*static constexpr unsigned int GridSizeKey = hashStringToInt("GridSize"),
        TimerIntervalKey,
        LivingCellRedKey,
        LivingCellGreenKey,
        LivingCellBlueKey,
        LivingCellAlphaKey,
        DeadCellRedKey,
        DeadCellGreenKey,
        DeadCellBlueKey,
        DeadCellAlphaKey,
        ShowNeighborCountKey;*/

    /*void Deserialize(const wxString& data) {
        wxStringTokenizer tokenizer(data, "\n");
        while (tokenizer.HasMoreTokens()) {
            wxString token = tokenizer.GetNextToken();
            wxString key = token.BeforeFirst('=');
            wxString value = token.AfterFirst('=');

            switch (hashStringToInt(key.c_str())) {
                case hashStringToInt("GridSize"):
                    long val;
                    if (value.ToLong(&val)) gridSize = static_cast<int>(val);
                    break;
            }
        }
    }*/


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

