#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    _pg_database(QSqlDatabase::addDatabase("QPSQL", "postgres"))
{
    ui->setupUi(this);

    if (!_pg_database.isValid()) {
        ui->statusBar->showMessage("[ERROR] QPSQL driver not found!");
        //ui->buttonConnect->setHidden(true);
    }

    ui->widgetConnectInfo->setHidden(true);

    auto selectionModel = ui->dbTreeWidget->selectionModel();
    connect(selectionModel, &QItemSelectionModel::selectionChanged, this, &MainWindow::on_dbTreeNodeSelected);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_buttonConnect_clicked()
{
    if (!connectToServer()) {
        ui->statusBar->showMessage("[ERROR] Cann't connect to this database!");
        return;
    }

    auto baseItem = new QTreeWidgetItem(ui->dbTreeWidget);
    baseItem->setText(0, QString("%1:%2").arg(ui->lineEditAddres->text()).arg(ui->lineEditPort->text()));
    ui->dbTreeWidget->addTopLevelItem(baseItem);

    QSqlQuery query(_pg_database);
    query.setForwardOnly(true);
    if (!query.exec("SELECT datname FROM pg_database WHERE datacl is NULL;")) {
        ui->statusBar->showMessage("[ERROR] Query \"Get list of databases\" return false!");
    }

    QSqlRecord rec = query.record();
    while ( query.next() ) {
        QString databaseName = query.value(rec.indexOf("datname")).toString();
        qDebug() << databaseName;
        if (databaseName == "postgres") { continue; }

        _databases[databaseName] = QSqlDatabase::addDatabase("QPSQL", databaseName);
        _databases[databaseName].setDatabaseName(databaseName);

        _databases[databaseName].setHostName(ui->lineEditAddres->text());
        _databases[databaseName].setPort(ui->lineEditPort->text().toInt());

        _databases[databaseName].setUserName(ui->lineEditLogin->text());
        _databases[databaseName].setPassword(ui->lineEditPassword->text());

        qDebug() << "Try connect to " << databaseName;

        if (!_databases[databaseName].open()) {
            ui->statusBar->showMessage("[ERROR] Cann't connect to " + databaseName, 5000);
            _databases.remove(databaseName);
            qDebug() << "Error!" << endl;
            continue;
        }

        qDebug() << "Connected!";

        auto databaseNameItem = new QTreeWidgetItem();
        databaseNameItem->setText(0, databaseName);

        baseItem->addChild(databaseNameItem);

        qDebug() << "Get table names!";
        QSqlQuery queryTables(_databases[databaseName]);
        queryTables.setForwardOnly(true);
        if (!queryTables.exec("SELECT table_name as name FROM information_schema.tables WHERE table_schema = 'public';")) {
            qDebug() << "Error!" << endl;
            continue;
        }

        while ( queryTables.next() ) {
            QString databaseTableName = queryTables.value(0).toString();

            auto databaseTableNameItem = new QTreeWidgetItem();
            databaseTableNameItem->setText(0, databaseTableName);

            databaseNameItem->addChild(databaseTableNameItem);
        }

        qDebug() << "Complate!" << endl;
    }
}

void MainWindow::on_buttonDisconnect_clicked()
{

}

void MainWindow::on_dbTreeNodeSelected(const QItemSelection& selected , const QItemSelection& deselected)
{
    auto item = ui->dbTreeWidget->currentItem();
    ui->statusBar->showMessage(item->text(0));
}

bool MainWindow::connectToServer()
{
    _pg_database.setDatabaseName("postgres");

    _pg_database.setHostName(ui->lineEditAddres->text());
    _pg_database.setPort(ui->lineEditPort->text().toInt());

    _pg_database.setUserName(ui->lineEditLogin->text());
    _pg_database.setPassword(ui->lineEditPassword->text());

    return _pg_database.open();
}
