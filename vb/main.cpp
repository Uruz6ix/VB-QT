#include "dialog.h"
#include <QApplication>
#include <qdebug.h>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QTextCodec>
#include "func.h"
#include "mainwind.h"
#include "recite.h"
#include "searchnrecord.h"

//有任何问题都可以写在注释里，然后把自己备份的工程发群里，在群里说问题--dwy
//请组长看了之后分工一下每个人要完成的函数，我先睡了--dwy

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //QTextCodec::setCodecFortr(QTextCodec::codecForLocale());
    QSqlDatabase db=QSqlDatabase::addDatabase("QSQLITE");
    db.setHostName("vobo");
    db.setDatabaseName("qtDB.db");
    db.setUserName("dwy");
    db.setPassword("19880204");
    db.open();

    mainwind q;
    q.show();
    //Dialog w;
    //w.show();
    //qDebug() << queryname;
    return a.exec();
}
