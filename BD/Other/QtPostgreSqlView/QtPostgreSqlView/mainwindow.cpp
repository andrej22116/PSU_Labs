#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "ui_inputdatabaseconnectinfodialog.h"

#include <QtSvg/QSvgRenderer>
#include <QPixmap>

enum TreeTextColors {
    Color_Database = 0xe0c58f,
    Color_Schema = 0xf7ccb9,
    Color_Table = 0xb1deed,
    Color_Function = 0xd1edb1,
    Color_Column = 0xb1edbe
};

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    makeRootItem();
    makeRouterMap();

    auto selectionModel = ui->dbTreeWidget->selectionModel();
    connect(selectionModel, &QItemSelectionModel::selectionChanged, this, &MainWindow::on_dbTreeNodeSelected);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_dbTreeNodeSelected(const QItemSelection& selected , const QItemSelection& deselected)
{
    auto item = ui->dbTreeWidget->currentItem();
    ui->dbTreeWidget->clearSelection();

    ui->statusBar->showMessage(item->text(0));

    if ( routerSelectMap.contains(item->text(0)) && item->childCount() == 0 ) {
        try {
            (this->*routerSelectMap[item->text(0)])(item);
            item->setExpanded(true);
        } catch (QString exceptionMessage) {
            ui->statusBar->showMessage(exceptionMessage);
        }
    }
}


void MainWindow::makeRootItem()
{
    auto root = new QTreeWidgetItem(ui->dbTreeWidget);
    root->setText(0, "Databases");
    root->setIcon(0, QIcon(":/icons/database_bad"));
    root->setTextColor(0, QColor(TreeTextColors::Color_Database));

    ui->dbTreeWidget->addTopLevelItem(root);
}

void MainWindow::makeRouterMap()
{
    routerSelectMap["Databases"] = &MainWindow::loadDatabaseItems;
    routerSelectMap["Schemas"] = &MainWindow::loadSchemasItems;
    routerSelectMap["Tables"] = &MainWindow::loadTablesItems;
    routerSelectMap["Columns"] = &MainWindow::loadColumnsItems;
    routerSelectMap["Functions"] = &MainWindow::loadFunctionsItems;
}

void MainWindow::makeBranchFromList(const NamesList& namesList, QTreeWidgetItem* root,
                                    const std::function<void(QTreeWidgetItem*)> fn)
{
    for (const auto& itemName : namesList) {
        auto item = new QTreeWidgetItem();
        item->setText(0, itemName);

        if ( fn != nullptr ) {
            fn(item);
        }

        root->addChild(item);
    }
}

void MainWindow::loadDatabaseItems(QTreeWidgetItem* rootItem)
{
    auto dbList = pgView.getDatabasesList();

    auto schemasBkBrush = getGradientBrush(QColor(247, 204, 185, 60),
                                           QColor(247, 204, 185, 0));

    makeBranchFromList(dbList, rootItem, [&schemasBkBrush](QTreeWidgetItem* item) {
        auto schemasItem = new QTreeWidgetItem();
        schemasItem->setText(0, "Schemas");
        schemasItem->setIcon(0, QIcon(":/icons/schemas"));
        schemasItem->setTextColor(0, QColor(TreeTextColors::Color_Schema));
        schemasItem->setBackground(0, schemasBkBrush);

        item->setIcon(0, QIcon(":/icons/database"));
        item->setTextColor(0, QColor(TreeTextColors::Color_Database));
        item->addChild(schemasItem);
    });

    rootItem->setIcon(0, QIcon(":/icons/databases"));
    rootItem->setBackground(0, getGradientBrush(QColor(224, 197, 143, 60),
                                                QColor(224, 197, 143, 0)));
}

void MainWindow::loadSchemasItems(QTreeWidgetItem* schemaItem)
{
    auto schemasList = pgView.getDatabaseSchemasList(schemaItem->parent()->text(0));

    auto tablesBkBrush = getGradientBrush(QColor(177, 222, 237, 60),
                                          QColor(177, 222, 237, 0));
    auto functionsBkBrush = getGradientBrush(QColor(209, 237, 177, 60),
                                             QColor(209, 237, 177, 0));

    makeBranchFromList(schemasList, schemaItem, [&tablesBkBrush, &functionsBkBrush](QTreeWidgetItem* item) {
        auto tablesItem = new QTreeWidgetItem();
        tablesItem->setText(0, "Tables");
        tablesItem->setIcon(0, QIcon(":/icons/tables"));
        tablesItem->setTextColor(0, QColor(TreeTextColors::Color_Table));
        tablesItem->setBackground(0, tablesBkBrush);

        auto functionsItem = new QTreeWidgetItem();
        functionsItem->setText(0, "Functions");
        functionsItem->setIcon(0, QIcon(":/icons/functions"));
        functionsItem->setTextColor(0, QColor(TreeTextColors::Color_Function));
        functionsItem->setBackground(0, functionsBkBrush);

        item->setIcon(0, QIcon(":/icons/schema"));
        item->setTextColor(0, QColor(TreeTextColors::Color_Schema));
        item->addChild(tablesItem);
        item->addChild(functionsItem);
    });
}

void MainWindow::loadTablesItems(QTreeWidgetItem* tablesItem)
{
    auto schemaItem = tablesItem->parent();
    auto databaseItem = schemaItem->parent()->parent();

    auto tablesList = pgView.getDatabaseSchemaTablesList(
                databaseItem->text(0), schemaItem->text(0));

    auto columnsBkBrush = getGradientBrush(QColor(177, 237, 190, 60),
                                           QColor(177, 237, 190, 0));

    makeBranchFromList(tablesList, tablesItem, [&columnsBkBrush](QTreeWidgetItem* item) {
        auto columnsItem = new QTreeWidgetItem();
        columnsItem->setText(0, "Columns");
        columnsItem->setIcon(0, QIcon(":/icons/columns"));
        columnsItem->setTextColor(0, QColor(TreeTextColors::Color_Column));
        columnsItem->setBackground(0, columnsBkBrush);


        item->setIcon(0, QIcon(":/icons/table"));
        item->setTextColor(0, QColor(TreeTextColors::Color_Table));
        item->addChild(columnsItem);
    });
}

void MainWindow::loadColumnsItems(QTreeWidgetItem* columnsItem)
{
    auto tableItem = columnsItem->parent();
    auto schemaItem = tableItem->parent()->parent();
    auto databaseItem = schemaItem->parent()->parent();

    auto columnsList = pgView.getDatabaseSchemaTableColumnsList(
            databaseItem->text(0), schemaItem->text(0), tableItem->text(0));

    makeBranchFromList(columnsList, columnsItem, [](QTreeWidgetItem* item) {
        item->setIcon(0, QIcon(":/icons/column"));
        item->setTextColor(0, QColor(TreeTextColors::Color_Column));
    });
}

void MainWindow::loadFunctionsItems(QTreeWidgetItem* functionItem)
{
    auto schemaItem = functionItem->parent();
    auto databaseItem = schemaItem->parent()->parent();

    auto functionsList = pgView.getDatabaseFunctionsList(
                databaseItem->text(0), schemaItem->text(0));

    makeBranchFromList(functionsList, functionItem, [=](QTreeWidgetItem* item) {
        auto parametersList = pgView.getDatabaseFunctionParametersList(
                    databaseItem->text(0), schemaItem->text(0), item->text(0));

        item->setIcon(0, QIcon(":/icons/function"));
        item->setTextColor(0, QColor(TreeTextColors::Color_Function));

        makeBranchFromList(parametersList, item, [](QTreeWidgetItem* item) {
            item->setIcon(0, QIcon(":/icons/function"));
            item->setTextColor(0, QColor(TreeTextColors::Color_Function));
        });
    });
}

QLinearGradient MainWindow::getGradientBrush(const QColor &beginColor, const QColor &endColor)
{
    QLinearGradient gradient(QPointF(0, 0), QPointF(1, 0));
    gradient.setColorAt(0.0, beginColor);
    gradient.setColorAt(1.0, endColor);
    gradient.setCoordinateMode(QGradient::ObjectBoundingMode);

    return gradient;
}

void MainWindow::on_actionSetConnectInfo_triggered()
{
    QDialog dialog;
    Ui_Dialog dialog_ui;
    dialog_ui.setupUi(&dialog);

    if ( dialog.exec() == QDialog::DialogCode::Accepted ) {
        QString url = dialog_ui.editHostUrl->text().length() == 0
                ? "localhost"
                : dialog_ui.editHostUrl->text();

        int port = dialog_ui.editPort->text().length() == 0
                ? 5432
                : dialog_ui.editPort->text().toInt();

        QString login = dialog_ui.editLogin->text().length() == 0
                ? "postgres"
                : dialog_ui.editLogin->text();

        QString password = dialog_ui.editPassword->text();

        QString db = dialog_ui.editDatabaseName->text().length() == 0
                ? "postgres"
                : dialog_ui.editDatabaseName->text();

        pgView.setConnectInfo(url, port, db, login, password);
    }
}

void MainWindow::on_actionClearTree_triggered()
{
    ui->dbTreeWidget->clear();
    makeRootItem();
}
