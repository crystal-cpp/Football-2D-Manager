#pragma once
#include <string>
#include <vector>
#include <algorithm>

enum class Position { GK, CB, LB, RB, CM, CDM, CAM, LW, RW, ST };

struct PlayerAttributes {
    int Pace, Shooting, Passing, Dribbling, Defending, Physical;
};

class Player {
public:
    Player(std::string name, Position pos, PlayerAttributes attrs, int age, int potential) 
        : Name(name), Pos(pos), Attributes(attrs), Age(age), Potential(potential), CurrentXP(0) {
        CalculateOVR();
    }
    
    void CalculateOVR() {
        if (Pos == Position::ST or Pos == Position::LW or Pos == Position::RW) {
            OVR = (Attributes.Shooting * 0.4) + (Attributes.Pace * 0.3) + (Attributes.Dribbling * 0.3);
        } else if (Pos == Position::CM or Pos == Position::CAM or Pos == Position::CDM) {
            OVR = (Attributes.Passing * 0.5) + (Attributes.Dribbling * 0.3) + (Attributes.Defending * 0.2);
        } else if (Pos == Position::CB or Pos == Position::LB or Pos == Position::RB) {
            OVR = (Attributes.Defending * 0.6) + (Attributes.Physical * 0.3) + (Attributes.Pace * 0.1);
        } else {
            OVR = Attributes.Defending; 
        }
    }

    bool ApplyTrainingXP(int xpAmount) {
        if (OVR >= Potential) return false;

        CurrentXP += xpAmount;
        int xpNeeded = OVR * 100; 

        if (CurrentXP >= xpNeeded) {
            CurrentXP -= xpNeeded;
            LevelUpAttributes(1);
            return true; 
        }
        return false;
    }

    void SimulateYearlyGrowth() {
        Age++;
        if (Age < 24 && OVR < Potential) {
            LevelUpAttributes(2); 
        } else if (Age >= 32) {
            DeclineAttributes(1);
        }
    }

    std::string GetName() const { return Name; }
    int GetOVR() const { return OVR; }
    int GetAge() const { return Age; }
    double GetMarketValue() const { return OVR * 1000000.0; }

private:
    std::string Name;
    Position Pos;
    PlayerAttributes Attributes;
    int OVR, Age, Potential, CurrentXP;

    void LevelUpAttributes(int amount) {
        Attributes.Pace = std::min(99, Attributes.Pace + amount);
        Attributes.Shooting = std::min(99, Attributes.Shooting + amount);
        Attributes.Passing = std::min(99, Attributes.Passing + amount);
        Attributes.Dribbling = std::min(99, Attributes.Dribbling + amount);
        Attributes.Defending = std::min(99, Attributes.Defending + amount);
        Attributes.Physical = std::min(99, Attributes.Physical + amount);
        CalculateOVR();
    }

    void DeclineAttributes(int amount) {
        Attributes.Pace = std::max(1, Attributes.Pace - amount * 2); 
        Attributes.Physical = std::max(1, Attributes.Physical - amount);
        CalculateOVR();
    }
};
