#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QtSql>
#include <QMap>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

    QSqlDatabase _pg_database;
    QMap<QString, QSqlDatabase> _databases;

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_buttonConnect_clicked();

    void on_buttonDisconnect_clicked();

    void on_dbTreeNodeSelected(const QItemSelection& current , const QItemSelection& previous);

private:
    bool connectToServer();


private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
