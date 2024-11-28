#ifndef GAMEMECHS_H
#define GAMEMECHS_H

#include <cstdlib>
#include <time.h>

#include "objPos.h"
#include "objPosArrayList.h"

using namespace std;

class GameMechs
{
    private:
        char input; //last input
        bool exitFlag;
        bool loseFlag;
        int score;
        int points;

        int boardSizeX;
        int boardSizeY;

        objPos* food;

    public:
        GameMechs();
        GameMechs(int boardX, int boardY);
        ~GameMechs(); 
        
        //getters and setters
        bool getExitFlagStatus() const; 
        void setExitTrue();
        bool getLoseFlagStatus() const;
        void setLoseFlag();

        char getInput() const;
        void setInput(char this_input);
        void clearInput();

        int getBoardSizeX() const;
        int getBoardSizeY() const;
        
        int getScore() const;
        void incrementScore();
        
        // More methods should be added here

        int getPoints() const;
        void setPoints(int new_points);

        void generateFood(objPos blockOff);
        const objPos* getFoodPos() const;

};

#endif