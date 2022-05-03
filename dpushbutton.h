#ifndef DPUSHBUTTON_H
#define DPUSHBUTTON_H
#include <QDateTime>
#include <QDebug>
#define mylogtime() (QDateTime::currentDateTime().toString("[yyyy/MM/dd hh:mm:ss]"))
#define log(str) (qDebug().noquote() << mylogtime() << "[info]" << str)
#include <QWidget>
#include <QEvent>
#include <QPushButton>
#include <QEnterEvent>
namespace Ui {
class DPushButton;
}

class DPushButton : public QPushButton
{
    Q_OBJECT
protected:
    virtual void enterEvent(QEnterEvent  *event);
    virtual void leaveEvent(QEvent *event);
public:
    explicit DPushButton(QPushButton *parent = nullptr);
    ~DPushButton();

    // init
    void DefaultInit();
    void InitIcon(QString IconUrl);
    void Initscale(int width = 30, int height = 30);


    // process
    QStringList splitbtnIconUrl(QString url);
private:
    Ui::DPushButton *ui;
    QString btnIconUrl{"none"};
};

#endif // DPUSHBUTTON_H
