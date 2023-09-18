#include "Core/Game/GameTable.h"

int main()
{
    th::GameTable gameTable;
    if (gameTable.initTable(8, 1000, 5) == true)
    {
        gameTable.startANewGame();
        gameTable.clearTable();
    }

    return 0;
}