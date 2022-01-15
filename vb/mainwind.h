
#ifndef MAINWIND_H
#define MAINWIND_H

#include <QDialog>
#include <QSqlQuery>
#include <QApplication>
#include <qdebug.h>
#include <QSqlDatabase>
#include <QSqlError>

namespace Ui {
class mainwind;
}

extern QSqlQuery query;

extern QString queryname;

class mainwind : public QDialog
{
    Q_OBJECT

public:
    explicit mainwind(QWidget *parent = nullptr);
    ~mainwind();
    QString queryName() const;
private slots:
    void okbottomClick();
    void addquery(const QString &queryname);
    int searchquery(const QString &queryname);

    //void on_pushButton_clicked();

private:
    Ui::mainwind *ui;
};

#endif // MAINWIND_H
