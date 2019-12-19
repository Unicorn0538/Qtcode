#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "findpath.h"
#include <QDebug>
#include <QtSql/QSqlQuery>
#include <QtCharts/QChart>
#include <QtCharts/QChartView>
#include <QtCharts/QChartGlobal>
#include <QtCharts/QtCharts>
#include <QString>
#include <QChartView>
#include <QBarSet>
#include <QPercentBarSeries>
#include <QBarSet>
#include <QLegend>
#include <QBarCategoryAxis>
#include <QHorizontalStackedBarSeries>
QT_CHARTS_USE_NAMESPACE

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_2_clicked()
{
    this->hide();
    Findpath *f=new Findpath(this);
    connect(f, SIGNAL(sendsignal()),this,SLOT(reshow()));
    f->setWindowTitle("Find Route");
    f->show();
}


void MainWindow::on_pushButton_clicked()
{
    ui->graphicsView->clearMask();
    QBarSet *set0 = new QBarSet("payType_0");
    QBarSet *set1 = new QBarSet("payType_1");
    QBarSet *set2 = new QBarSet("payType_2");
    QBarSet *set3 = new QBarSet("payType_3");
    for(int i=7;i<14;i++)
    {
        QString strDay;
        strDay.append(QString::number(i));

        QString path;
        path.append( ":/data"+strDay+"/data/data"+strDay+"/payType.csv");

        QFile file(path);
        if(file.open(QIODevice::ReadOnly))cout<<"-----Open Success-----"<<endl;
        else cout<<"------Sorry, Open failed!------"<<endl;

        QTextStream *out = new QTextStream(&file);
        QStringList tmp = out->readAll().split("\n");
        QStringList tmp1 = tmp.at(1).split(",");

        *set0 << tmp1[0].toInt();
        *set1 << tmp1[1].toInt();
        *set2 << tmp1[2].toInt();
        *set3 << tmp1[3].toInt();
        file.close();
    }
    QHorizontalStackedBarSeries *series = new QHorizontalStackedBarSeries();
    series->append(set0);
    series->append(set1);
    series->append(set2);
    series->append(set3);

    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("Statistics of payment methods at subway stations");
    chart->setAnimationOptions(QChart::SeriesAnimations);

    QStringList categories;
    categories << "2019/1/7" << "2019/1/8" << "2019/1/9" << "2019/1/10" << "2019/1/11" << "2019/1/12"<<"2019/1/13";
    QBarCategoryAxis *axis = new QBarCategoryAxis();
    axis->append(categories);
    chart->createDefaultAxes();
    chart->setAxisY(axis, series);

    QFont font("",13,QFont::Bold);
    chart->setTitleFont(font);
    chart->legend()->setVisible(true);
    chart->legend()->setAlignment(Qt::AlignBottom);


    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
    chartView->resize(1220,610);

   QGraphicsScene *ccharts = new QGraphicsScene(this);
   ui->graphicsView->setScene(ccharts);
   ccharts->addWidget(chartView);
   ui->graphicsView->show();
}




void MainWindow::on_pushButton_4_clicked()
{
    ui->graphicsView->close();
   QString timeStep = ui->spinBox_2->text();
   QString stationID = ui->spinBox->text();
   QString startDay = ui->dateTimeEdit_2->sectionText(QDateEdit::DaySection);
   QString endDay = ui->dateTimeEdit->sectionText(QDateEdit::DaySection);
   QString startHour =ui->dateTimeEdit_2->sectionText(QDateEdit::HourSection);
   QString startMinuts =ui->dateTimeEdit_2->sectionText(QDateEdit::MinuteSection);
   QString endHour =ui->dateTimeEdit->sectionText(QDateEdit::HourSection);
   QString endMinuts =ui->dateTimeEdit->sectionText(QDateEdit::MinuteSection);
   //QDateTime time1 = ui->dateTimeEdit->D
   QSplineSeries *series_in = new QSplineSeries();
   QSplineSeries *series_out = new QSplineSeries();

   cout<<stationID.toStdString()<<endl;
   cout<<startHour.toStdString()<<":"<<startMinuts.toStdString()<<endl;
   int S = 1, E = 289, max1 = 0;

   QDateTime Time;
   for(int i=startDay.toInt(); i<=endDay.toInt();i++)
   {
       if(i == startDay.toInt())
           S = (startHour.toInt()*60+startMinuts.toInt())/5;
       cout<<"s:"<<S<<endl;
       if(i == endDay.toInt())
           E = (endHour.toInt()*60+endMinuts.toInt())/5;
       cout<<"E:"<<E<<endl;
       QString strDay;
       strDay.append(QString::number(i));

       QString path;
       path.append( ":/data"+strDay+"/data/data"+strDay+"/station"+stationID+"_in.csv");

       QFile file(path);
       if(file.open(QIODevice::ReadOnly))cout<<"-----Open Success-----"<<endl;
       else cout<<"------Sorry, Open failed!------"<<endl;

       QTextStream *out = new QTextStream(&file);
       QStringList tmp = out->readAll().split("\n");



       for(int j=S;j<E;j+=(timeStep.toInt()/5)) //i作为开始值要改变
       {
           Time.setDate(QDate(2019,01,i));
           Time.setTime(QTime((j-1)/12,(j-1)%12*5,0));
           //cout<<Time.<<" and "<<tmp[j].toInt()<<"     ";
           series_in->append(Time.toMSecsSinceEpoch(), tmp[j].toInt());
           if(max1<tmp[j].toInt())max1 = tmp[j].toInt();
       }
       cout<<endl;
       file.close();

       QString path1;
       path1.append( ":/data"+strDay+"/data/data"+strDay+"/station"+stationID+"_out.csv");

       QFile file1(path1);
       if(file1.open(QIODevice::ReadOnly))cout<<"-----Open Success-----"<<endl;
       else cout<<"------Sorry, Open failed!------"<<endl;

       QTextStream *out1 = new QTextStream(&file1);
       QStringList tmp1 = out1->readAll().split("\n");

       for(int j=S;j<E;j+=(timeStep.toInt()/5)) //i作为开始值要改变
       {
           Time.setDate(QDate(2019,01,i));
           Time.setTime(QTime((j-1)/12,(j-1)%12*5,0));
           series_out->append(Time.toMSecsSinceEpoch(), tmp1[j].toInt());
           if(max1<tmp1[j].toInt())max1 = tmp1[j].toInt();
       }

       file1.close();
   }

   QChart *chart = new QChart();
   chart->addSeries(series_in);
   chart->addSeries(series_out);
   chart->setTitle("Population in and out of subway station "+stationID);

   QFont font("",13,QFont::Bold);
   chart->setTitleFont(font);
   series_in->setName("Flow_in");
   series_out->setName("Flow_out");
   QDateTimeAxis *axisX = new QDateTimeAxis();
   axisX->setTickCount(15);
   axisX->setRange(QDateTime(),QDateTime());
   axisX->setFormat("MM-dd hh:mm");
   axisX->setLabelsAngle(60);
   axisX->setTitleText("Date");
   chart->addAxis(axisX, Qt::AlignBottom);


   series_in->attachAxis(axisX);

   QValueAxis *axisY = new QValueAxis;
   if(max1==0)axisY->setRange(0,100);
   else axisY->setRange(0,max1+10);
   axisY->setLabelFormat("%i");
   axisY->setTitleText("Population");
   chart->addAxis(axisY, Qt::AlignLeft);

   series_in->attachAxis(axisY);

   series_out->attachAxis(axisY);
   series_out->attachAxis(axisX);

   QChartView *chartView = new QChartView(chart);
   chartView->setRenderHint(QPainter::Antialiasing);
   chartView->resize(1220,610);
   chartView->setRenderHint(QPainter::Antialiasing);


   QGraphicsScene *ccharts = new QGraphicsScene(this);
   ui->graphicsView->setScene(ccharts);
   ccharts->addWidget(chartView);
   ui->graphicsView->show();
}
