#include "mainwind.h"
#include "ui_mainwind.h"
#include "dialog.h"
#include <qdebug.h>

mainwind::mainwind(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::mainwind)
{
    ui->setupUi(this);
    connect(ui->pushButton,SIGNAL(clicked(bool)),this,SLOT(okbottomClick()));
}

mainwind::~mainwind()
{
    delete ui;
}
//需要添加槽函数绑定行为
//已解决
QString queryname;
QString mainwind::queryName() const{
    //QString queryname =ui->queryname->text();
    return ui->queryname->text();
}
void mainwind::okbottomClick(){
    //表存在时调用对应表，不存在时创建并调用。
    //已解决
    //需要补充：如果没有输入直接return
    //已解决
    queryname=queryName();
    if(queryname==NULL){
        return;
    }
    if(searchquery(queryname)){
       addquery(queryname);
       //qDebug()<< "创建";
    }

    //需要补充可以返回表名称至下一个界面的函数
    //↑↑尝试使用extern解决
    //2021-12-28 14:44
    Dialog *nextPage= new Dialog;
    nextPage->show();
    this->hide();
    //qDebug() << queryname;

}

void mainwind::addquery(const QString &queryname){
    //创建新表
    QSqlQuery query;
    QString createTableStr="create table ";
    createTableStr+=queryname;
    createTableStr+=" ( vocabulary varchar(40) primary, translation varchar(40), nominal varchar(40), faultNum int ) ";
    //单词在单词本中是唯一的，从左到右分别是单词、释义、词性和错误次数。
    query.exec(createTableStr);

}

int mainwind::searchquery(const QString &queryname){
    QSqlQuery query;
    query.exec(QString("select count(*) from sqlite_master where type='table' and name='%1'").arg(queryname));
    query.next();
    return query.value(0).toInt()==0;
}
