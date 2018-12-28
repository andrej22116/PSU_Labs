#ifndef DEVELOPMENTTABCONTROLLER_H
#define DEVELOPMENTTABCONTROLLER_H

namespace Ui {
class MainWindow;
}

class DevelopmentTabController
{
public:
    DevelopmentTabController(Ui::MainWindow* mainWindow);
    ~DevelopmentTabController() = default;
    DevelopmentTabController(const DevelopmentTabController&) = delete;
    DevelopmentTabController(DevelopmentTabController&&) = delete;
    DevelopmentTabController& operator = (const DevelopmentTabController&) = delete;
    DevelopmentTabController& operator = (DevelopmentTabController&&) = delete;

private:
    Ui::MainWindow* mainWindow;
};

#endif // DEVELOPMENTTABCONTROLLER_H
