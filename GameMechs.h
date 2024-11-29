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

        objPosArrayList* foodPosList; //food objPosArrayList
        
    public:
        GameMechs(); //default constructor
        GameMechs(int boardX, int boardY); // parameterized constructor 
        ~GameMechs();  //destructor 

        objPosArrayList* getFoodPos() const;
        
        //getters and setters -basic implementation from base Project code
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

        //set and get points value
        int getPoints() const;
        void setPoints(int new_points);

        //random food generation
        void generateFood(objPosArrayList& playerPosList);
        
};

#endif