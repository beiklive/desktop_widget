#ifndef RESIZEBTN_H
#define RESIZEBTN_H

#include <QWidget>
#include "dpushbutton.h"
#include <QResizeEvent>
#include <QMouseEvent>
#include <QEvent>
namespace Ui {
class ResizeBtn;
}

class ResizeBtn : public QWidget
{
    Q_OBJECT

public:
    explicit ResizeBtn(QWidget *parent = nullptr);
    void init(QWidget *body);
    void setPos();
    ~ResizeBtn();

//protected:
//    virtual void resizeEvent(QResizeEvent *event) override;
//    virtual void paintEvent(QPaintEvent *event) override;
//    virtual void closeEvent(QCloseEvent *event) override;

protected:
    virtual void mousePressEvent(QMouseEvent* event) override;
    virtual void mouseMoveEvent(QMouseEvent* event) override;

private:
    Ui::ResizeBtn *ui;
    QWidget *tempbody{nullptr};
    QPoint last_mouse_position_;
};

#endif // RESIZEBTN_H
