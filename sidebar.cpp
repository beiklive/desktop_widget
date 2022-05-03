#include "sidebar.h"
#include "ui_sidebar.h"
#include <QRect>
sidebar::sidebar(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::sidebar)
{
    ui->setupUi(this);
    setWindowFlags(Qt::FramelessWindowHint | Qt::Tool | Qt::WindowStaysOnTopHint);
    setAttribute(Qt::WA_TranslucentBackground);
    this->resize(30, 200);
}

void sidebar::init(QWidget *body)
{
    tempbody = body;
    if(tempbody == nullptr)
        return;
    log("[sidebar::init] body get");

    barappear();
    SetBtn();
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
    painter.setBrush(QBrush(QColor(224, 224, 224,1)));
    painter.setPen(QColor(224, 224, 224, 1));
    QRect rect = this->rect();
    rect.setWidth(rect.width() - 1);
    rect.setHeight(rect.height() - 1);
    painter.drawRoundedRect(rect, 10, 10);
    painter.end();
}

void sidebar::SetBtn()
{
    QVBoxLayout* pvLayout = new QVBoxLayout();
    DPushButton *btn1 = new DPushButton();
    btn1->InitIcon("/res/btn/open.png");
    btn1->setToolTip("open new");
    btn1->Initscale(this->width(), this->width());
    pvLayout->addWidget(btn1);

    DPushButton *btn2 = new DPushButton();
    btn2->InitIcon("/res/btn/copy.png");
    btn2->setToolTip("copy this");
    btn2->Initscale(this->width(), this->width());
    pvLayout->addWidget(btn2);

    DPushButton *btn3 = new DPushButton();
    btn3->InitIcon("/res/btn/close.png");
    btn3->setToolTip("close this");
    btn3->Initscale(this->width(), this->width());
    pvLayout->addWidget(btn3);

    DPushButton *btn4 = new DPushButton();
    btn4->InitIcon("/res/btn/setting.png");
    btn4->setToolTip("setting");
    btn4->Initscale(this->width(), this->width());
    pvLayout->addWidget(btn4);

    DPushButton *btn5 = new DPushButton();
    btn5->InitIcon("/res/btn/lock.png");
    btn5->setToolTip("lock");
    btn5->Initscale(this->width(), this->width());
    pvLayout->addWidget(btn5);
    pvLayout->setContentsMargins(0,0,0,0);
    this->setLayout(pvLayout);
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
    log("[sidebar::closeEvent] close");
    tempbody = nullptr;
}
