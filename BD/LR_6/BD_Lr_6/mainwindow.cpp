#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QtSql>
#include <QtCharts>
#include <QLineEdit>
#include <QPushButton>
#include <QGridLayout>
using namespace QtCharts;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    auto line_date = new QLineSeries();
    auto line_popular = new QLineSeries();

    *line_date << QPointF(0, 0)
               << QPointF(0, 0)
               << QPointF(0, 0)
               << QPointF(0, 0)
               << QPointF(0, 0)
               << QPointF(0, 0);
    *line_popular << QPointF(0, 0)
                  << QPointF(1, 5)
                  << QPointF(2, 10)
                  << QPointF(3, 50)
                  << QPointF(4, 25)
                  << QPointF(5, 0);

    auto areaSeries = new QAreaSeries(line_date, line_popular);
    QPen pen(0x427df4);
    pen.setWidth(3);
    areaSeries->setPen(pen);

    QLinearGradient gradientBrush(QPointF(0, 0), QPointF(0, 1));
    gradientBrush.setColorAt(0.0, 0x9ab5ed);
    gradientBrush.setColorAt(1.0, 0x6798fc);
    gradientBrush.setCoordinateMode(QGradient::ObjectBoundingMode);
    areaSeries->setBrush(gradientBrush);

    auto chart = new QChart();
    chart->addSeries(areaSeries);
    chart->setTitle("Популярность игры");
    chart->createDefaultAxes();
    chart->axisX()->setTitleText("Время");
    chart->axisY()->setTitleText("Популярность");

    auto chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    auto editPopular = new QLineEdit();
    auto editDate = new QLineEdit();
    auto pushButtonAdd = new QPushButton();

    auto layout = new QGridLayout(ui->centralWidget);
    layout->addWidget(chartView, 0, 0, 3, 1);
    layout->addWidget(editDate, 0, 1);
    layout->addWidget(editPopular, 1, 1);
    layout->addWidget(pushButtonAdd, 2, 1);

    connect(pushButtonAdd, &QPushButton::clicked, this, [=](){
        *line_date << QPointF(editDate->text().toInt(), 0);
        *line_popular << QPointF(editDate->text().toInt(), editPopular->text().toInt());
    });
}

MainWindow::~MainWindow()
{
    delete ui;
}
