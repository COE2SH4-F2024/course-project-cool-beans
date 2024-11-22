#include <iostream>
#include "MacUILib.h"
#include "objPos.h"
#include "Player.h"
#include "GameMechs.h"

using namespace std;

#define DELAY_CONST 100000

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

    myGM = new GameMechs();
    myPlayer = new Player(myGM);
}

void GetInput(void)
{
   
}

void RunLogic(void)
{
    myPlayer->updatePlayerDir();
    myPlayer->movePlayer();
}

void DrawScreen(void)
{
    MacUILib_clearScreen();
    
    objPos playerPos = myPlayer->getPlayerPos();
    
    for(int j = 0; j < myGM->getBoardSizeY(); j++)
    {
        for(int i = 0; i < myGM->getBoardSizeX(); i++)
        {
            if(i == playerPos.pos->x && j == playerPos.pos->y)
            {
                MacUILib_printf("%c", playerPos.symbol);
            }
            else if(i == myGM->getBoardSizeX() - 1)
            {
                MacUILib_printf("#\n");
            }
            else if(j == 0 || j == myGM->getBoardSizeY() - 1 || i == 0)
            {
                MacUILib_printf("#");
            }
            else 
            {
                MacUILib_printf(" ");
            }
        }   
    }

    MacUILib_printf("\n");
    MacUILib_printf("Player[x, y] = [%d, %d], %c", playerPos.pos->x, playerPos.pos->y, playerPos.symbol);
}

void LoopDelay(void)
{
    MacUILib_Delay(DELAY_CONST); // 0.1s delay
}


void CleanUp(void)
{
    MacUILib_clearScreen();   

    delete myPlayer; 
    delete myGM;

    MacUILib_uninit();
}
