#include "findpath.h"
#include "ui_findpath.h"
#include "mainwindow.h"
#include <QDebug>
#include <QValidator>
#include <iostream>
#include <QFile>
#include <findroad.h>
#include<QRegExpValidator>
using namespace std;

Findpath::Findpath(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Findpath)
{
    ui->setupUi(this);

    ui->lineEdit->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    ui->lineEdit->setText("0");
    ui->lineEdit->setValidator(new QIntValidator(0, 80, ui->lineEdit));
    ui->lineEdit_2->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    ui->lineEdit_2->setText("1");
    ui->lineEdit_2->setValidator(new QIntValidator(0, 80, ui->lineEdit_2));
    ui->textBrowser->setFontPointSize(14);
}

Findpath::~Findpath()
{
    delete ui;
}

void Findpath::on_pushButton_clicked()
{
   emit sendsignal();
    this->close();
}


void Findpath::on_pushButton_2_clicked()
{
    ui->textBrowser->clear();
    if(ui->lineEdit->text().isEmpty()||ui->lineEdit_2->text().isEmpty())return;

    int num_1=ui->lineEdit->text().toInt();
    int num_2 =ui->lineEdit_2->text().toInt();

    int path[81][81];

    QFile csvfile(":/data/roadMap.csv");
    if(csvfile.open(QIODevice::ReadOnly))
    cout<<"-----csvfile is opened-----"<<endl;
    else cout<<"-----open file fail-----"<<endl;

    QTextStream *out = new QTextStream(&csvfile);
    QStringList tmp = out->readAll().split("\n");
    for(int i=1;i<82;i++)
    {
        QStringList tmp1 = tmp.at(i).split(",");
        for(int j=1; j<82;j++)
           path[i-1][j-1]=tmp1[j].toInt();
    }
    csvfile.close();

    Graph G;
    G.FIND(path,num_1,num_2);

    QString r1,r2;


    for(int i=0;i<G.pathNum;i++)
    {
        r2.clear();
        for(int j=0;j<NUM;j++)
        {


            r1.setNum(G.resultPath[i][j]);
            r2.append(r1);

            if (G.resultPath[i][j]==num_2)
            {
                break;
            }
            r2.append("->");
        }
        ui->textBrowser->append(r2+'\n');
    }
    if(G.pathNum==0)ui->textBrowser->append("Don't find road!");

}
