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
<<<<<<< HEAD
=======

>>>>>>> 460677fe782a08528b9498a9281666d4753e3593
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

<<<<<<< HEAD
=======

// just for now to only generate one character, global variable at the top currently.
>>>>>>> 460677fe782a08528b9498a9281666d4753e3593
    if (hit == true)
    {
        myGM->generateFood(playerPos);
        hit = false;
    }
<<<<<<< HEAD
    const objPos* foodPos = myGM->getFoodPos();
=======

    const objPos* foodPos = myGM->getFoodPos();
    
>>>>>>> 460677fe782a08528b9498a9281666d4753e3593
    
    for(int j = 0; j < myGM->getBoardSizeY(); j++)
    {
        for(int i = 0; i < myGM->getBoardSizeX(); i++)
        {
            if(i == playerPos.pos->x && j == playerPos.pos->y)
            {
                MacUILib_printf("%c", playerPos.symbol);
            }
            else if (i == foodPos->pos->x && j == foodPos->pos->y) {
                MacUILib_printf("%c", foodPos->symbol); 
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

<<<<<<< HEAD
    MacUILib_printf("\n");
=======
    MacUILib_printf("\n\n");
>>>>>>> 460677fe782a08528b9498a9281666d4753e3593
    MacUILib_printf("Enter move (w/a/s/d) or q to quit: ");
    MacUILib_printf("\n\nPlayer[x, y] = [%d, %d], %c", playerPos.pos->x, playerPos.pos->y, playerPos.symbol);
    MacUILib_printf("\nFood[x, y] = [%d, %d], %c", foodPos->pos->x, foodPos->pos->y, foodPos->getSymbol());
    MacUILib_printf("\nScore: %d\nScore is currently increasing by %d point(s)!", myGM->getScore(), myGM->getPoints());
    //can change score statement later
<<<<<<< HEAD
=======


>>>>>>> 460677fe782a08528b9498a9281666d4753e3593
    if (myGM->getExitFlagStatus() == true)
    {
        MacUILib_printf("\n-----GAME OVER-----\nScore: %d", myGM->getScore());
    }
<<<<<<< HEAD
=======
    
>>>>>>> 460677fe782a08528b9498a9281666d4753e3593
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
