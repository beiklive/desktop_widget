#ifndef SIDEBAR_H
#define SIDEBAR_H
#include <QDateTime>
#include <QDebug>
#define mylogtime() (QDateTime::currentDateTime().toString("[yyyy/MM/dd hh:mm:ss]"))
#define log(str) (qDebug().noquote() << mylogtime() << "[info]" << str)

#include <QWidget>
#include <QPainter>
#include <QResizeEvent>
#include <QMouseEvent>
#include <QEvent>
#include <QPropertyAnimation>
#include <QParallelAnimationGroup>
#include <QCloseEvent>
namespace Ui {
class sidebar;
}

class sidebar : public QWidget
{
    Q_OBJECT

public:
    explicit sidebar(QWidget *parent = nullptr);
    void init(QWidget *body);
    void barappear();
    void barhidden();
    void drawbody();
    bool isclose();

    ~sidebar();

protected:
    virtual void resizeEvent(QResizeEvent *event) override;
    virtual void paintEvent(QPaintEvent *event) override;
    virtual void closeEvent(QCloseEvent *event) override;
private:
    Ui::sidebar *ui;
    QWidget *tempbody{nullptr};
    QPainter painter;
    QFont font;    //颜色
    QColor color;  //字体
    QPen pen;      //画笔
};

#endif // SIDEBAR_H
