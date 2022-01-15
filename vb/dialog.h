#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QApplication>
#include <qdebug.h>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = nullptr);
    ~Dialog();

private :
    Ui::Dialog *ui;
private slots:
    void bottom1Clicked();
    void bottom2Clicked();
    void bottom3Clicked();
    //int queryRowCount(QSqlQuery query);
};

#endif // DIALOG_H
