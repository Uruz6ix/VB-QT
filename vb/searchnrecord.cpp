#include "searchnrecord.h"
#include "ui_searchnrecord.h"
#include "dialog.h"
#include "ui_dialog.h"
#include "recite.h"
#include "mainwind.h"
#include "QSqlQueryModel"


searchnrecord::searchnrecord(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::searchnrecord)
{
    ui->setupUi(this);
    connect(ui->pushButton_2,SIGNAL(clicked(bool)),this,SLOT(insertVoc()));
    connect(ui->pushButton,SIGNAL(clicked(bool)),this,SLOT(searchVoc()));
}

searchnrecord::~searchnrecord()
{
    delete ui;
}


//需要补充，根据输入返回释义到文本框的函数，绑定按钮
//↑↑已解决
void searchnrecord:: searchVoc(){
    QString voc=ui->textEdit->toPlainText();
    QSqlQuery query;
    query.exec(QString("select * from %1 where vocabulary = \"%2\"").arg(queryname).arg(voc));
    QSqlQueryModel *model = new QSqlQueryModel(ui->tableView);


            model->setQuery(query);
            ui->tableView->setModel(model);


        //to 杨一婵：要把tableview拉大一点--dwy


}

//↑↑可能需要补充一个删除按钮用来删除单词


//需要补充：根据输入值将新单词插入对应表，绑定按钮
//↑↑已解决
void searchnrecord:: insertVoc(){
    QString voc=ui->textEdit_2->toPlainText();
    QString trans=ui->textEdit_3->toPlainText();
    QString nom=ui->textEdit_4->toPlainText();
    int faultNum=0;
    if(voc!=NULL&&trans!=NULL&&nom!=NULL){
        QSqlQuery query;
        if(query.exec(QString("INSERT INTO %1 VALUES (\"%2\",\"%3\",\"%4\",%5)").arg(queryname).arg(voc).arg(trans).arg(nom).arg(faultNum))){
            ui->label_3->setText("成功！");
        }
        else{
            ui->label_3->setText("失败啦！");
        }
        return;
    }
    else
        return;
}
//插入的语法拍照我发到群里，QString拼接参照mainwind.cpp里addquery函数
//需要sql语句

//需要补充：依旧是一个返回上一个界面的按钮
//已解决
void searchnrecord::on_pushButton_3_clicked()
{
    Dialog *nextPage=new Dialog;
    nextPage->show();
    this->hide();
}
