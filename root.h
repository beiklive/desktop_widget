#ifndef ROOT_H
#define ROOT_H
#include <QDateTime>
#include <QDebug>
#define mylogtime() (QDateTime::currentDateTime().toString("[yyyy/MM/dd hh:mm:ss]"))
#define log(str) (qDebug().noquote() << mylogtime() << "[info]" << str)
#include <QWidget>
#include <QVector>
#include "body.h"
namespace Ui {
class root;
}

class root : public QWidget
{
    Q_OBJECT

public:
    explicit root(QWidget *parent = nullptr);
    void CreateBody();
    ~root();

private:
    Ui::root *ui;
    MainWindow *body{nullptr};
    QVector<MainWindow *> body_box;
};

#endif // ROOT_H
