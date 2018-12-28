#ifndef USERPROFILETABCONTROLLER_H
#define USERPROFILETABCONTROLLER_H

namespace Ui {
class MainWindow;
}

class UserProfileTabController
{
public:
    UserProfileTabController(Ui::MainWindow* mainWindow);
    ~UserProfileTabController() = default;
    UserProfileTabController(const UserProfileTabController&) = delete;
    UserProfileTabController(UserProfileTabController&&) = delete;
    UserProfileTabController& operator = (const UserProfileTabController&) = delete;
    UserProfileTabController& operator = (UserProfileTabController&&) = delete;

private:
    Ui::MainWindow* mainWindow;
};

#endif // USERPROFILETABCONTROLLER_H
