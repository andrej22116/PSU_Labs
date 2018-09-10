/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.11.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QVBoxLayout *verticalLayout_2;
    QSplitter *splitter;
    QWidget *dataWidget;
    QGridLayout *gridLayout_5;
    QGroupBox *group;
    QGridLayout *gridLayout_2;
    QTableWidget *dataTable;
    QWidget *controlWidget;
    QGridLayout *gridLayout_3;
    QGroupBox *groupRemove;
    QVBoxLayout *verticalLayout;
    QCheckBox *checkBoxConfirmation;
    QPushButton *buttonRemove;
    QGroupBox *groupLoadSave;
    QGridLayout *gridLayout;
    QRadioButton *radioButtonBin;
    QPushButton *buttonSave;
    QPushButton *buttonLoad;
    QRadioButton *radioButtonTxt;
    QSpacerItem *spacer;
    QGroupBox *groupAdd;
    QFormLayout *formLayout;
    QLabel *labelAddres;
    QLineEdit *lineEditFio;
    QLabel *labelBornDate;
    QLineEdit *lineEditBornDate;
    QLabel *labelGroup;
    QLineEdit *lineEditGroup;
    QLabel *labelNumber;
    QLineEdit *lineEditNumber;
    QLabel *labelAddres_2;
    QLineEdit *lineEditAddres;
    QPushButton *buttonAdd;
    QSpacerItem *verticalSpacer;
    QMenuBar *menuBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(1000, 600);
        MainWindow->setMinimumSize(QSize(1000, 600));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        centralWidget->setStyleSheet(QLatin1String("QWidget {\n"
"	font-size: 14px;\n"
"}\n"
"\n"
"QPushButton {\n"
"	font-style: inherit;\n"
"	font-size: 24px;\n"
"}"));
        verticalLayout_2 = new QVBoxLayout(centralWidget);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        splitter = new QSplitter(centralWidget);
        splitter->setObjectName(QStringLiteral("splitter"));
        splitter->setStyleSheet(QLatin1String("QSplitter::handle:horizontal {\n"
"	background-color: #aaa;\n"
"	border: 2 dashed gray;\n"
"}"));
        splitter->setLineWidth(1);
        splitter->setMidLineWidth(0);
        splitter->setOrientation(Qt::Horizontal);
        splitter->setOpaqueResize(true);
        splitter->setHandleWidth(5);
        splitter->setChildrenCollapsible(true);
        dataWidget = new QWidget(splitter);
        dataWidget->setObjectName(QStringLiteral("dataWidget"));
        gridLayout_5 = new QGridLayout(dataWidget);
        gridLayout_5->setSpacing(0);
        gridLayout_5->setContentsMargins(11, 11, 11, 11);
        gridLayout_5->setObjectName(QStringLiteral("gridLayout_5"));
        gridLayout_5->setContentsMargins(0, 0, 0, 0);
        group = new QGroupBox(dataWidget);
        group->setObjectName(QStringLiteral("group"));
        gridLayout_2 = new QGridLayout(group);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        gridLayout_2->setContentsMargins(9, 9, 9, 9);
        dataTable = new QTableWidget(group);
        if (dataTable->columnCount() < 5)
            dataTable->setColumnCount(5);
        QFont font;
        font.setPointSize(12);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        __qtablewidgetitem->setFont(font);
        dataTable->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        __qtablewidgetitem1->setFont(font);
        dataTable->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        __qtablewidgetitem2->setFont(font);
        dataTable->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        __qtablewidgetitem3->setFont(font);
        dataTable->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        __qtablewidgetitem4->setFont(font);
        dataTable->setHorizontalHeaderItem(4, __qtablewidgetitem4);
        dataTable->setObjectName(QStringLiteral("dataTable"));
        dataTable->setColumnCount(5);

        gridLayout_2->addWidget(dataTable, 0, 0, 1, 1);


        gridLayout_5->addWidget(group, 0, 0, 1, 1);

        splitter->addWidget(dataWidget);
        controlWidget = new QWidget(splitter);
        controlWidget->setObjectName(QStringLiteral("controlWidget"));
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(controlWidget->sizePolicy().hasHeightForWidth());
        controlWidget->setSizePolicy(sizePolicy);
        controlWidget->setMaximumSize(QSize(16777215, 16777215));
        gridLayout_3 = new QGridLayout(controlWidget);
        gridLayout_3->setSpacing(0);
        gridLayout_3->setContentsMargins(11, 11, 11, 11);
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        gridLayout_3->setContentsMargins(0, 0, 0, 0);
        groupRemove = new QGroupBox(controlWidget);
        groupRemove->setObjectName(QStringLiteral("groupRemove"));
        verticalLayout = new QVBoxLayout(groupRemove);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        checkBoxConfirmation = new QCheckBox(groupRemove);
        checkBoxConfirmation->setObjectName(QStringLiteral("checkBoxConfirmation"));

        verticalLayout->addWidget(checkBoxConfirmation);

        buttonRemove = new QPushButton(groupRemove);
        buttonRemove->setObjectName(QStringLiteral("buttonRemove"));
        QIcon icon;
        icon.addFile(QStringLiteral(":/images/icons/BD_Drop.png"), QSize(), QIcon::Normal, QIcon::Off);
        buttonRemove->setIcon(icon);
        buttonRemove->setIconSize(QSize(32, 32));

        verticalLayout->addWidget(buttonRemove);


        gridLayout_3->addWidget(groupRemove, 1, 0, 1, 1);

        groupLoadSave = new QGroupBox(controlWidget);
        groupLoadSave->setObjectName(QStringLiteral("groupLoadSave"));
        gridLayout = new QGridLayout(groupLoadSave);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        radioButtonBin = new QRadioButton(groupLoadSave);
        radioButtonBin->setObjectName(QStringLiteral("radioButtonBin"));
        QIcon icon1;
        icon1.addFile(QStringLiteral(":/images/icons/BD_Bin.png"), QSize(), QIcon::Normal, QIcon::Off);
        radioButtonBin->setIcon(icon1);
        radioButtonBin->setIconSize(QSize(32, 32));

        gridLayout->addWidget(radioButtonBin, 4, 0, 1, 1);

        buttonSave = new QPushButton(groupLoadSave);
        buttonSave->setObjectName(QStringLiteral("buttonSave"));
        QIcon icon2;
        icon2.addFile(QStringLiteral(":/images/icons/BD_Save.png"), QSize(), QIcon::Normal, QIcon::Off);
        buttonSave->setIcon(icon2);
        buttonSave->setIconSize(QSize(32, 32));

        gridLayout->addWidget(buttonSave, 4, 2, 1, 1);

        buttonLoad = new QPushButton(groupLoadSave);
        buttonLoad->setObjectName(QStringLiteral("buttonLoad"));
        QIcon icon3;
        icon3.addFile(QStringLiteral(":/images/icons/BD_Load.png"), QSize(), QIcon::Normal, QIcon::Off);
        buttonLoad->setIcon(icon3);
        buttonLoad->setIconSize(QSize(32, 32));
        buttonLoad->setAutoRepeatDelay(300);
        buttonLoad->setAutoRepeatInterval(100);
        buttonLoad->setAutoDefault(false);
        buttonLoad->setFlat(false);

        gridLayout->addWidget(buttonLoad, 2, 2, 1, 1);

        radioButtonTxt = new QRadioButton(groupLoadSave);
        radioButtonTxt->setObjectName(QStringLiteral("radioButtonTxt"));
        QIcon icon4;
        icon4.addFile(QStringLiteral(":/images/icons/BD_Txt.png"), QSize(), QIcon::Normal, QIcon::Off);
        radioButtonTxt->setIcon(icon4);
        radioButtonTxt->setIconSize(QSize(32, 32));

        gridLayout->addWidget(radioButtonTxt, 2, 0, 1, 1);

        spacer = new QSpacerItem(20, 20, QSizePolicy::Maximum, QSizePolicy::Minimum);

        gridLayout->addItem(spacer, 2, 1, 1, 1);


        gridLayout_3->addWidget(groupLoadSave, 2, 0, 1, 1);

        groupAdd = new QGroupBox(controlWidget);
        groupAdd->setObjectName(QStringLiteral("groupAdd"));
        groupAdd->setLayoutDirection(Qt::LeftToRight);
        formLayout = new QFormLayout(groupAdd);
        formLayout->setSpacing(6);
        formLayout->setContentsMargins(11, 11, 11, 11);
        formLayout->setObjectName(QStringLiteral("formLayout"));
        formLayout->setLabelAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        formLayout->setHorizontalSpacing(9);
        formLayout->setVerticalSpacing(6);
        formLayout->setContentsMargins(9, 9, 9, 9);
        labelAddres = new QLabel(groupAdd);
        labelAddres->setObjectName(QStringLiteral("labelAddres"));
        labelAddres->setTextFormat(Qt::AutoText);
        labelAddres->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        formLayout->setWidget(0, QFormLayout::LabelRole, labelAddres);

        lineEditFio = new QLineEdit(groupAdd);
        lineEditFio->setObjectName(QStringLiteral("lineEditFio"));

        formLayout->setWidget(0, QFormLayout::FieldRole, lineEditFio);

        labelBornDate = new QLabel(groupAdd);
        labelBornDate->setObjectName(QStringLiteral("labelBornDate"));

        formLayout->setWidget(1, QFormLayout::LabelRole, labelBornDate);

        lineEditBornDate = new QLineEdit(groupAdd);
        lineEditBornDate->setObjectName(QStringLiteral("lineEditBornDate"));

        formLayout->setWidget(1, QFormLayout::FieldRole, lineEditBornDate);

        labelGroup = new QLabel(groupAdd);
        labelGroup->setObjectName(QStringLiteral("labelGroup"));

        formLayout->setWidget(2, QFormLayout::LabelRole, labelGroup);

        lineEditGroup = new QLineEdit(groupAdd);
        lineEditGroup->setObjectName(QStringLiteral("lineEditGroup"));

        formLayout->setWidget(2, QFormLayout::FieldRole, lineEditGroup);

        labelNumber = new QLabel(groupAdd);
        labelNumber->setObjectName(QStringLiteral("labelNumber"));

        formLayout->setWidget(3, QFormLayout::LabelRole, labelNumber);

        lineEditNumber = new QLineEdit(groupAdd);
        lineEditNumber->setObjectName(QStringLiteral("lineEditNumber"));

        formLayout->setWidget(3, QFormLayout::FieldRole, lineEditNumber);

        labelAddres_2 = new QLabel(groupAdd);
        labelAddres_2->setObjectName(QStringLiteral("labelAddres_2"));

        formLayout->setWidget(4, QFormLayout::LabelRole, labelAddres_2);

        lineEditAddres = new QLineEdit(groupAdd);
        lineEditAddres->setObjectName(QStringLiteral("lineEditAddres"));

        formLayout->setWidget(4, QFormLayout::FieldRole, lineEditAddres);

        buttonAdd = new QPushButton(groupAdd);
        buttonAdd->setObjectName(QStringLiteral("buttonAdd"));
        QIcon icon5;
        icon5.addFile(QStringLiteral(":/images/icons/BD_Add.png"), QSize(), QIcon::Normal, QIcon::Off);
        buttonAdd->setIcon(icon5);
        buttonAdd->setIconSize(QSize(32, 32));
        buttonAdd->setCheckable(false);

        formLayout->setWidget(5, QFormLayout::SpanningRole, buttonAdd);


        gridLayout_3->addWidget(groupAdd, 0, 0, 1, 1);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_3->addItem(verticalSpacer, 3, 0, 1, 1);

        splitter->addWidget(controlWidget);

        verticalLayout_2->addWidget(splitter);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1000, 21));
        MainWindow->setMenuBar(menuBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        statusBar->setSizeGripEnabled(true);
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        buttonLoad->setDefault(false);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", nullptr));
        group->setTitle(QApplication::translate("MainWindow", "\320\224\320\260\320\275\320\275\321\213\320\265", nullptr));
        QTableWidgetItem *___qtablewidgetitem = dataTable->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QApplication::translate("MainWindow", "\320\244\320\230\320\236", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = dataTable->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QApplication::translate("MainWindow", "\320\224\320\260\321\202\320\260 \321\200\320\276\320\266\320\264\320\265\320\275\320\270\321\217", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = dataTable->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QApplication::translate("MainWindow", "\320\223\321\200\321\203\320\277\320\277\320\260", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = dataTable->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QApplication::translate("MainWindow", "\320\242\320\265\320\273\320\265\321\204\320\276\320\275", nullptr));
        QTableWidgetItem *___qtablewidgetitem4 = dataTable->horizontalHeaderItem(4);
        ___qtablewidgetitem4->setText(QApplication::translate("MainWindow", "\320\220\320\264\321\200\320\265\321\201", nullptr));
        groupRemove->setTitle(QApplication::translate("MainWindow", "\320\243\320\264\320\260\320\273\320\270\321\202\321\214 \320\262\321\213\320\264\320\265\320\273\320\265\320\275\320\275\321\203\321\216 \320\267\320\260\320\277\320\270\321\201\321\214", nullptr));
        checkBoxConfirmation->setText(QApplication::translate("MainWindow", "\320\237\320\276\320\264\321\202\320\262\320\265\321\200\320\266\320\264\320\260\321\202\321\214 \321\203\320\264\320\260\320\273\320\265\320\275\320\270\320\265", nullptr));
        buttonRemove->setText(QApplication::translate("MainWindow", "\320\243\320\264\320\260\320\273\320\270\321\202\321\214", nullptr));
        groupLoadSave->setTitle(QApplication::translate("MainWindow", "\320\227\320\260\320\263\321\200\321\203\320\267\320\270\321\202\321\214/\320\241\320\276\321\205\321\200\320\260\320\275\320\270\321\202\321\214 \320\261\320\260\320\267\321\203", nullptr));
        radioButtonBin->setText(QApplication::translate("MainWindow", ".bin", nullptr));
        buttonSave->setText(QApplication::translate("MainWindow", "\320\241\320\276\321\205\321\200\320\260\320\275\320\270\321\202\321\214", nullptr));
        buttonLoad->setText(QApplication::translate("MainWindow", "\320\227\320\260\320\263\321\200\321\203\320\267\320\270\321\202\321\214", nullptr));
        radioButtonTxt->setText(QApplication::translate("MainWindow", ".txt", nullptr));
        groupAdd->setTitle(QApplication::translate("MainWindow", "\320\224\320\276\320\261\320\260\320\262\320\273\320\265\320\275\320\270\320\265 \320\267\320\260\320\277\320\270\321\201\320\270", nullptr));
        labelAddres->setText(QApplication::translate("MainWindow", "\320\244\320\230\320\236", nullptr));
        labelBornDate->setText(QApplication::translate("MainWindow", "\320\224\320\260\321\202\320\260 \321\200\320\276\320\266\320\264\320\265\320\275\320\270\321\217", nullptr));
        lineEditBornDate->setInputMask(QString());
        labelGroup->setText(QApplication::translate("MainWindow", "\320\223\321\200\321\203\320\277\320\277\320\260", nullptr));
        labelNumber->setText(QApplication::translate("MainWindow", "\320\242\320\265\320\273\320\265\321\204\320\276\320\275", nullptr));
        lineEditNumber->setInputMask(QApplication::translate("MainWindow", "999-99-99", nullptr));
        labelAddres_2->setText(QApplication::translate("MainWindow", "\320\220\320\264\321\200\320\265\321\201", nullptr));
        buttonAdd->setText(QApplication::translate("MainWindow", "\320\224\320\276\320\261\320\260\320\262\320\270\321\202\321\214", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
