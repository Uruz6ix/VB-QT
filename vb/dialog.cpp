#include "dialog.h"
#include "ui_dialog.h"
#include "recite.h"
#include "searchnrecord.h"
#include "mainwind.h"
#include "QSqlQueryModel"
#include <QTimer>
Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    static QSqlQueryModel *model = new QSqlQueryModel(ui->tableView);
    //qDebug()<<queryname;
    model->setQuery(QString("select * from %1").arg(queryname));
    //model->setHeaderData(0,Qt::Horizontal,QObject::tr("编号"));
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("单词"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("释义"));
    ui->tableView->setModel(model);
    connect(ui->pushButton,SIGNAL(clicked(bool)),this,SLOT(bottom1Clicked()));
    connect(ui->pushButton_2,SIGNAL(clicked(bool)),this,SLOT(bottom2Clicked()));
    connect(ui->pushButton_3,SIGNAL(clicked(bool)),this,SLOT(bottom3Clicked()));
    QTimer *pTimer=new QTimer();

    connect(pTimer, &QTimer::timeout, [=](){
        int pos=model->rowCount();
        ui->lcdNumber->display(pos);
        //qDebug()<<pos;
    });//词总量

    pTimer->start(100); // 每100ms更新一次
}


Dialog::~Dialog()
{
    delete ui;
}



//需要补充：点击按钮1进入查找界面
//↑↑已解决

void Dialog:: bottom1Clicked(){
    searchnrecord *nextPage= new searchnrecord;
    nextPage->show();
    this->hide();
}

//需要补充：点击按钮2进入背诵界面
//↑↑已解决
void Dialog:: bottom2Clicked(){
    recite *nextPage=new recite;
    nextPage->show();
    this->hide();
}

//需要补充：点击按钮3返回上一个界面
//↑↑已解决
void Dialog:: bottom3Clicked(){
    mainwind *nextPage=new mainwind;
    nextPage->show();
    this->hide();
}
//需要补充：在右侧显示所有单词的tableview
//↑↑已解决
//记得绑定槽函数！
//↑↑已解决

//需要补充：绑定LCD灯与已有数据组数
//已解决
