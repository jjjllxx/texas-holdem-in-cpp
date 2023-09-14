#include "GUIMainWindow.h"

#include <QApplication>

int main(int argc, char** argv)
{
    QApplication app(argc, argv);

    th::GUIMainWindow mainWindow;

    mainWindow.show();
    QApplication::exec();

    return 0;
}