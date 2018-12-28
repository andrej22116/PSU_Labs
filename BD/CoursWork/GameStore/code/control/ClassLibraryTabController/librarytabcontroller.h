#ifndef LIBRARYTABCONTROLLER_H
#define LIBRARYTABCONTROLLER_H

namespace Ui {
class MainWindow;
}

class LibraryTabController
{
public:
    LibraryTabController(Ui::MainWindow* mainWindow);
    ~LibraryTabController() = default;
    LibraryTabController(const LibraryTabController&) = delete;
    LibraryTabController(LibraryTabController&&) = delete;
    LibraryTabController& operator = (const LibraryTabController&) = delete;
    LibraryTabController& operator = (LibraryTabController&&) = delete;

private:
    Ui::MainWindow* mainWindow;
};

#endif // LIBRARYTABCONTROLLER_H
