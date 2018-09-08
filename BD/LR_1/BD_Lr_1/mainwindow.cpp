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
    ui->centralWidget->setStyleSheet("QWidget { font-size: 24px; }");

    auto labelWithOperation = new QLabel();
    auto lineEdit = new CustomLineEdit(CustomLineEdit::EditType_Double);
    auto pushButton_sin = new QPushButton("Sin");
    auto pushButton_cos = new QPushButton("Cos");
    auto pushButton_tan = new QPushButton("Tan");
    auto pushButton_ctan = new QPushButton("CTan");
    auto pushButton_log = new QPushButton("Log");
    auto pushButton_exp = new QPushButton("Exp");
    auto pushButton_pow2 = new QPushButton("x^2");
    auto pushButton_pow = new QPushButton("x^y");
    auto pushButton_pi = new QPushButton("Pi");
    auto pushButton_sqrt = new QPushButton("Sqrt");
    auto pushButton_revers = new QPushButton("+/-");
    auto pushButton_dot = new QPushButton(".");
    auto pushButton_calculate = new QPushButton("=");
    auto pushButton_0 = new QPushButton("0");
    auto pushButton_1 = new QPushButton("1");
    auto pushButton_2 = new QPushButton("2");
    auto pushButton_3 = new QPushButton("3");
    auto pushButton_4 = new QPushButton("4");
    auto pushButton_5 = new QPushButton("5");
    auto pushButton_6 = new QPushButton("6");
    auto pushButton_7 = new QPushButton("7");
    auto pushButton_8 = new QPushButton("8");
    auto pushButton_9 = new QPushButton("9");
    auto pushButton_c = new QPushButton("c");
    auto pushButton_ce = new QPushButton("ce");
    auto pushButton_add = new QPushButton("+");
    auto pushButton_sub = new QPushButton("-");
    auto pushButton_mul = new QPushButton("*");
    auto pushButton_div = new QPushButton("/");

    int maxSize = 10000;
    pushButton_sin->setMaximumSize(maxSize, maxSize);
    pushButton_cos->setMaximumSize(maxSize, maxSize);
    pushButton_tan->setMaximumSize(maxSize, maxSize);
    pushButton_ctan->setMaximumSize(maxSize, maxSize);
    pushButton_log->setMaximumSize(maxSize, maxSize);
    pushButton_exp->setMaximumSize(maxSize, maxSize);
    pushButton_pow2->setMaximumSize(maxSize, maxSize);
    pushButton_pow->setMaximumSize(maxSize, maxSize);
    pushButton_pi->setMaximumSize(maxSize, maxSize);
    pushButton_sqrt->setMaximumSize(maxSize, maxSize);
    pushButton_revers->setMaximumSize(maxSize, maxSize);
    pushButton_dot->setMaximumSize(maxSize, maxSize);
    pushButton_calculate->setMaximumSize(maxSize, maxSize);
    pushButton_0->setMaximumSize(maxSize, maxSize);
    pushButton_1->setMaximumSize(maxSize, maxSize);
    pushButton_2->setMaximumSize(maxSize, maxSize);
    pushButton_3->setMaximumSize(maxSize, maxSize);
    pushButton_4->setMaximumSize(maxSize, maxSize);
    pushButton_5->setMaximumSize(maxSize, maxSize);
    pushButton_6->setMaximumSize(maxSize, maxSize);
    pushButton_7->setMaximumSize(maxSize, maxSize);
    pushButton_8->setMaximumSize(maxSize, maxSize);
    pushButton_9->setMaximumSize(maxSize, maxSize);
    pushButton_c->setMaximumSize(maxSize, maxSize);
    pushButton_ce->setMaximumSize(maxSize, maxSize);
    pushButton_add->setMaximumSize(maxSize, maxSize);
    pushButton_sub->setMaximumSize(maxSize, maxSize);
    pushButton_mul->setMaximumSize(maxSize, maxSize);
    pushButton_div->setMaximumSize(maxSize, maxSize);

    labelWithOperation->setAlignment(Qt::Alignment(Qt::AlignmentFlag::AlignRight | Qt::AlignmentFlag::AlignVCenter));

    auto layout = new QGridLayout();

    layout->addWidget(labelWithOperation, 0, 0, 1, 2);
    layout->addWidget(lineEdit, 0, 2, 1, 4);

    layout->addWidget(pushButton_sin, 1, 0);
    layout->addWidget(pushButton_cos, 1, 1);
    layout->addWidget(pushButton_tan, 2, 0);
    layout->addWidget(pushButton_ctan, 2, 1);
    layout->addWidget(pushButton_log, 3, 0);
    layout->addWidget(pushButton_exp, 3, 1);
    layout->addWidget(pushButton_pow, 4, 0);
    layout->addWidget(pushButton_pow2, 4, 1);
    layout->addWidget(pushButton_sqrt, 5, 0);
    layout->addWidget(pushButton_pi, 5, 1);

    layout->addWidget(pushButton_1, 1, 2);
    layout->addWidget(pushButton_2, 1, 3);
    layout->addWidget(pushButton_3, 1, 4);
    layout->addWidget(pushButton_4, 2, 2);
    layout->addWidget(pushButton_5, 2, 3);
    layout->addWidget(pushButton_6, 2, 4);
    layout->addWidget(pushButton_7, 3, 2);
    layout->addWidget(pushButton_8, 3, 3);
    layout->addWidget(pushButton_9, 3, 4);
    layout->addWidget(pushButton_revers, 4, 2);
    layout->addWidget(pushButton_0, 4, 3);
    layout->addWidget(pushButton_dot, 4, 4);

    layout->addWidget(pushButton_add, 1, 5);
    layout->addWidget(pushButton_sub, 2, 5);
    layout->addWidget(pushButton_mul, 3, 5);
    layout->addWidget(pushButton_div, 4, 5);

    layout->addWidget(pushButton_calculate, 5, 2, 1, 4);

    ui->centralWidget->setLayout(layout);

    QLocale locale;

    auto mathAdd = [=]() {
        task7_number = task7_number + locale.toDouble(lineEdit->text());
    };
    auto mathSub = [=]() {
        task7_number = task7_number - locale.toDouble(lineEdit->text());
    };
    auto mathMul = [=]() {
        task7_number = task7_number * locale.toDouble(lineEdit->text());
    };
    auto mathDiv = [=]() {
        task7_number = task7_number / locale.toDouble(lineEdit->text());
    };
    auto mathPow = [=]() {
        task7_number = pow(task7_number, locale.toDouble(lineEdit->text()));
    };

    auto validNumber = [lineEdit]() -> bool {
        return lineEdit->property("status") == 2;
    };
    auto calcLast = [=]() {
        if (task7_math == Null) {
            task7_number = locale.toDouble(lineEdit->text());
            return;
        }

        switch(task7_math) {
        case Add: mathAdd(); break;
        case Sub: mathSub(); break;
        case Mul: mathMul(); break;
        case Div: mathDiv(); break;
        case Pow: mathPow(); break;
        }

        task7_math = Null;
    };

    connect(pushButton_0, &QPushButton::clicked, this, [=](bool status) {
        lineEdit->insert("0");
    });
    connect(pushButton_1, &QPushButton::clicked, this, [=](bool status) {
        lineEdit->insert("1");
    });
    connect(pushButton_2, &QPushButton::clicked, this, [=](bool status) {
        lineEdit->insert("2");
    });
    connect(pushButton_3, &QPushButton::clicked, this, [=](bool status) {
        lineEdit->insert("3");
    });
    connect(pushButton_4, &QPushButton::clicked, this, [=](bool status) {
        lineEdit->insert("4");
    });
    connect(pushButton_5, &QPushButton::clicked, this, [=](bool status) {
        lineEdit->insert("5");
    });
    connect(pushButton_6, &QPushButton::clicked, this, [=](bool status) {
        lineEdit->insert("6");
    });
    connect(pushButton_7, &QPushButton::clicked, this, [=](bool status) {
        lineEdit->insert("7");
    });
    connect(pushButton_8, &QPushButton::clicked, this, [=](bool status) {
        lineEdit->insert("8");
    });
    connect(pushButton_9, &QPushButton::clicked, this, [=](bool status) {
        lineEdit->insert("9");
    });
    connect(pushButton_dot, &QPushButton::clicked, this, [=](bool status) {
        if (!validNumber()) return;
        lineEdit->insert(",");
    });
    connect(pushButton_revers, &QPushButton::clicked, this, [=](bool status) {
        if (!validNumber()) return;
        auto numStr = lineEdit->text();
        auto cursorPos = lineEdit->cursorPosition();

        lineEdit->setCursorPosition(0);
        if ( numStr[0] != '-' ) {
            lineEdit->insert("-");
        }
        else {
            lineEdit->del();
        }
        lineEdit->setCursorPosition(cursorPos);
    });


    connect(pushButton_add, &QPushButton::clicked, this, [=](bool status) {
        if (!validNumber()) return;

        calcLast();
        labelWithOperation->setText(locale.toString(task7_number, 'g', 16) + " + ");

        task7_math = Add;
        lineEdit->setText("");
    });
    connect(pushButton_sub, &QPushButton::clicked, this, [=](bool status) {
        if (!validNumber()) return;

        calcLast();
        labelWithOperation->setText(locale.toString(task7_number, 'g', 16) + " - ");

        task7_math = Sub;
        lineEdit->setText("");
    });
    connect(pushButton_mul, &QPushButton::clicked, this, [=](bool status) {
        if (!validNumber()) return;

        calcLast();
        labelWithOperation->setText(locale.toString(task7_number, 'g', 16) + " * ");

        task7_math = Mul;
        lineEdit->setText("");
    });
    connect(pushButton_div, &QPushButton::clicked, this, [=](bool status) {
        if (!validNumber()) return;

        calcLast();
        labelWithOperation->setText(locale.toString(task7_number, 'g', 16) + " / ");

        task7_math = Div;
        lineEdit->setText("");
    });
    connect(pushButton_pow, &QPushButton::clicked, this, [=](bool status) {
        if (!validNumber()) return;

        calcLast();
        labelWithOperation->setText(locale.toString(task7_number, 'g', 16) + " ^ ");

        task7_math = Pow;
        lineEdit->setText("");
    });


    connect(pushButton_sin, &QPushButton::clicked, this, [=](bool status) {
        if (!validNumber()) return;

        calcLast();
        labelWithOperation->setText(QString("Sin(%1) = ").arg(locale.toString(task7_number)));
        lineEdit->setText(locale.toString(sin(task7_number), 'g', 16));
    });
    connect(pushButton_cos, &QPushButton::clicked, this, [=](bool status) {
        if (!validNumber()) return;

        calcLast();
        labelWithOperation->setText(QString("Cos(%1) = ").arg(locale.toString(task7_number)));
        lineEdit->setText(locale.toString(cos(task7_number), 'g', 16));
    });
    connect(pushButton_tan, &QPushButton::clicked, this, [=](bool status) {
        if (!validNumber()) return;

        calcLast();
        labelWithOperation->setText(QString("Tan(%1) = ").arg(locale.toString(task7_number)));
        lineEdit->setText(locale.toString(tan(task7_number), 'g', 16));
    });
    connect(pushButton_ctan, &QPushButton::clicked, this, [=](bool status) {
        if (!validNumber()) return;

        calcLast();
        labelWithOperation->setText(QString("Ctan(%1) = ").arg(locale.toString(task7_number)));
        lineEdit->setText(locale.toString(1/tan(task7_number), 'g', 16));
    });
    connect(pushButton_log, &QPushButton::clicked, this, [=](bool status) {
        if (!validNumber()) return;

        calcLast();
        labelWithOperation->setText(QString("Log(%1) = ").arg(locale.toString(task7_number)));
        lineEdit->setText(locale.toString(log(task7_number), 'g', 16));
    });
    connect(pushButton_exp, &QPushButton::clicked, this, [=](bool status) {
        if (!validNumber()) return;

        calcLast();
        labelWithOperation->setText(QString("Exp(%1) = ").arg(locale.toString(task7_number)));
        lineEdit->setText(locale.toString(exp(task7_number), 'g', 16));
    });
    connect(pushButton_sqrt, &QPushButton::clicked, this, [=](bool status) {
        if (!validNumber()) return;

        calcLast();
        labelWithOperation->setText(QString("Sqrt(%1) = ").arg(locale.toString(task7_number)));
        lineEdit->setText(locale.toString(sqrt(task7_number), 'g', 16));
    });
    connect(pushButton_pow2, &QPushButton::clicked, this, [=](bool status) {
        if (!validNumber()) return;

        calcLast();
        labelWithOperation->setText(QString("%1 ^ 2 = ").arg(locale.toString(task7_number)));
        lineEdit->setText(locale.toString(task7_number * task7_number, 'g', 16));
    });
    connect(pushButton_pi, &QPushButton::clicked, this, [=](bool status) {
        lineEdit->setText(locale.toString(M_PI, 'g', 16));
    });


    connect(pushButton_calculate, &QPushButton::clicked, this, [=](bool status) {
        if (!validNumber()) return;

        calcLast();
        labelWithOperation->setText("");
        lineEdit->setText(locale.toString(task7_number, 'g', 16));
    });
}



MainWindow::~MainWindow()
{
    delete ui;
}
