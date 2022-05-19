#ifndef RESIZEBTN_H
#define RESIZEBTN_H

#include <QWidget>
#include <QResizeEvent>
#include <QMouseEvent>
#include <QEvent>
#include "dragbtn.h"
#include "dpushbutton.h"
#include <QPropertyAnimation>
#include <QParallelAnimationGroup>
#include <QPainter>
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
    void drawbody();
    // animation =============
    void barappear();
    void barhidden();


    ~ResizeBtn();

protected:
//    virtual void resizeEvent(QResizeEvent *event) override;
    virtual void paintEvent(QPaintEvent *event) override;
//    virtual void closeEvent(QCloseEvent *event) override;

//protected:
//    virtual void mousePressEvent(QMouseEvent* event) override;
//    virtual void mouseMoveEvent(QMouseEvent* event) override;

private:
    Ui::ResizeBtn *ui;
    QWidget *tempbody{nullptr};
    QPoint last_mouse_position_;
    Dragbtn *btn_resize{nullptr};


    QPainter painter;
    QFont font;
    QColor color;
    QPen pen;
};

#endif // RESIZEBTN_H
