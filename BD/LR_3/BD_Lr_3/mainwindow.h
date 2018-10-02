#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QFileDialog>

#include "src/ClassDataBaseConnectDialog/DataBaseConnectDialog.h"

class QValidator;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

    QValidator* nameValidator = nullptr;
    QValidator* dateValidator = nullptr;

    QMessageBox removeQuestionDialog;
    QFileDialog fileOpenDialog;
    QFileDialog fileSaveDialog;

    QSqlDatabase database;

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    void initValidators();
    void initControls();
    void initTable();
    void initDialogs();

    void addLineToTable(const QString& fio, const QString& bornDate, const QString& group,
                        const QString& number, const QString& addres, size_t line = 0);

    void removeLineFromTable(size_t line);

    bool saveToTxtFile(const QString& path);
    bool loadFromTxtFile(const QString& path);
    bool saveToBinaryFile(const QString& path);
    bool loadFromBinaryFile(const QString& path);
    bool saveToDataBase();
    bool loadFromDataBase();

private slots:
    void onClick_buttonAdd();
    void onClick_buttonRem();
    void onClick_buttonLoad();
    void onClick_buttonSave();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
