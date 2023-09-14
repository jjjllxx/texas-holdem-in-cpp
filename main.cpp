#include "Game/GameTable.h"

int main()
{
    th::GameTable gameTable;
    gameTable.initTable(8, 1000, 5);
    gameTable.startANewGame();
    gameTable.clearTable();

    return 0;
}