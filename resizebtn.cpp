#include "resizebtn.h"
#include "ui_resizebtn.h"
#include <QVBoxLayout>
ResizeBtn::ResizeBtn(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ResizeBtn)
{
    ui->setupUi(this);
    setWindowFlags(Qt::FramelessWindowHint | Qt::Tool | Qt::WindowStaysOnTopHint);
    setAttribute(Qt::WA_TranslucentBackground);
    this->resize(30, 30);

}

void ResizeBtn::init(QWidget *body)
{
    tempbody = body;
    if(tempbody == nullptr)
        return;
    QVBoxLayout* pvLayout = new QVBoxLayout();
    btn_resize = new Dragbtn(this);
    btn_resize->InitIcon("/res/btn/resize.png");

    btn_resize->setToolTip("resize this");
    btn_resize->Initscale(this->width(), this->width());
    pvLayout->addWidget(btn_resize);
    pvLayout->setContentsMargins(0,0,0,0);
    this->setLayout(pvLayout);
    btn_resize->GetBody(tempbody);
    setPos();
}

void ResizeBtn::setPos()
{
    if(tempbody == nullptr)
        return;
    this->move(tempbody->pos().x()+ tempbody->width() + 5,tempbody->pos().y()+ tempbody->height() + 5);
}

void ResizeBtn::drawbody()
{
    painter.begin(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setBrush(QBrush(QColor(224, 224, 224,30)));
    painter.setPen(QColor(224, 224, 224));
    QRect rect = this->rect();
    rect.setWidth(rect.width() - 1);
    rect.setHeight(rect.height() - 1);
    painter.drawRoundedRect(rect, 5, 5);
    painter.end();
}

void ResizeBtn::barappear()
{
    auto bodySize = tempbody->size();
    auto bodyPos = tempbody->pos();
    update();
    this->show();
    QPropertyAnimation *Anima = new QPropertyAnimation(this,"pos");
    Anima->setDuration(500);
    Anima->setStartValue(QPoint(bodyPos.x()+bodySize.width()-10, bodyPos.y()+bodySize.height() - 10));
    Anima->setEndValue(QPoint(bodyPos.x()+bodySize.width()+5, bodyPos.y()+bodySize.height()+5));
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
}

void ResizeBtn::barhidden()
{
    auto bodySize = tempbody->size();
    auto bodyPos = tempbody->pos();

    QPropertyAnimation *Anima = new QPropertyAnimation(this,"pos");
    Anima->setDuration(500);
    Anima->setStartValue(QPoint(bodyPos.x()+bodySize.width()+5, bodyPos.y()+bodySize.height()+5));
    Anima->setEndValue(QPoint(bodyPos.x()+bodySize.width()-10, bodyPos.y()+bodySize.height() - 10));
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

    connect(pParaTwo, SIGNAL(finished()), this, SLOT(hide()));
}

ResizeBtn::~ResizeBtn()
{
    delete ui;
}

void ResizeBtn::paintEvent(QPaintEvent *event)
{
drawbody();
}

//void ResizeBtn::mousePressEvent(QMouseEvent *event)
//{

//}

//void ResizeBtn::mouseMoveEvent(QMouseEvent *event)
//{

//}
