#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QDateTime>
#include <QDebug>
#define mylogtime() (QDateTime::currentDateTime().toString("[yyyy/MM/dd hh:mm:ss]"))
#define log(str) (qDebug().noquote() << mylogtime() << "[info]" << str)

#include <QMainWindow>
#include <QPainter>
#include <QResizeEvent>
#include <QMouseEvent>
#include <QEvent>

#include "sidebar.h"
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT


public:
    explicit MainWindow(QWidget *parent = nullptr);
    QWidget* GetMe();
    void drawScale();
    void drawbody();
    void LeftmousePress(QMouseEvent* event);
    void RightmousePress(QMouseEvent* event);
    ~MainWindow();

protected:
    virtual void resizeEvent(QResizeEvent *event) override;
    virtual void paintEvent(QPaintEvent *event) override;
protected:
    void mousePressEvent(QMouseEvent* event);
    void mouseMoveEvent(QMouseEvent* event);
private:
    Ui::MainWindow *ui;
    QMouseEvent *me;
    QPainter painter;
    QFont font;    //颜色
    QColor color;  //字体
    QPen pen;      //画笔
    QPoint last_mouse_position_;

    sidebar *bodybar = nullptr;
};

#endif // MAINWINDOW_H
