#include "recite.h"
#include "ui_recite.h"
#include "searchnrecord.h"
#include "ui_searchnrecord.h"
#include "dialog.h"
#include "ui_dialog.h"
#include "recite.h"
#include "mainwind.h"
#include "QSqlQueryModel"
#include <QTimer>
#include <QString>
//int passnum = 0;


int recite::queryRowCount()
{
    QSqlQuery query;
    int initialPos = query.at();
    // Very strange but for no records .at() returns -2
    int pos = 0;
    if (query.last()){
        pos = query.at() + 1;
    }else{
        pos = 0;
    }
    // Important to restore initial pos
    query.seek(initialPos);
    return pos;
}


/*
QString getWord(){
    QString word;
    QSqlQuery query;
    //int i = getRandNum();
    word = query.exec("select * from student where id = 1");
    return word;
}*/



recite::~recite()
{
    delete ui;
}

//QSqlQuery query;

//需要补充：提取所有错误次数大于上方spinbox值的单词的函数
//已解决
//提取spinbox的函数
int recite::getSpinbox(){
    int i;
    i=ui->spinBox->value();
    return i;
}

//提取所有符合单词的函数
QList <voc> a;
int passNum;
void recite::getVoc(){
    QSqlQuery query;
    int leastNum=ui->spinBox->value();
    int i=0;
    query.exec(QString("select * from %1 where faultNum >= %2").arg(queryname).arg(leastNum));
    query.first();
    do{
        voc p;
        a<<p;
        a[i].position=i;
        a[i].faultNum=query.value(3).toInt();qDebug()<<i;
        a[i].vocabulary=query.value(0).toString();
        a[i].nomi=query.value(2).toString();
        a[i].tran=query.value(1).toString();
        i++;
        qDebug()<<a[0].faultNum;
    }while(query.next());
    std::random_shuffle(a.begin(),a.end());
    passNum=i;
    ui->textBrowser->setPlainText(a[0].vocabulary);


}
/*根据错误权值滚动（不一定权值，随机就行了）上述所有单词的函数，并判断输入值的正误，错了请把对应错误次数修改，绑定好！
请一定参考发在群里的文章！*/
//补充了一个用于管理的结构体在头文件，请查看
//我的建议是使用结构体数组实现
//↓↓这个不要了
int recite::getRandNum()
{
    srand((unsigned)time(NULL));
    return rand()%passNum;
}
//新代码
int passed=0;

void recite::shufflePut(){
    qDebug()<<(a[0].tran==ui->textEdit->toPlainText());
    qDebug()<<ui->textEdit->toPlainText()<<a[0].tran;
    if((a[0].tran==ui->textEdit->toPlainText())){
        ui->textBrowser_2->setPlainText("答对啦！");
    }//比较函数要换一下
    else{
        ui->textBrowser_2->setPlainText(QString("Oops，答错了，正确答案是：%1").arg(a[0].tran));
        a[0].faultNum++;
        QSqlQuery query;
        qDebug()<<a[0].faultNum;
        qDebug()<<query.exec(QString("update %1 set faultNum= %2 where vocabulary = '%3'").arg(queryname).arg(a[0].faultNum).arg(a[0].vocabulary));//存不进去
        qDebug()<<query.lastError();
    }
    a.removeFirst();
    passed++;
    if(!a.isEmpty()){
        ui->textBrowser->setPlainText(a[0].vocabulary);


    }
    else{
        ui->textBrowser->append("答完了！");
    }
}
//我把python代码贴在最后，是用文本显示的，逻辑很简单，大家可以参考一下来写：）

//可能需要添加一个能显示过完所有单词的函数，并绑定

//需要补充：两个可以绑定右侧LCD显示的函数
//用一个定时信号来更新显示





//返回上层界面的函数↓
//↑↑已解决
void recite::on_pushButton_3_clicked()//王梓宇添加的内容
{
    //passnum = 0;
    Dialog *nextPage=new Dialog;
    nextPage->show();
    this->close();
}

void recite::on_pushButton_2_clicked()
{
   // passnum++;
    QString answer=ui->textEdit->toPlainText();
    //if(answer != key){
    //faultnum++;
    //}
}

recite::recite(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::recite)
{
    ui->setupUi(this);
    connect(ui->pushButton,SIGNAL(clicked(bool)),this,SLOT(getVoc()));
    connect(ui->pushButton_2,SIGNAL(clicked(bool)),this,SLOT(shufflePut()));

    QTimer *pTimer=new QTimer();
    connect(pTimer, &QTimer::timeout, [=](){
        ui->lcdNumber->display(passed);
    });//这里是过词数量
    //ui->textBrowser->setText(getWord());
  connect(pTimer, &QTimer::timeout, [=](){
    ui->lcdNumber_2->display(passNum-passed);
    });    // ↑这里是剩余词数量   这里有bug 不懂
    pTimer->start(100);
    // 每100ms更新一次
//可以获取单词总数 然后根据时间做总数范围内的一个随机数，按照序号显示单词
}
