#include "Game/GameTable.h"

#include "GUI/GUIMainWindow.h"

#include <QApplication>

int main(int argc, char** argv)
{
    QApplication app(argc, argv);

    th::GUIMainWindow mainWindow;

    mainWindow.show();
    QApplication::exec();

    // th::GameTable gameTable;
    // gameTable.initPokerTable(8, 1000, 5);
    // gameTable.getGameNum();
    // gameTable.startANewGame();
    // gameTable.getGameNum();
    // gameTable.clearPokerTable();

    return 0;
}