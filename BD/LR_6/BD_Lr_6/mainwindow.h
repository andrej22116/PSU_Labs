#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtSql>

namespace Ui {
class MainWindow;
}

namespace QtCharts {
class QLineSeries;
class QChart;
class QAreaSeries;
class QChartView;
class QDateTimeAxis;
class QValueAxis;
}

class DataBaseConnectDialog;

class MainWindow : public QMainWindow
{
    Q_OBJECT

    QSqlDatabase _database;
    QtCharts::QChartView* _view;
    QtCharts::QAreaSeries* _area = nullptr;
    QtCharts::QLineSeries* _data = nullptr;
    QtCharts::QChart* _chart = nullptr;
    QtCharts::QDateTimeAxis* _axisX = nullptr;
    QtCharts::QValueAxis* _axisY = nullptr;
    DataBaseConnectDialog* _dbConnectDialog = nullptr;

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

private slots:
    void on_action_connectToDB_triggered();

    void on_action_update_triggered();

private:
    void makeAxisX();
    void makeAxisY();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
