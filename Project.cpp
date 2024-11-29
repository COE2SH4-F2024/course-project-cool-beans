#include <iostream>
#include "MacUILib.h"
#include "objPos.h"
#include "Player.h"
#include "GameMechs.h"

using namespace std;

#define DELAY_CONST 100000

//Player and GameMechs initialized
Player *myPlayer;
GameMechs *myGM;

void Initialize(void);
void GetInput(void);
void RunLogic(void);
void DrawScreen(void);
void LoopDelay(void);
void CleanUp(void);


int main(void)
{
    Initialize();

    while(myGM->getExitFlagStatus() == false)  
    {
        GetInput();
        RunLogic();
        DrawScreen();
        LoopDelay();
    }

    CleanUp();
}

void Initialize(void)
{
    MacUILib_init();
    MacUILib_clearScreen();
    
    //random generator
    srand(time(NULL));

    // Initialize heap members
    myGM = new GameMechs();
    myPlayer = new Player(myGM);
}

void GetInput(void)
{   
    //check if key has been pressed then get input(stored in simulatedInput)
    char simulatedInput;
    int pressed;

    pressed = MacUILib_hasChar();

    if(pressed == 1)
    {
        simulatedInput = MacUILib_getChar();
    }
    
    myGM->setInput(simulatedInput);

    // Set exit flag if q is pressed
    if (simulatedInput == 'q') 
    {
        myGM->setExitTrue();
    }
}

void RunLogic(void)
{
    // Use Player class to update move player logic
    myPlayer->updatePlayerDir();
    myPlayer->movePlayer(); 
}

void DrawScreen(void)
{
    MacUILib_clearScreen();
    
    objPosArrayList* playerPos = myPlayer->getPlayerPos(); // Initialize player position
    int playerSize = playerPos->getSize(); // Initialize player size
    objPosArrayList* foodPos = myGM->getFoodPos(); // Initialize food position
    
    //at the beginning of the game foodPos = 0, generate 3 new foods only for the beginning
    if (foodPos->getSize() < 3)
    {
        myGM->generateFood(*playerPos);
    }
    
    //get food list size
    int foodSize = foodPos->getSize();
    
    //boarder size
    int boardX = myGM->getBoardSizeX();
    int boardY = myGM->getBoardSizeY();

    //get head element (for printing elements)
    objPos currentHead = myPlayer->getPlayerPos()->getHeadElement();

    for(int j = 0; j < boardY; j++)
    {
        for(int i = 0; i < boardX; i++)
        {   
            //print player character first
            bool printed = false;
            for(int k = 0; k < playerSize; k++)
            {
                objPos thisSeg = playerPos->getElement(k);

                if(thisSeg.pos->x == i && thisSeg.pos->y == j)//if i and j match player position, print
                {
                    MacUILib_printf("%c", thisSeg.symbol);
                    printed = true;
                    break;
                }
            }

            //print food character
            for(int m = 0; m < foodSize; m++)
            {
                    objPos thisSeg = foodPos->getElement(m);

                    if(thisSeg.pos->x == i && thisSeg.pos->y == j)//if i and j match food position, print
                    {
                        MacUILib_printf("%c", thisSeg.symbol);
                        printed = true;
                        break;
                    }
            }
            
            // If not player, print border and blank spaces
            if(!printed)
            {   
                if(i == boardX - 1)
                {
                    MacUILib_printf("#\n");
                }
                else if(j == 0 || j == boardY - 1 || i == 0)
                {
                    MacUILib_printf("#");
                }
                else 
                {
                    MacUILib_printf(" ");
                }
            }
        }   
    }
    
    MacUILib_printf("\n\n");
    MacUILib_printf("Enter move (w/a/s/d) or q to quit: ");
    MacUILib_printf("\n\nPlayer[x, y] = [%d, %d], %c", currentHead.pos->x, currentHead.pos->y, currentHead.symbol); //player position

    //print all the positions of the food elements
    objPos currentFood = foodPos->getElement(0);
    for (int i = 0; i < foodSize; i++)
    {
        currentFood = foodPos->getElement(i);
        MacUILib_printf("\nFood %d [x, y] = [%d, %d], %c",i+1,currentFood.pos->x, currentFood.pos->y, currentFood.symbol);
    }

    MacUILib_printf("\nSnake Length: %d", playerSize);
    
    //Stuff for printed related to score
    MacUILib_printf("\n\nEffects only increases score. Tail will always increase by 1.\n1 point = 0\t2 points = +\t3 points = !\nScore: %d \n+%d points added!",myGM->getScore(),myGM->getPoints());

    if (myGM->getExitFlagStatus() == true)
    {
        MacUILib_printf("\n-----GAME OVER-----\nScore: %d", myGM->getScore());
    }   
}

void LoopDelay(void)
{
    MacUILib_Delay(DELAY_CONST); // 0.1s delay
}

void CleanUp(void)
{
    // Delete heap members
    delete myPlayer; 
    delete myGM;

    MacUILib_uninit();
}
