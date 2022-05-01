#include "root.h"
#include "ui_root.h"

root::root(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::root)
{
    ui->setupUi(this);
}

root::~root()
{
    delete ui;
}
