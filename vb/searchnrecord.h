#ifndef SEARCHNRECORD_H
#define SEARCHNRECORD_H

#include <QDialog>
#include <QApplication>
#include <qdebug.h>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>

namespace Ui {
class searchnrecord;
}

class searchnrecord : public QDialog
{
    Q_OBJECT

public:
    explicit searchnrecord(QWidget *parent = nullptr);
    ~searchnrecord();
private slots:
    void insertVoc();
    void searchVoc();

    void on_pushButton_3_clicked();//王梓宇添加的内容

private:
    Ui::searchnrecord *ui;
};

#endif // SEARCHNRECORD_H
