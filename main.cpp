#include "Card/CardDeck.h"

#include "Game/GameTable.h"

int main(int argc, const char *argv[])
{
    (void) argc;
    (void) argv;

    th::GameTable gameTable;
    gameTable.initPokerTable(8, 1000, 5);
    gameTable.getGameNum();
    gameTable.startANewGame();
    gameTable.getGameNum();
    gameTable.clearPokerTable();

    return 0;
}