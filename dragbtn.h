#ifndef DRAGBTN_H
#define DRAGBTN_H

#include "dpushbutton.h"

class Dragbtn : public DPushButton
{
public:
    Dragbtn(QWidget *parent = nullptr);
    void GetBody(QWidget* body);
protected:
    virtual void mousePressEvent(QMouseEvent* event) override;
    virtual void mouseMoveEvent(QMouseEvent* event) override;

private:
//    Ui::ResizeBtn *ui;
    QWidget *tempbody{nullptr};
    QWidget *Parent{nullptr};
    QPoint last_mouse_position_;

};

#endif // DRAGBTN_H
