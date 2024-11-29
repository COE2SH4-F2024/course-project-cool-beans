#include "Player.h"


Player::Player(GameMechs* thisGMRef)
{
    mainGameMechsRef = thisGMRef;
    playerPosList = new objPosArrayList();
    myDir = STOP;

    objPos headPos(thisGMRef->getBoardSizeX() / 2, thisGMRef->getBoardSizeY() / 2, '*');
    playerPosList->insertHead(headPos);
}


Player::~Player()
{
    // delete any heap members here
    delete playerPosList;
}

objPosArrayList* Player::getPlayerPos() const
{
    return playerPosList;
    // return the reference to the playerPos array list
}

void Player::updatePlayerDir()
{
    char input = mainGameMechsRef->getInput();
             
    switch(input)
    {                      
        case 'w':  // Set direction to up only if stopped, left, or right
            if(myDir == STOP || myDir == LEFT || myDir == RIGHT)
            {
                myDir = UP;
            }
            break;

        case 'a':  // Set direction to left only if stopped, up, or down
            if(myDir == STOP || myDir == UP || myDir == DOWN)
            {
                myDir = LEFT;
            }
            break;

        case 's':  // Set direction to down only if stopped, left, or right
            if(myDir == STOP || myDir == LEFT || myDir == RIGHT)
            {
                myDir = DOWN;
            }
        break;

        case 'd':  // Set direction to right only if stopped, up, or down
            if(myDir == STOP || myDir == UP || myDir == DOWN)
            {
                myDir = RIGHT;
            }
        break;

        default:
            break;
    }             

    mainGameMechsRef->clearInput();
}

void Player::movePlayer()
{
    updatePlayerDir();

    objPos currentHead = playerPosList->getHeadElement();
    objPos newHead = currentHead;
    objPosArrayList* foodPosList = mainGameMechsRef->getFoodPos();

    switch(myDir)
    {
        case UP:  // Decrease y if direction is up, wrap around when at boundary
            newHead.pos->y--;
            if(newHead.pos->y < 1)
            {
                newHead.pos->y = mainGameMechsRef->getBoardSizeY() - 2;
            }
            break;

        case LEFT:  // Decrease x if direction is left, wrap around when at boundary
            newHead.pos->x--;
            if(newHead.pos->x < 1)
            {
                newHead.pos->x = mainGameMechsRef->getBoardSizeX() - 2;
            }
            break;
        
        case DOWN:  // Increase y if direction is down, wrap around when at boundary
            newHead.pos->y++;
            if(newHead.pos->y > mainGameMechsRef->getBoardSizeY() - 2)
            {
                newHead.pos->y = 1;
            }
            break;
        
        case RIGHT:  // Increase x if direction is right, wrap around when at boundary
            newHead.pos->x++;
            if(newHead.pos->x > mainGameMechsRef->getBoardSizeX() - 2)
            {
                newHead.pos->x = 1;
            }
            break;

        case STOP:
        default:
            break;
    }
    objPos currentFood = foodPosList->getElement(0);

    for (int i = 0; i < foodPosList->getSize(); i++)
    {
        currentFood = foodPosList->getElement(i);
        if (newHead.pos->x == currentFood.pos->x && newHead.pos->y == currentFood.pos->y)
        {
            playerPosList->insertHead(newHead);

            char symbolCollison = currentFood.getSymbol();
            switch ((int)symbolCollison)
            {
            case 48:
                mainGameMechsRef->setPoints(1);
                break;
            case 43:
                mainGameMechsRef->setPoints(2);
                break;
            case 33:
                mainGameMechsRef->setPoints(3);
                break;
            default:
                break;
            }
        
        //these have to be after
        mainGameMechsRef->incrementScore();
        for (int j = 0; j < foodPosList->getSize(); j++)
        {
            foodPosList->removeHead();
            foodPosList->removeTail();
        }
        
        mainGameMechsRef->generateFood(*playerPosList);

        }
        else
        {
            playerPosList->insertHead(newHead);
            playerPosList->removeTail();
        }
        
    }
}

// More methods to be added