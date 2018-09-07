#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "src/ClassCustomLineEdit/customlineedit.h"

#include <QLocale>
#include <QtMath>
#include <QLabel>
#include <QPushButton>
#include <QGridLayout>

#include <random>
#include <ctime>

#define TASK_7

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);



#ifdef TASK_2
    makeTask2();
#endif

#ifdef TASK_3
    makeTask3();
#endif

#ifdef TASK_4
    makeTask4();
#endif

#ifdef TASK_5
    makeTask5();
#endif

#ifdef TASK_6
    makeTask6();
#endif

#ifdef TASK_7
    makeTask7();
#endif
}

void MainWindow::makeTask2()
{
    srand(time(nullptr));
    task2_number = rand() % 100;

    auto customLineEdit = new CustomLineEdit(CustomLineEdit::EditType_Integer);
    auto pushButton = new QPushButton("Ответ");
    auto labelResult = new QLabel("Результат: ");

    customLineEdit->setToolTip(QString("Ответ: %1").arg(task2_number));

    auto layout = new QGridLayout();
    layout->addWidget(new QLabel("Введите число:"), 0, 0);
    layout->addWidget(customLineEdit, 0, 1);
    layout->addWidget(pushButton, 1, 0, 1, 2);
    layout->addWidget(labelResult, 2, 0, 1, 2);
    ui->centralWidget->setLayout(layout);

    auto onPushButtonSignal = [=](bool checked) {
        if (customLineEdit->property("status") < 2) {
            return;
        }

        if (customLineEdit->text().toInt() == task2_number) {
            task2_number = rand() % 100;

            labelResult->setText("Результат: ПРАВИЛЬНО!");
            customLineEdit->setToolTip(QString("Ответ: %1").arg(task2_number));
        }
        else {
            labelResult->setText("Результат: НЕПРАВИЛЬНО!");
        }
    };

    connect(pushButton, &QPushButton::clicked, this, onPushButtonSignal);
}


void MainWindow::makeTask3()
{
    auto customLineEdit = new CustomLineEdit(CustomLineEdit::EditType_Integer);
    auto pushButton = new QPushButton("Вычислить");
    auto labelResult = new QLabel("Результат: ");

    auto layout = new QGridLayout();
    layout->addWidget(new QLabel("Введите число:"), 0, 0);
    layout->addWidget(customLineEdit->setInterval(1, double((1 << 16) - 1)), 0, 1);
    layout->addWidget(pushButton, 1, 0, 1, 2);
    layout->addWidget(labelResult, 2, 0, 1, 2);
    ui->centralWidget->setLayout(layout);

    auto onPushButtonSignal = [=](bool checked) {
        if (customLineEdit->property("status") < 2) {
            return;
        }

        int n = customLineEdit->text().toInt();
        quint64 res = (n + 1) * n / 2;
        labelResult->setText(QString("Результат: %1").arg(res));
    };

    connect(pushButton, &QPushButton::clicked, this, onPushButtonSignal);
}


void MainWindow::makeTask4()
{
    auto customLineEdit = new CustomLineEdit(CustomLineEdit::EditType_Double);
    auto pushButton_abs = new QPushButton("Abs");
    auto pushButton_cint = new QPushButton("Cint");
    auto pushButton_fix = new QPushButton("Fix");
    auto pushButton_int = new QPushButton("Int");
    auto pushButton_sqr = new QPushButton("Sqr");
    auto labelResult = new QLabel("Результат: ");

    auto layout = new QGridLayout();
    layout->addWidget(new QLabel("Введите число:"), 0, 0, 1, 1);
    layout->addWidget(customLineEdit, 0, 1, 1, 4);

    layout->addWidget(pushButton_abs, 1, 0);
    layout->addWidget(pushButton_cint, 1, 1);
    layout->addWidget(pushButton_fix, 1, 2);
    layout->addWidget(pushButton_int, 1, 3);
    layout->addWidget(pushButton_sqr, 1, 4);

    layout->addWidget(labelResult, 2, 0, 1, 5);
    ui->centralWidget->setLayout(layout);

    connect(pushButton_abs, &QPushButton::clicked, this, [=](bool checked) {
        if (customLineEdit->property("status") < 2) {
            return;
        }

        QLocale locale;
        double number = locale.toDouble(customLineEdit->text());
        labelResult->setText(QString("Результат: %1").arg(qAbs(number)));
    });

    connect(pushButton_cint, &QPushButton::clicked, this, [=](bool checked) {
        if (customLineEdit->property("status") < 2) {
            return;
        }

        QLocale locale;
        double number = locale.toDouble(customLineEdit->text());
        labelResult->setText(QString("Результат: %1").arg(int(number)));
    });

    connect(pushButton_fix, &QPushButton::clicked, this, [=](bool checked) {
        if (customLineEdit->property("status") < 2) {
            return;
        }

        QLocale locale;
        double number = locale.toDouble(customLineEdit->text());
        labelResult->setText(QString("Результат: %1").arg(int(number + 0.5)));
    });

    connect(pushButton_int, &QPushButton::clicked, this, [=](bool checked) {
        if (customLineEdit->property("status") < 2) {
            return;
        }

        QLocale locale;
        double number = locale.toDouble(customLineEdit->text());
        labelResult->setText(QString("Результат: %1").arg(int(number) + 1));
    });

    connect(pushButton_sqr, &QPushButton::clicked, this, [=](bool checked) {
        if (customLineEdit->property("status") < 2) {
            return;
        }

        QLocale locale;
        double number = locale.toDouble(customLineEdit->text());
        labelResult->setText(QString("Результат: %1").arg(qSqrt(number)));
    });
}


void MainWindow::makeTask5()
{
    auto customLineEdit_width = new CustomLineEdit(CustomLineEdit::EditType_Double);
    auto customLineEdit_height = new CustomLineEdit(CustomLineEdit::EditType_Double);
    auto pushButton = new QPushButton("Вычислить");
    auto labelResult = new QLabel("Площадь: ");

    auto layout = new QGridLayout();
    layout->addWidget(new QLabel("Высота:"), 0, 0);
    layout->addWidget(customLineEdit_width->setInterval(0, double((1 << 16) - 1)), 0, 1);

    layout->addWidget(new QLabel("Ширина:"), 1, 0);
    layout->addWidget(customLineEdit_height->setInterval(0, double((1 << 16) - 1)), 1, 1);

    layout->addWidget(pushButton, 2, 0, 1, 2);
    layout->addWidget(labelResult, 3, 0, 1, 2);
    ui->centralWidget->setLayout(layout);

    auto onPushButtonSignal = [=](bool checked) {
        if ( (customLineEdit_width->property("status") < 2)
                && (customLineEdit_height->property("status") < 2) ) {
            return;
        }

        QLocale locale(QLocale::C);
        double width = locale.toDouble(customLineEdit_width->text());
        double height = locale.toDouble(customLineEdit_height->text());
        labelResult->setText(QString("Площадь: %1").arg(width * height, 0, 'g', 30));
    };

    connect(pushButton, &QPushButton::clicked, this, onPushButtonSignal);
}


void MainWindow::makeTask6()
{
    auto lineEdit = new CustomLineEdit();
    auto label = new QLabel("Длинна текста: 0");

    auto layout = new QGridLayout();

    layout->addWidget(new QLabel("Введите строку:"), 0, 0);
    layout->addWidget(lineEdit, 0, 1);
    layout->addWidget(label, 1, 0, 1, 2);

    ui->centralWidget->setLayout(layout);

    connect(lineEdit, &QLineEdit::textEdited, this, [=](const QString& text){
        label->setText(QString("Длинна текста: %1").arg(text.length()));
    });
}


void MainWindow::makeTask7()
{
    auto layout = new QGridLayout();

    ui->centralWidget->setLayout(layout);
}



MainWindow::~MainWindow()
{
    delete ui;
}
