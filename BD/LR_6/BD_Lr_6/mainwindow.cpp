#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <src/ClassDataBaseConnectDialog/DataBaseConnectDialog.h>

#include <QtSql>
#include <QtCharts>
#include <QLineEdit>
#include <QPushButton>
#include <QGridLayout>
using namespace QtCharts;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui( new Ui::MainWindow ),
    _data( new QLineSeries() ),
    _chart( new QChart() ),
    _dbConnectDialog( new DataBaseConnectDialog() ),
    _axisX( new QDateTimeAxis() ),
    _axisY( new QValueAxis() )
{
    ui->setupUi(this);

    _area = new QAreaSeries(_data);
    _area->setUseOpenGL(true);

    QPen pen(QColor(109, 160, 255));
    pen.setWidth(3);
    _area->setPen(pen);

    QLinearGradient gradientBrush(QPointF(0, 0), QPointF(0, 1));
    gradientBrush.setColorAt(0.0, QColor(109, 177, 255, 255));
    gradientBrush.setColorAt(1.0, QColor(109, 177, 255, 64));
    gradientBrush.setCoordinateMode(QGradient::ObjectBoundingMode);
    _area->setBrush(gradientBrush);

    _chart->setTheme(QChart::ChartThemeDark);
    _chart->addSeries(_area);
    _chart->setTitle("Популярность игры");
    _chart->setTitleFont(QFont("Arial", 24, 700));

    makeAxisX();
    makeAxisY();

    _view = new QChartView(_chart);
    _view->setRenderHint(QPainter::Antialiasing);

    auto layout = new QGridLayout(ui->centralWidget);
    layout->addWidget(_view, 0, 0);
    layout->setSpacing(0);
    layout->setContentsMargins(0, 0, 0, 0);

}

MainWindow::~MainWindow()
{
    delete _axisX;
    delete _axisY;
    delete _area;
    delete _dbConnectDialog;
    delete _chart;
    delete _data;
    delete ui;
}


void MainWindow::makeAxisX()
{
    _axisX->setTitleText("Время");
    _axisX->setFormat("MMMM yyyy");
    _axisX->setTickCount(12);
    _axisX->setTitleFont(QFont("Arial", 12, 900));
    _chart->setAxisX(_axisX, _area);
}


void MainWindow::makeAxisY()
{
    _axisY->setTitleText("Популярность");
    _axisY->setTitleFont(QFont("Arial", 12, 900));
    _axisY->setLabelFormat("%i");
    _chart->setAxisY(_axisY, _area);
}


void MainWindow::on_action_connectToDB_triggered()
{
    _dbConnectDialog->exec();
    auto db = _dbConnectDialog->getDatabaseConnect();
    if ( db.isOpen() ) {
        _database = db;
        on_action_update_triggered();
    }
    else {
        ui->statusBar->showMessage("Не удалось подключиться к базе данных!", 5000);
    }
}

void MainWindow::on_action_update_triggered()
{
    QSqlQuery query(_database);
    if ( !query.exec("select * from public.\"Popular\" order by \"date\";") ) {
        ui->statusBar->showMessage("Не удалось загрузить данные из базы данных!", 5000);
        return;
    }

    QDateTimeAxis* axisX = dynamic_cast<QDateTimeAxis*>(_chart->axisX());
    QValueAxis* axisY = dynamic_cast<QValueAxis*>(_chart->axisY());

    axisY->setMin(0);
    axisY->setMax(1);
    _data->clear();

    QSqlRecord rec = query.record();
    while( query.next() ) {
        auto date = QDateTime(query.value(rec.indexOf("date")).toDate()).toMSecsSinceEpoch();
        auto popular = query.value(rec.indexOf("count")).toInt();

        if (popular > axisY->max()) {
            axisY->setMax(popular);
        }
        if (popular < axisY->min()) {
            axisY->setMin(popular);
        }
        _data->append( date, popular );
    }

    auto dataVector = _data->pointsVector();

    axisX->setRange(
        QDateTime::fromMSecsSinceEpoch(dataVector[0].x()),
        QDateTime::fromMSecsSinceEpoch(dataVector.last().x())
    );

    ui->statusBar->showMessage("Данные обновлены!", 5000);
}
