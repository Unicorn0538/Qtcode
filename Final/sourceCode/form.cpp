#include "form.h"
#include "ui_form.h"
#include <QPixmap>

#include <QPalette>

#include <QBitmap>
Form::Form(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Form)
{
    ui->setupUi(this);
    setWindowFlags(Qt::FramelessWindowHint|Qt::WindowMinimizeButtonHint);
    QPixmap bgImage(":/image/7957b9be84c844c.jpg");
    QPalette bgPalette = this->palette();
    bgPalette.setBrush(QPalette::Background,bgImage);
    this->setPalette(bgPalette);
}

Form::~Form()
{
    delete ui;
}
