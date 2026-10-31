#pragma once
#include "mainplayer.h"
#include <vector>
#include <memory>
#include <string>

class Team {
public:
    Team(std::string name, double budget) 
        : Name(name), TransferBudget(budget), TrainingPoints(0) {}
    
    void AddPlayer(std::shared_ptr<Player> player) { 
        Roster.push_back(player); 
        if (StartingXI.size() < 11) StartingXI.push_back(player);
    }
    
    int GetTeamRating() const {
        if (StartingXI.empty()) return 0;
        int totalOVR = 0;
        for (const auto& p : StartingXI) totalOVR += p->GetOVR();
        return totalOVR / StartingXI.size();
    }

    void AddTrainingPoints(int amount) { TrainingPoints += amount; }
    bool SpendTrainingPoints(int amount) {
        if (TrainingPoints >= amount) {
            TrainingPoints -= amount;
            return true;
        }
        return false;
    }
    
    void DeductBudget(double amount) { TransferBudget -= amount; }
    double GetBudget() const { return TransferBudget; }
    int GetTrainingPoints() const { return TrainingPoints; }
    std::string GetName() const { return Name; }

    void ProcessEndOfWeekOrSeason() {
        for (auto& player : Roster) player->SimulateYearlyGrowth();
    }

private:
    std::string Name;
    std::vector<std::shared_ptr<Player>> Roster;
    std::vector<std::shared_ptr<Player>> StartingXI;
    double TransferBudget;
    int TrainingPoints;
};
