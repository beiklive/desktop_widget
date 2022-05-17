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
#include <QWebEngineView>
#include "sidebar.h"
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT


public:
    explicit MainWindow(QWidget *parent = nullptr);
    MainWindow* GetMe();
    void drawScale();
    void drawbody();
    void LeftmousePress(QMouseEvent* event);
    void RightmousePress(QMouseEvent* event);
    void setbrowser(QString url);
    void setIndex(int index){
        body_index = index;
    }
    int  getIndex(){
        return body_index;
    }
    //config====================
    void ChangeLock(bool Lock);
    ~MainWindow();

protected:
    virtual void resizeEvent(QResizeEvent *event) override;
    virtual void paintEvent(QPaintEvent *event) override;
    virtual void closeEvent(QCloseEvent *event) override;
protected:
    virtual void mousePressEvent(QMouseEvent* event) override;
    virtual void mouseMoveEvent(QMouseEvent* event) override;




private:
    Ui::MainWindow *ui;
    QMouseEvent *me;
    QPainter painter;
    QFont font;    //颜色
    QColor color;  //字体
    QPen pen;      //画笔
    QPoint last_mouse_position_;
    sidebar *bodybar = nullptr;
    QWebEngineView *view{nullptr};
    enum BODY_STATUS{
        NONE,
        BODY_LOCKED,
        BODY_RELEASE
    };

    //config=====================
    int isLock = BODY_RELEASE;
    int body_index;

};

#endif // MAINWINDOW_H
