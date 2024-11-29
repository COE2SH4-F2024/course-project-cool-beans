#include "Player.h"


Player::Player(GameMechs* thisGMRef)
{
    mainGameMechsRef = thisGMRef; // Store reference to GameMechs
    playerPosList = new objPosArrayList(); // Initialize player position list
    myDir = STOP; // Initialize player not moving

    // Add starting head position to list
    objPos headPos(thisGMRef->getBoardSizeX() / 2, thisGMRef->getBoardSizeY() / 2, '*');
    playerPosList->insertHead(headPos);
}

Player::~Player()
{
    delete playerPosList; // delete heap members
}

objPosArrayList* Player::getPlayerPos() const
{
    return playerPosList; // return the reference to the playerPos array list
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

    mainGameMechsRef->clearInput(); // Clear input after processing
}

void Player::movePlayer()
{
    updatePlayerDir(); // Update direction before moving

    objPos currentHead = playerPosList->getHeadElement(); // Get current head position
    objPos newHead = currentHead; // Initialize new head position
    objPosArrayList* foodPosList = mainGameMechsRef->getFoodPos(); // Get food positions

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

    // Check for self collision
    for (int k = 0; k < playerPosList->getSize(); k++) 
    {
        objPos bodyPart = playerPosList->getElement(k);

        if (newHead.pos->x == bodyPart.pos->x && newHead.pos->y == bodyPart.pos->y) 
        {
            // Set lose and exit flag if head collides with part of snake body
            if (k != playerPosList->getSize() - 1)
            {
                mainGameMechsRef->setLoseFlag();
                mainGameMechsRef->setExitTrue();
                return;
            }
        }
    }

    
    // Check for collision with food
    for (int i = 0; i < foodPosList->getSize(); i++)
    {
        objPos currentFood = foodPosList->getElement(i); //get food element at i to compared with snake/player body

        if (newHead.pos->x == currentFood.pos->x && newHead.pos->y == currentFood.pos->y) //see if food element at i collided with snake/player body
        {
            playerPosList->insertHead(newHead); // Add new head without removing tail if food collision

            // get the food symbol that the snake has collided with
            char symbolCollison = currentFood.getSymbol();

            // Update score based on food symbol
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
        
        mainGameMechsRef->incrementScore(); // Update total score

        int size = foodPosList->getSize(); //get size of foodPosList to know how many to remove
        
        // Clear all food
        for (int j = 0; j < size; j++)
        {
            foodPosList->removeElement(j);
        }
        
        
        mainGameMechsRef->generateFood(*playerPosList); // Generate new food

        return;
        }
    }

    // Add new head and remove tail when not food collision (normal movement)
    playerPosList->insertHead(newHead);
    playerPosList->removeTail();
}