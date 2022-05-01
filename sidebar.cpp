#include "sidebar.h"
#include "ui_sidebar.h"
#include <QRect>
sidebar::sidebar(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::sidebar)
{
    ui->setupUi(this);
    setWindowFlags(Qt::FramelessWindowHint);
    setAttribute(Qt::WA_TranslucentBackground);
    this->resize(20, 200);
}

void sidebar::init(QWidget *body)
{
    tempbody = body;
    if(tempbody == nullptr)
        return;
    log("body get");

    barappear();
}

void sidebar::barappear()
{

    auto bodySize = tempbody->size();
    auto bodyPos = tempbody->pos();

    QPropertyAnimation *Anima = new QPropertyAnimation(this,"pos");
    Anima->setDuration(500);
    Anima->setStartValue(QPoint(bodyPos.x()+bodySize.width()-10, bodyPos.y()));
    Anima->setEndValue(QPoint(bodyPos.x()+bodySize.width()+10, bodyPos.y()));
    Anima->setEasingCurve(QEasingCurve::InOutCubic);

    QPropertyAnimation *animation = new QPropertyAnimation(this, "windowOpacity");
    animation->setDuration(500);
    animation->setStartValue(0);
    animation->setEndValue(1);
    animation->setEasingCurve(QEasingCurve::InOutCubic);

    QParallelAnimationGroup* pParaTwo = new QParallelAnimationGroup(this);
    pParaTwo->addAnimation(Anima);
    pParaTwo->addAnimation(animation);
    pParaTwo->start();

    //    this->move(bodyPos.x()+bodySize.width()+10, bodyPos.y());
}

void sidebar::barhidden()
{
    auto bodySize = tempbody->size();
    auto bodyPos = tempbody->pos();

    QPropertyAnimation *Anima = new QPropertyAnimation(this,"pos");
    Anima->setDuration(500);
    Anima->setStartValue(QPoint(bodyPos.x()+bodySize.width()+10, bodyPos.y()));
    Anima->setEndValue(QPoint(bodyPos.x()+bodySize.width()-10, bodyPos.y()));
    Anima->setEasingCurve(QEasingCurve::InOutCubic);

    QPropertyAnimation *animation = new QPropertyAnimation(this, "windowOpacity");
    animation->setDuration(500);
    animation->setStartValue(1);
    animation->setEndValue(0);
    animation->setEasingCurve(QEasingCurve::InOutCubic);


    QParallelAnimationGroup* pParaTwo = new QParallelAnimationGroup(this);
    pParaTwo->addAnimation(Anima);
    pParaTwo->addAnimation(animation);
    pParaTwo->start();
    connect(pParaTwo, SIGNAL(finished()), this, SLOT(close()));
}

void sidebar::drawbody(){
    painter.begin(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setBrush(QBrush(QColor(214, 214, 214,200)));
//    painter.setPen(Qt::transparent);
    painter.setPen(QColor(161, 161, 161));
    QRect rect = this->rect();
    rect.setWidth(rect.width() - 1);
    rect.setHeight(rect.height() - 1);
    painter.drawRoundedRect(rect, 5, 5);
    painter.end();
}

bool sidebar::isclose()
{
    if(tempbody == nullptr){
        return true;
    }else{
        return false;
    }
}

sidebar::~sidebar()
{
    delete ui;
}

void sidebar::resizeEvent(QResizeEvent *event)
{

}

void sidebar::paintEvent(QPaintEvent *event)
{
    drawbody();
}

void sidebar::closeEvent(QCloseEvent *event)
{
    this->close();
    log("close");
    tempbody = nullptr;
}
