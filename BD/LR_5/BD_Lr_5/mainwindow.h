#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

    void keyPressEvent(QKeyEvent* event) override;

private slots:
    void on_menuFigureQuad_triggered();

    void on_menuFigureRect_triggered();

    void on_menuFigureCircle_triggered();

    void on_menuFigureSphere_triggered();

    void on_menuFillColor_triggered();

    void on_menuFillTypeFull_triggered();

    void on_menuFillTypeHorizontalLines_triggered();

    void on_menuFillTypeVerticalLines_triggered();

    void on_menuAddTen_triggered();

    void on_menuSubTen_triggered();

    void on_menuFigureLine_triggered();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
