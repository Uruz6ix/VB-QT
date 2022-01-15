#ifndef RECITE_H
#define RECITE_H

#include <QDialog>
#include <QApplication>
#include <qdebug.h>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>

typedef struct vocabu{
    int position;//单词编号，请用query.at()获取
    int faultNum;
    QString vocabulary;
    QString nomi;
    QString tran;
}voc;//用于管理的结构体。

namespace Ui {
class recite;
}
extern QSqlQuery query;
class recite : public QDialog
{
    Q_OBJECT

public:
    explicit recite(QWidget *parent = nullptr);
    ~recite();


private slots:
    void on_pushButton_3_clicked();
    void on_pushButton_2_clicked();
    int getSpinbox();
    void getVoc();
    int queryRowCount();
    int getRandNum();
    void shufflePut();
private:
    Ui::recite *ui;

};

#endif // RECITE_H
