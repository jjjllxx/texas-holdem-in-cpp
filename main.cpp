#include "Core/Game/GameTable.h"

int main()
{
    th::GameTable gameTable;
    if (gameTable.init() == true)
    {
        gameTable.start();
        gameTable.clear();
    }

    return 0;
}