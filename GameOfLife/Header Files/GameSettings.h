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


   unsigned int hashStringToInt(const char* str) {
        unsigned int hash = 0;
        for (; *str; ++str) {
            hash = hash * 31 + static_cast<unsigned int>(*str);
        }
        return hash;
    }

   enum {
       GridSize,
       TimerInterval,
       LivingCellRed,
       LivingCellGreen,
       LivingCellBlue,
       LivingCellAlpha,
       DeadCellRed,
       DeadCellGreen,
       DeadCellBlue,
       DeadCellAlpha,
   };
   bool ShowNeighborCount;
   
   

    void Deserialize(const wxString& data) {
        wxStringTokenizer tokenizer(data, "\n");
        long val;
        while (tokenizer.HasMoreTokens()) {
            wxString token = tokenizer.GetNextToken();
            wxString key = token.BeforeFirst('=');
            wxString value = token.AfterFirst('=');

            int hashedKey = hashStringToInt(key.c_str());

            if (key == "GridSize") {
                if (value.ToLong(&val)) gridSize = static_cast<int>(val);                
            }
            else if (key == "TimerInterval") {
                if (value.ToLong(&val)) timerInterval = static_cast<int>(val);
            }
            else if (key == "LivingCellRed") {
                if (value.ToLong(&val)) livingCellRed = static_cast<int>(val);
            }
            else if (key == "LivingCellGreen") {
                if (value.ToLong(&val)) livingCellGreen = static_cast<int>(val);
            }
            else if (key == "LivingCellBlue") {
                if (value.ToLong(&val)) livingCellBlue = static_cast<int>(val);
            }
            else if (key == "LivingCellAlpha") {
                if (value.ToLong(&val)) livingCellAlpha = static_cast<int>(val);
            }
            else if (key == "DeadCellRed") {
                if (value.ToLong(&val)) deadCellRed = static_cast<int>(val);
            }
            else if (key == "DeadCellGreen") {
                if (value.ToLong(&val)) deadCellGreen = static_cast<int>(val);
            }
            else if (key == "DeadCellBlue") {
                if (value.ToLong(&val)) deadCellBlue = static_cast<int>(val);
            }
            else if (key == "DeadCellAlpha") {
                if (value.ToLong(&val)) deadCellAlpha = static_cast<int>(val);
            }
            else if (key == "ShowNeighborCount") {
                if (value.ToLong(&val)) showNeighborCount = (val != 0);
            }
        }
    }


    /*void Save() const {
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
    }*/

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

