#include "dpushbutton.h"
#include "ui_dpushbutton.h"

void DPushButton::enterEvent(QEnterEvent  *event)
{
    auto style = QString("border-image: url(%1);").arg(splitbtnIconUrl(btnIconUrl)[0] + "-hover." + splitbtnIconUrl(btnIconUrl)[1]);
    this->setStyleSheet(style);
    log("[DPushButton::enterEvent] style: " + style);
}

void DPushButton::leaveEvent(QEvent *event)
{
    auto style = QString("border-image: url(%1);").arg(splitbtnIconUrl(btnIconUrl)[0] + "." + splitbtnIconUrl(btnIconUrl)[1]);
    this->setStyleSheet(style);
    log("[DPushButton::leaveEvent] style: " + style);
}

DPushButton::DPushButton(QPushButton *parent) :
    QPushButton(parent),
    ui(new Ui::DPushButton)
{
    ui->setupUi(this);
    log("[DPushButton::DPushButton] constructor init");
    DefaultInit();
    update();
}

DPushButton::~DPushButton()
{
    delete ui;
}

void DPushButton::DefaultInit()
{
    this->autoFillBackground();
    Initscale(20, 20);

    InitIcon(":/res/btn/none.png");

//            InitIcon("D:/QT_Project/desktop_widget/res/btn/none.png");
}

void DPushButton::InitIcon(QString IconUrl)
{
    #ifdef QT_DEBUG
        btnIconUrl = "D:/QT_Project/desktop_widget" + IconUrl;
    #endif
    #ifdef QT_NO_DEBUG
        btnIconUrl = QCoreApplication::applicationDirPath() + IconUrl;
    #endif

    this->setStyleSheet(QString("border-image: url(%1)").arg(btnIconUrl));
    log("[DPushButton::InitIcon] set icon url : " + btnIconUrl);
}

void DPushButton::Initscale(int width, int height)
{
//    this->resize(width, height);
    this->setFixedSize(width, height);
    auto style = QString("color:gray;");
//    this->setStyleSheet(style);
    log(QString("[DPushButton::Initscale] setFixedSize w=%1 h = %2").arg(width).arg(height));
}

QStringList DPushButton::splitbtnIconUrl(QString url)
{
    auto list = url.split(".");
    if(list.size() > 2){
        QStringList tlist{"", list[list.size()-1]};
        for(int i = 1; i < list.size() - 2; --i){
            tlist[0] += list[i];
        }
        return tlist;
    }
    return list;
}
