#include "Game/GameTable.h"

#include "GUI/GUIMainWindow.h"

#include <QApplication>

int main(int argc, char** argv)
{
    // QApplication app(argc, argv);

    // th::GUIMainWindow mainWindow;

    // mainWindow.show();
    // QApplication::exec();

    (void) argc;
    (void) argv;
    th::GameTable gameTable;
    gameTable.initTable(8, 1000, 5);
    gameTable.getGameNum();
    gameTable.startANewGame();
    gameTable.getGameNum();
    gameTable.clearTable();

    return 0;
}