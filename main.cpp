#include "Card/CardDeck.h"

#include "Game/GameProcess.h"

int main(int argc, const char *argv[])
{
    (void) argc;
    (void) argv;

    th::GameProcess game;
    game.initPokerTable(8, 1000);
    game.clearPokerTable();

    return 0;
}