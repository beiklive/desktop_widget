#ifndef ROOT_H
#define ROOT_H
#include <QDateTime>
#include <QDebug>
#define mylogtime() (QDateTime::currentDateTime().toString("[yyyy/MM/dd hh:mm:ss]"))
#define log(str) (qDebug().noquote() << mylogtime() << "[info]" << str)
#include <QWidget>
#include <QVector>
#include<QMenu>
#include <qsystemtrayicon.h>
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
    void SysTrayIcon();
    ~root();

private:
    Ui::root *ui;
    MainWindow *body{nullptr};
    QSystemTrayIcon* mSysTrayIcon;
    QVector<MainWindow *> body_box;

    struct tray_config{
        bool isclock = false;
    }root_config;
};

#endif // ROOT_H
