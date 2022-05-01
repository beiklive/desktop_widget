#include "root.h"
#include "ui_root.h"

root::root(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::root)
{
    ui->setupUi(this);
    setWindowFlags(Qt::FramelessWindowHint);
    setAttribute(Qt::WA_TranslucentBackground);

}

void root::CreateBody()
{
    log("enter CreateBody()");
    if(body != nullptr){
        log("do append");
        body_box.append(body);
    }
    log("create new");
    body = new MainWindow();
    body->show();
}

root::~root()
{
    delete ui;
}
