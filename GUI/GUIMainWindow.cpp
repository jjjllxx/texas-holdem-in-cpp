#include "GUIMainWindow.h"
#include "ui_GUIMainWindow.h"

th::GUIMainWindow::GUIMainWindow(QWidget* parent) :
    QMainWindow(parent), ui(new Ui::GUIMainWindow)
{
    ui->setupUi(this);
}

th::GUIMainWindow::~GUIMainWindow()
{
    delete ui;
}
