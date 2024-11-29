#ifndef PLAYER_H
#define PLAYER_H

#include "GameMechs.h"
#include "objPos.h"
#include "objPosArrayList.h"

class Player
{
    public:
        enum Dir {UP, DOWN, LEFT, RIGHT, STOP};

        Player(GameMechs* thisGMRef);
        ~Player();

        objPosArrayList* getPlayerPos() const;  
        void updatePlayerDir();
        void movePlayer();

    private:      
        objPosArrayList* playerPosList;
        enum Dir myDir;
        GameMechs* mainGameMechsRef;
};

#endif