#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QRegExpValidator>
#include <QFile>
#include <QTextStream>
#include <QDataStream>
#include <QStringBuilder>

#include "src/ClassDateValidator/datevalidator.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    auto dialog = new DataBaseConnectDialog(this);
    dialog->exec();
    database = dialog->getDatabaseConnect();

    initValidators();
    initControls();
    initTable();
    initDialogs();
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::initValidators()
{
    nameValidator = new QRegExpValidator(QRegExp("^(\\D)+$"));
    dateValidator = new DateValidator('.');

    ui->lineEditFio->setValidator(nameValidator);
    ui->lineEditBornDate->setValidator(dateValidator);
}


void MainWindow::initControls()
{
    ui->checkBoxConfirmation->setCheckState(Qt::CheckState::Checked);
    ui->radioButtonTxt->setChecked(true);

    connect(ui->buttonAdd, &QPushButton::clicked, this, &MainWindow::onClick_buttonAdd);
    connect(ui->buttonRemove, &QPushButton::clicked, this, &MainWindow::onClick_buttonRem);
    connect(ui->buttonLoad, &QPushButton::clicked, this, &MainWindow::onClick_buttonLoad);
    connect(ui->buttonSave, &QPushButton::clicked, this, &MainWindow::onClick_buttonSave);
}


void MainWindow::initTable()
{
    ui->dataTable->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->dataTable->setSelectionBehavior(QAbstractItemView::SelectRows);
}


void MainWindow::initDialogs()
{
    removeQuestionDialog.setWindowTitle("Удадение записи");
    removeQuestionDialog.setInformativeText("Это действие нельзя отменить.");
    removeQuestionDialog.setStandardButtons(QMessageBox::StandardButton::Yes | QMessageBox::StandardButton::No);
    removeQuestionDialog.setDefaultButton(QMessageBox::StandardButton::No);
    removeQuestionDialog.setIcon(QMessageBox::Icon::Question);

    fileOpenDialog.setFileMode(QFileDialog::AnyFile);
    fileOpenDialog.setAcceptMode(QFileDialog::AcceptOpen);

    fileSaveDialog.setFileMode(QFileDialog::AnyFile);
    fileSaveDialog.setAcceptMode(QFileDialog::AcceptSave);
}


void MainWindow::onClick_buttonAdd()
{
    if ( !ui->lineEditFio->hasAcceptableInput() ) { return; }
    if ( !ui->lineEditBornDate->hasAcceptableInput() ) { return; }
    if ( !ui->lineEditNumber->hasAcceptableInput() ) { return; }
    if ( ui->lineEditGroup->text().length() == 0 ) { return; }
    if ( ui->lineEditAddres->text().length() == 0 ) { return; }

    addLineToTable(ui->lineEditFio->text(), ui->lineEditBornDate->text(),
                   ui->lineEditGroup->text(), ui->lineEditNumber->text(), ui->lineEditAddres->text());

    ui->lineEditFio->setText("");
    ui->lineEditBornDate->setText("");
    ui->lineEditGroup->setText("");
    ui->lineEditNumber->setText("");
    ui->lineEditAddres->setText("");

    ui->statusBar->showMessage("Запись успешно добавлена!", 5000);
}

void MainWindow::onClick_buttonRem()
{
    auto select = ui->dataTable->selectionModel();
    auto selectedRows = select->selectedRows();
    if ( selectedRows.empty() ) {
        ui->statusBar->showMessage("Не удалось удалить запись: Запись не выбрана!", 5000);
        return;
    }

    int lineSelected = selectedRows[0].row();
    bool canBeRemoved = true;

    if ( ui->checkBoxConfirmation->checkState() == Qt::CheckState::Checked ) {
        removeQuestionDialog.setText(QString("Вы действительно хотите удалить запись под номером %1?")
                                     .arg(lineSelected + 1));
        auto answer = removeQuestionDialog.exec();

        if ( answer == QMessageBox::No ) {
            ui->statusBar->showMessage("Не удалось удалить запись: Удаление отменено!", 5000);
            canBeRemoved = false;
        }
    }

    if ( canBeRemoved ) {
        removeLineFromTable(lineSelected);
        ui->statusBar->showMessage("Запись удалена!", 5000);
    }
}

void MainWindow::onClick_buttonLoad()
{
    if ( ui->radioButtonSql->isChecked() ) {
        if ( !database.isOpen() || !loadFromDataBase() ) {
            ui->statusBar->showMessage("Не удалось загрузить данные из базы данных.", 5000);
        }
        else {
            ui->statusBar->showMessage("Данные загружены из базы данных - " + database.databaseName(), 5000);
        }
    }
    else {
        fileOpenDialog.setAcceptMode(QFileDialog::AcceptOpen);
        fileOpenDialog.selectFile("");

        bool openTxtFile = ui->radioButtonTxt->isChecked();

        if ( openTxtFile ) {
            fileOpenDialog.setWindowTitle("Открытие текстового файла");
            fileOpenDialog.setNameFilter(tr("Text (*.txt)"));
        } else {
            fileOpenDialog.setWindowTitle("Открытие бинарного файла");
            fileOpenDialog.setNameFilter(tr("Binary (*.bin)"));
        }

        if ( !fileOpenDialog.exec() ) {
            ui->statusBar->showMessage("Загрузка данных из файла отменена.", 5000);
            return;
        }

        bool result = true;
        auto filePath = fileOpenDialog.selectedFiles()[0];

        if (ui->radioButtonTxt->isChecked()) {
            result = loadFromTxtFile(filePath);
        }
        else {
            result = loadFromBinaryFile(filePath);
        }

        if (result) {
            ui->statusBar->showMessage("Открыт файл - " + filePath, 5000);
        }
        else {
            ui->statusBar->showMessage("Не удалось загрузить файл - " + filePath, 5000);
        }
    }
}

void MainWindow::onClick_buttonSave()
{
    if ( ui->radioButtonSql->isChecked() ) {
        if ( !database.isOpen() || !saveToDataBase() ) {
            ui->statusBar->showMessage("Не удалось сохранить данные в базу данных.", 5000);
        }
        else {
            ui->statusBar->showMessage("Данные сохранены в базу данных - " + database.databaseName(), 5000);
        }
    }
    else {
        fileSaveDialog.selectFile("");
        bool openTxtFile = ui->radioButtonTxt->isChecked();

        if ( openTxtFile ) {
            fileSaveDialog.setWindowTitle("Сохранение текстового файла");
            fileSaveDialog.setNameFilter(tr("Text (*.txt)"));
        }
        else {
            fileSaveDialog.setWindowTitle("Сохранение бинарного файла");
            fileSaveDialog.setNameFilter(tr("Binary (*.bin)"));
        }

        if ( !fileSaveDialog.exec() ) {
            ui->statusBar->showMessage("Сохранение данных в файл отменена.", 5000);
            return;
        }

        auto filePath = fileSaveDialog.selectedFiles()[0];

        bool result = false;
        if (ui->radioButtonTxt->isChecked()) {
            result = saveToTxtFile(filePath);
        }
        else {
            result = saveToBinaryFile(filePath);
        }

        if ( result ) {
            ui->statusBar->showMessage(QString("Файл \"%1\" успешно сохранён!").arg(filePath), 5000);
        }
        else {
            ui->statusBar->showMessage("Не удалось сохранить файл - " + filePath, 5000);
        }
    }
}



void MainWindow::addLineToTable(const QString& fio, const QString& bornDate, const QString& group,
                                const QString& number, const QString& addres, size_t line) {
    ui->dataTable->insertRow(line);
    ui->dataTable->setItem(line, 0, new QTableWidgetItem(fio));
    ui->dataTable->setItem(line, 1, new QTableWidgetItem(bornDate));
    ui->dataTable->setItem(line, 2, new QTableWidgetItem(group));
    ui->dataTable->setItem(line, 3, new QTableWidgetItem(number));
    ui->dataTable->setItem(line, 4, new QTableWidgetItem(addres));
}

void MainWindow::removeLineFromTable(size_t line)
{
    ui->dataTable->removeRow(line);
}


bool MainWindow::saveToTxtFile(const QString& path)
{
    QFile file(path);
    if ( !file.open(QIODevice::WriteOnly) ) { return false; }

    QTextStream stream(&file);
    for ( int i = 0, count = ui->dataTable->rowCount(); i < count; i++ ) {
        stream << ui->dataTable->item(i, 0)->text() << "|"
               << ui->dataTable->item(i, 1)->text() << "|"
               << ui->dataTable->item(i, 2)->text() << "|"
               << ui->dataTable->item(i, 3)->text() << "|"
               << ui->dataTable->item(i, 4)->text() << endl;
    }

    file.close();

    return true;
}


bool MainWindow::loadFromTxtFile(const QString& path)
{
    QFile file(path);
    if ( !file.exists() || !file.open(QIODevice::ReadOnly) ) { return false; }

    QTextStream stream(&file);
    while ( !stream.atEnd() ) {
        auto list = stream.readLine().split("|");
        if ( list.size() != 5 ) {
            file.close();
            return false;
        }

        addLineToTable(list[0], list[1], list[2], list[3], list[4]);
    }

    file.close();

    return true;
}


bool MainWindow::saveToBinaryFile(const QString& path)
{
    QFile file(path);
    if ( !file.open(QIODevice::WriteOnly) ) { return false; }

    QDataStream stream(&file);
    for (int i = 0, count = ui->dataTable->rowCount(); i < count; i++) {
        stream << ui->dataTable->item(i, 0)->text()
               << ui->dataTable->item(i, 1)->text()
               << ui->dataTable->item(i, 2)->text()
               << ui->dataTable->item(i, 3)->text()
               << ui->dataTable->item(i, 4)->text();
    }

    file.close();

    return true;
}


bool MainWindow::loadFromBinaryFile(const QString& path)
{
    QFile file(path);
    if ( !file.exists() || !file.open(QIODevice::ReadOnly) ) { return false; }

    QDataStream stream(&file);
    QStringList list;
    QString string;
    while ( !stream.atEnd() ) {
        for ( int i = 0; i < 5; i++ )
        {
            stream >> string;
            list << string;
        }
        if ( list.size() != 5 ) {
            file.close();
            return false;
        }

        addLineToTable(list[0], list[1], list[2], list[3], list[4]);
        list.clear();
    }

    file.close();

    return true;
}

bool MainWindow::saveToDataBase()
{
    QSqlQuery query(database);
    query.setForwardOnly(true);

    QString queryString;
    for ( int i = 0, count = ui->dataTable->rowCount(); i < count; i++ ) {
        queryString += QString("select * from public.\"addStudent\"('%0', '%1', '%2', '%3', '%4'); ")
                .arg(ui->dataTable->item(i, 0)->text())
                .arg(ui->dataTable->item(i, 1)->text())
                .arg(ui->dataTable->item(i, 2)->text())
                .arg(ui->dataTable->item(i, 3)->text())
                .arg(ui->dataTable->item(i, 4)->text());
    }

    if ( !query.exec(queryString) )
    {
        ui->statusBar->showMessage("Проблемесы, йпта.", 5000);
        return false;
    }

    return true;
}

bool MainWindow::loadFromDataBase()
{
    QSqlQuery query(database);
    query.setForwardOnly(true);
    if ( !query.exec("select * from public.\"Students\"") )
    {
        ui->statusBar->showMessage("Проблемесы, йпта.", 5000);
        return false;
    }

    QSqlRecord rec = query.record();
    while ( query.next() ) {
        addLineToTable(
                query.value(rec.indexOf("fio")).toString(),
                query.value(rec.indexOf("date_born")).toString(),
                query.value(rec.indexOf("group")).toString(),
                query.value(rec.indexOf("number")).toString(),
                query.value(rec.indexOf("addres")).toString()
                );
    }

    return true;
}

