#include "dragbtn.h"

Dragbtn::Dragbtn(QWidget *parent):
    Parent(parent)
{

}

void Dragbtn::GetBody(QWidget *body)
{
    tempbody = body;
    if(tempbody == nullptr)
        return;
}

void Dragbtn::mousePressEvent(QMouseEvent *event)
{
    last_mouse_position_ = event->globalPos();
    log("[MainWindow::LeftmousePress] LeftmousePress");
}

void Dragbtn::mouseMoveEvent(QMouseEvent *event)
{
    if (!event->buttons().testFlag(Qt::LeftButton))
        return;
    const QPoint position = pos() + event->globalPos() - last_mouse_position_;
    Parent->move(position.x(), position.y());
    const QPoint delta = event->globalPos() - last_mouse_position_;
    auto bodySize = QSize(tempbody->width()+delta.x(), tempbody->height()+delta.y());
//    auto bodyPos = this->pos();
    tempbody->resize(bodySize);
//    resizeBtn->move(bodyPos.x()+bodySize.width()+5, bodyPos.y()+bodySize.height() + 5);
    last_mouse_position_ = event->globalPos();
}
