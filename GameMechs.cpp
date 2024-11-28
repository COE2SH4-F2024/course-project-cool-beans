#include "GameMechs.h"

GameMechs::GameMechs()
{
    input = 0;
    points = 1;
    exitFlag = false;
    loseFlag = false;
    score = 0;
    boardSizeX = 30;
    boardSizeY = 15;
    food = new objPos(0, 0, 'O');
}

GameMechs::GameMechs(int boardX, int boardY)
{
    input = 0;
    points = 1;
    exitFlag = false;
    loseFlag = false;
    score = 0;
    boardSizeX = boardX;
    boardSizeY = boardY;
    food = new objPos(0, 0, 'O');
}


GameMechs::~GameMechs()
{
    delete food;
}



bool GameMechs::getExitFlagStatus() const
{
    return exitFlag; 
}

bool GameMechs::getLoseFlagStatus() const
{
    return loseFlag;
}
    

char GameMechs::getInput() const
{
    return input;
}

int GameMechs::getScore() const
{
    return score;
}

void GameMechs::incrementScore()
{
    score += points;
}

int GameMechs::getBoardSizeX() const
{
    return boardSizeX;
}

int GameMechs::getBoardSizeY() const
{
    return boardSizeY;
}


void GameMechs::setExitTrue()
{
    exitFlag = true;
}

void GameMechs::setLoseFlag()
{
    loseFlag = true;
}

void GameMechs::setInput(char this_input)
{
    input = this_input;
}

void GameMechs::clearInput()
{
    input = 0;
}

// More methods should be added here

void GameMechs::setPoints(int new_points)
{
    points = new_points;
}

int GameMechs::getPoints() const
{
    return points;
}

void GameMechs::generateFood(objPos blockOff){//block off = players current position
    int foodX, foodY;

    int X = boardSizeX - 2;
    int Y = boardSizeY - 2;
    //considering all ends of the border

    do
    {
        foodX = (rand() % X) + 1;
        foodY = (rand() % Y) + 1;

    } while (foodX == blockOff.pos->x && foodY == blockOff.pos->y);

    
    food->setObjPos(foodX,foodY,'O');
    
}

const objPos* GameMechs::getFoodPos() const{
    return food;
}