#include "Core/Game/GameTable.h"

int main()
{
    th::GameTable gameTable;
    if (gameTable.init() == true)
    {
        gameTable.startANewGame();
        gameTable.clear();
    }

    return 0;
}