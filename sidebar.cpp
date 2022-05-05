#include "sidebar.h"
#include "ui_sidebar.h"
#include <QRect>
#include "body.h"
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
    DPushButton *buttonOpen = new DPushButton();
    buttonOpen->InitIcon("/res/btn/open.png");
    buttonOpen->setToolTip("open new");
    buttonOpen->Initscale(this->width(), this->width());
    pvLayout->addWidget(buttonOpen);

    DPushButton *buttonCopy = new DPushButton();
    buttonCopy->InitIcon("/res/btn/copy.png");
    buttonCopy->setToolTip("copy this");
    buttonCopy->Initscale(this->width(), this->width());
    pvLayout->addWidget(buttonCopy);

    DPushButton *buttonClose = new DPushButton();
    buttonClose->InitIcon("/res/btn/close.png");
    buttonClose->setToolTip("close this");
    buttonClose->Initscale(this->width(), this->width());
    pvLayout->addWidget(buttonClose);

    DPushButton *buttonSetting = new DPushButton();
    buttonSetting->InitIcon("/res/btn/setting.png");
    buttonSetting->setToolTip("setting");
    buttonSetting->Initscale(this->width(), this->width());
    pvLayout->addWidget(buttonSetting);

    DPushButton *buttonLock = new DPushButton();
    buttonLock->InitIcon("/res/btn/lock.png");
    buttonLock->setToolTip("lock");
    buttonLock->Initscale(this->width(), this->width());
    pvLayout->addWidget(buttonLock);
    pvLayout->setContentsMargins(0,0,0,0);
    this->setLayout(pvLayout);

    connect(buttonClose, &QPushButton::clicked, [this]{
        MainWindow *body = (MainWindow *)tempbody;
        body->close();
        this->close();
    });
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
