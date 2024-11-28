#include <iostream>
#include "MacUILib.h"
#include "objPos.h"
#include "Player.h"
#include "GameMechs.h"

using namespace std;

#define DELAY_CONST 100000

Player *myPlayer;
GameMechs *myGM;
bool hit = true;

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
    
    srand(time(NULL));

    srand(time(NULL));

    myGM = new GameMechs();
    myPlayer = new Player(myGM);
}

void GetInput(void)
{
    char simulatedInput;
    int pressed;

    pressed = MacUILib_hasChar();

    if(pressed == 1){
        simulatedInput = MacUILib_getChar();
    }
    
    myGM->setInput(simulatedInput);
    if (simulatedInput == 'q') {
        myGM->setExitTrue();
    }
}

void RunLogic(void)
{
    myPlayer->updatePlayerDir();
    myPlayer->movePlayer(); 
}

void DrawScreen(void)
{
    MacUILib_clearScreen();
    
    objPosArrayList* playerPos = myPlayer->getPlayerPos();
    int playerSize = playerPos->getSize();
    const objPos* foodPos = myGM->getFoodPos();
    int boardX = myGM->getBoardSizeX();
    int boardY = myGM->getBoardSizeY();
    objPos currentHead = myPlayer->getPlayerPos()->getHeadElement();

    // just for now to only generate one character, global variable at the top currently.
    if (hit == true)
    {
        myGM->generateFood(*playerPos);
        hit = false;
    }
    
    for(int j = 0; j < boardY; j++)
    {
        for(int i = 0; i < boardX; i++)
        {
            bool printed = false;
            for(int k = 0; k < playerSize; k++)
            {
                objPos thisSeg = playerPos->getElement(k);

                if(thisSeg.pos->x == i && thisSeg.pos->y == j)
                {
                    MacUILib_printf("%c", thisSeg.symbol);
                    printed = true;
                    break;
                }
            }
            
            if(!printed)
            {
                if (i == foodPos->pos->x && j == foodPos->pos->y) 
                {
                    MacUILib_printf("%c", foodPos->symbol); 
                }
                else if(i == boardX - 1)
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
    MacUILib_printf("\n\nPlayer[x, y] = [%d, %d], %c", currentHead.pos->x, currentHead.pos->y, currentHead.symbol);
    MacUILib_printf("\nFood[x, y] = [%d, %d], %c", foodPos->pos->x, foodPos->pos->y, foodPos->getSymbol());
    MacUILib_printf("\nScore: %d\nScore is currently increasing by %d point(s)!", myGM->getScore(), myGM->getPoints());
    //can change score statement later

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
    delete myPlayer; 
    delete myGM;

    MacUILib_uninit();
}
