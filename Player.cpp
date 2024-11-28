#include "Player.h"


Player::Player(GameMechs* thisGMRef)
{
    mainGameMechsRef = thisGMRef;
    playerPosList = new objPosArrayList();
    myDir = STOP;

    objPos headPos(thisGMRef->getBoardSizeX() / 2, thisGMRef->getBoardSizeY() / 2, '*');

    playerPosList->insertHead(headPos);

    //playerPos.pos->x = mainGameMechsRef->getBoardSizeX() / 2;
    //playerPos.pos->y = mainGameMechsRef->getBoardSizeY() / 2;
    //playerPos.symbol = '*';
    // more actions to be included
}


Player::~Player()
{
    // delete any heap members here
    delete playerPosList;
}

objPosArrayList* Player::getPlayerPos() const
{
    return playerPosList;
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
    updatePlayerDir(); //???

    //TO DO - temp objpos to calc new head pos, get head element of arraylist

    // PPA3 Finite State Machine logic
    switch(myDir)
    {
        //TO DO - calc new pos of head using temp objpos
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
    //TO DO - insert temp objpos to head of list

    //Feat 2 TO DO - check if new temp objpos overlaps food pos (gamemechs), use isPosEqual from objPos class
    //if overlap, food consumed, do not remove tail, increase score
    //if no overlap, remove tail, complete movement
}

// More methods to be added