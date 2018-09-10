#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QFileDialog>

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
    QFileDialog fileDialog;

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

private slots:
    void onClick_buttonAdd(bool checked);
    void onClick_buttonRem(bool checked);
    void onClick_buttonLoad(bool checked);
    void onClick_buttonSave(bool checked);

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
