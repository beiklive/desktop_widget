#include "sidebar.h"
#pragma execution_character_set("utf-8")
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
    DPushButton *btn_open = new DPushButton();
    btn_open->InitIcon("/res/btn/open.png");
    btn_open->setToolTip("open new");
    btn_open->Initscale(this->width(), this->width());
    pvLayout->addWidget(btn_open);

//    DPushButton *btn_copy = new DPushButton();
//    btn_copy->InitIcon("/res/btn/copy.png");
//    btn_copy->setToolTip("copy this");
//    btn_copy->Initscale(this->width(), this->width());
//    pvLayout->addWidget(btn_copy);

    DPushButton *btn_close = new DPushButton();
    btn_close->InitIcon("/res/btn/close.png");
    btn_close->setToolTip("close this");
    btn_close->Initscale(this->width(), this->width());
    pvLayout->addWidget(btn_close);

    DPushButton *btn_cfg = new DPushButton();
    btn_cfg->InitIcon("/res/btn/setting.png");
    btn_cfg->setToolTip("setting");
    btn_cfg->Initscale(this->width(), this->width());
    pvLayout->addWidget(btn_cfg);

    DPushButton *btn_lock = new DPushButton();
    btn_lock->InitIcon("/res/btn/lock.png");
    btn_lock->setToolTip("lock");
    btn_lock->Initscale(this->width(), this->width());
    pvLayout->addWidget(btn_lock);
    pvLayout->setContentsMargins(0,0,0,0);
    this->setLayout(pvLayout);

    connect(btn_open, &QPushButton::clicked, [this]{
        GetUrlDiag *dlgUrl = new GetUrlDiag();
        log("[sidebar::connect ] btn_open");
        if (dlgUrl->exec() == QDialog::Accepted){
            MainWindow *body = (MainWindow *)tempbody;
            auto url = dlgUrl->GetUrl();
            log("[sidebar::connect ] btn_open GetUrl:" + url);
            body->setbrowser(url);
        }
        delete dlgUrl;
    });


    connect(btn_close, &QPushButton::clicked, [this]{
        MainWindow *body = (MainWindow *)tempbody;
        log("[sidebar::connect ] btn_close");
        body->close();
    });

    connect(btn_lock, &QPushButton::clicked, [this]{
        MainWindow *body = (MainWindow *)tempbody;
        log("[sidebar::connect ] btn_close");
        body->ChangeLock(true);
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
