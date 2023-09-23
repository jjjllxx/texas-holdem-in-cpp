#include "Core/Game/GameTable.h"

int main()
{
    if (th::GameTable gameTable;
        gameTable.init() == true)
    {
        gameTable.start();
        gameTable.clear();
    }

    return 0;
}