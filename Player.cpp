#include "Player.h"


Player::Player(GameMechs* thisGMRef)
{
    mainGameMechsRef = thisGMRef;
    myDir = STOP;

    playerPos.pos->x = mainGameMechsRef->getBoardSizeX() / 2;
    playerPos.pos->y = mainGameMechsRef->getBoardSizeY() / 2;
    playerPos.symbol = '*';
    // more actions to be included
}


Player::~Player()
{
    // delete any heap members here
}

objPos Player::getPlayerPos() const
{
    return playerPos;
    // return the reference to the playerPos arrray list
}

void Player::updatePlayerDir()
{
    char input = mainGameMechsRef->getInput();
        // PPA3 input processing logic     
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
    // PPA3 Finite State Machine logic
    switch(myDir)
    {
        case UP:  // Decrease y if direction is up, wrap around when at boundary
            playerPos.pos->y--;
            if(playerPos.pos->y < 1)
            {
                playerPos.pos->y = mainGameMechsRef->getBoardSizeY() - 2;
            }
            break;

        case LEFT:  // Decrease x if direction is left, wrap around when at boundary
            playerPos.pos->x--;
            if(playerPos.pos->x < 1)
            {
                playerPos.pos->x = mainGameMechsRef->getBoardSizeX() - 2;
            }
            break;
        
        case DOWN:  // Increase y if direction is down, wrap around when at boundary
            playerPos.pos->y++;
            if(playerPos.pos->y > mainGameMechsRef->getBoardSizeY() - 2)
            {
                playerPos.pos->y = 1;
            }
            break;
        
        case RIGHT:  // Increase x if direction is right, wrap around when at boundary
            playerPos.pos->x++;
            if(playerPos.pos->x > mainGameMechsRef->getBoardSizeX() - 2)
            {
                playerPos.pos->x = 1;
            }
            break;

        case STOP:
        default:
            break;
    }
}

// More methods to be added