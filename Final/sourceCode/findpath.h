#ifndef FINDPATH_H
#define FINDPATH_H

#include <QDialog>
#include <QTextBrowser>
#include <QPushButton>
#include <QLineEdit>
#include <findroad.h>
namespace Ui {
class Findpath;
}

class Findpath : public QDialog
{
    Q_OBJECT

public:
    explicit Findpath(QWidget *parent = nullptr);
    ~Findpath();

private slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();


signals:
    void sendsignal();
    void display(int path[10][81]);

private:

    Ui::Findpath *ui;
    QLineEdit *lineEdit;
    QLineEdit *lineEdit_2;
    QLineEdit *lineEdit_3;
};

#endif // FINDPATH_H
