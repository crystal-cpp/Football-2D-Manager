#pragma once
#include <string>
#include <vector>
#include <algorithm>
#include <memory>
#include "mainplayer.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <unordered_map>


class PlayerDataBase {
public:
    bool LoadFromCSV(const std::string& filepath) {
        std::ifstream file(filepath);
        if (!file.is_open()) { return false; }
        }
        std::string line;
        bool isHeader = true;

        while (std::getline(file, line)) {
            if (isHeader) { isHeader = false; continue; }
            std::stringstream ss(line);
            std::string name, posStr;
            int pace, shooting, passing, dribbling, defending, physical, age, potential;

            std::getline(ss, name, ',');
            std::getline(ss, posStr, ',');
            ss >> pace; ss.ignore();
            ss >> shooting; ss.ignore();
            ss >> passing; ss.ignore();
            ss >> dribbling; ss.ignore();
            ss >> defending; ss.ignore();
            ss >> physical; ss.ignore();
            ss >> age; ss.ignore();
            ss >> potential;

            Position pos = StringToPosition(posStr);
            PlayerAttributes attrs{ pace, shooting, passing, dribbling, defending, physical };
            auto player = std::make_shared<Player>(name, pos, attrs, age, potential);
            players[name] = player;
        }
        return true;
    
}


