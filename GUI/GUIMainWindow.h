#pragma once

#include <QMainWindow>

namespace Ui
{
class GUIMainWindow;
}

namespace th
{
class GUIMainWindow final : public QMainWindow
{
    Q_OBJECT

public:
    GUIMainWindow(QWidget* parent = nullptr);
    ~GUIMainWindow() override;

private:
    Ui::GUIMainWindow* ui;
};
} // namespace th
