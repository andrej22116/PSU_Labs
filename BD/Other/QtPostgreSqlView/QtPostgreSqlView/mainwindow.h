#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QtSql>
#include <QMap>

#include "src/ClassPostgreSqlView/postgresqlview.h"

namespace Ui {
class MainWindow;
}

class QTreeWidgetItem;

class MainWindow : public QMainWindow
{
    Q_OBJECT



public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_dbTreeNodeSelected(const QItemSelection& current , const QItemSelection& previous);

    void on_actionSetConnectInfo_triggered();

    void on_actionClearTree_triggered();

private:
    void makeRootItem();
    void makeRouterMap();
    void makeBranchFromList( const NamesList& namesList
                           , QTreeWidgetItem* root
                           , const std::function<void(QTreeWidgetItem*)> fn
                           );

    void loadDatabaseItems(QTreeWidgetItem* rootItem);
    void loadSchemasItems(QTreeWidgetItem* schemaItem);
    void loadTablesItems(QTreeWidgetItem* tableItem);
    void loadColumnsItems(QTreeWidgetItem* columnItem);
    void loadFunctionsItems(QTreeWidgetItem* functionItem);

    QLinearGradient getGradientBrush(const QColor& beginColor, const QColor& endColor);

private:
    Ui::MainWindow *ui;

    PostgreSqlView pgView;

    QMap<QString, decltype(&MainWindow::loadDatabaseItems)> routerSelectMap;
};

#endif // MAINWINDOW_H
