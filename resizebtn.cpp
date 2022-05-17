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
    QVBoxLayout* pvLayout = new QVBoxLayout();
    DPushButton *btn_resize = new DPushButton();
    btn_resize->InitIcon("/res/btn/resize.png");
    btn_resize->setToolTip("resize this");
    btn_resize->Initscale(this->width(), this->width());
    pvLayout->addWidget(btn_resize);
    pvLayout->setContentsMargins(0,0,0,0);
    this->setLayout(pvLayout);
}

void ResizeBtn::init(QWidget *body)
{
    tempbody = body;
    if(tempbody == nullptr)
        return;
    setPos();
}

void ResizeBtn::setPos()
{
    if(tempbody == nullptr)
        return;
    this->move(tempbody->pos().x()+ tempbody->width() + 5,tempbody->pos().y()+ tempbody->height() + 5);
}

ResizeBtn::~ResizeBtn()
{
    delete ui;
}

void ResizeBtn::mousePressEvent(QMouseEvent *event)
{
    last_mouse_position_ = event->globalPos();
    log("[MainWindow::LeftmousePress] LeftmousePress");
}

void ResizeBtn::mouseMoveEvent(QMouseEvent *event)
{
    if (!event->buttons().testFlag(Qt::LeftButton))
        return;
    const QPoint position = pos() + event->globalPos() - last_mouse_position_;
    move(position.x(), position.y());
    const QPoint delta = event->globalPos() - last_mouse_position_;
    auto bodySize = QSize(tempbody->width()+delta.x(), tempbody->height()+delta.y());
//    auto bodyPos = this->pos();
    tempbody->resize(bodySize);
//    resizeBtn->move(bodyPos.x()+bodySize.width()+5, bodyPos.y()+bodySize.height() + 5);
    last_mouse_position_ = event->globalPos();
}
