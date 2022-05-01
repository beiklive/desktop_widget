#include "body.h"
#include "ui_body.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowFlags(Qt::FramelessWindowHint | Qt::Tool | Qt::WindowStaysOnTopHint);
    setAttribute(Qt::WA_TranslucentBackground);
    log("start up");

}

QWidget *MainWindow::GetMe()
{
    return this;
}

void MainWindow::drawScale()
{
    int right = this->width();
    int bottom = this->height();

    int mspace = 10;
    auto VerStart = QPoint(mspace, mspace);
    auto VerFin = QPoint(mspace, bottom - mspace);

    auto HorStart = QPoint(mspace, mspace);
    auto HorFin = QPoint(right - mspace, mspace);
    painter.begin(this);
    color.setRgb(0,0,0);
    painter.setPen(color);
    font.setFamily("黑体");
    font.setPointSize(8);
    font.setItalic(true);//斜体
    painter.setFont(font);//设置字体
    painter.drawLine(VerStart, VerFin);
    painter.drawLine(VerFin, QPoint(VerFin.x()-5, VerFin.y()-5));
    painter.drawLine(VerFin, QPoint(VerFin.x()+5, VerFin.y()-5));

    painter.drawLine(HorStart, HorFin);
    painter.drawLine(HorFin, QPoint(HorFin.x()-5, HorFin.y()+5));
    painter.drawLine(HorFin, QPoint(HorFin.x()-5, HorFin.y()-5));

    painter.drawText(mspace, bottom/2,  QString::number(bottom)+"px");
    painter.drawText(right/2, mspace,   QString::number(right)+"px");
    painter.end();
}

void MainWindow::drawbody(){
    painter.begin(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setBrush(QBrush(QColor(214, 214, 214,100)));
//    painter.setPen(Qt::transparent);
    painter.setPen(QColor(161, 161, 161));
    QRect rect = this->rect();
    rect.setWidth(rect.width() - 1);
    rect.setHeight(rect.height() - 1);
    painter.drawRoundedRect(rect, 5, 5);
    painter.end();
}

void MainWindow::LeftmousePress(QMouseEvent* event)
{
    last_mouse_position_ = event->globalPos();
    log("LeftmousePress");

}

void MainWindow::RightmousePress(QMouseEvent *event)
{
    log("RightmousePress");
    if(bodybar != nullptr && !bodybar->isclose()){
        log("remove sidebar");
        bodybar->barhidden();
    }else{
        delete bodybar;
        bodybar = nullptr;
        log("create sidebar");
        bodybar = new sidebar();
        bodybar->show();
        bodybar->init(GetMe());
    }

}

void MainWindow::ChangeLock()
{
    isLock = (isLock == BODY_RELEASE)? BODY_LOCKED : BODY_RELEASE;
    log(QString("change clock to %1").arg(isLock));
    update();
    if(isLock){
        this->setFixedSize(this->geometry().size());
    }else{

        this->setFixedSize(QSize(9999999,9999999));
    }

}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::paintEvent(QPaintEvent *event){
    if(isLock == BODY_RELEASE){
        drawbody();
    }
    drawScale();
    log("paintEvent");
}
void MainWindow::resizeEvent(QResizeEvent *event)
{

//    log(QString("w:%1, h:%2").arg(this->width()).arg(this->height()));
    if(bodybar != nullptr){
        auto bodySize = this->size();
        auto bodyPos = this->pos();

        bodybar->move(bodyPos.x()+bodySize.width()+10, bodyPos.y());
    }
}

void MainWindow::mousePressEvent(QMouseEvent* event)
{
    if(isLock == BODY_RELEASE){
        switch(event->button()){
           case Qt::LeftButton:
                LeftmousePress(event);
                break;
           case Qt::RightButton:
                RightmousePress(event);
                break;
            default:{}
        }
    }
}

void MainWindow::mouseMoveEvent(QMouseEvent* event)
{
    if(isLock == BODY_RELEASE){
        if (!event->buttons().testFlag(Qt::LeftButton))
            return;
        const QPoint position = pos() + event->globalPos() - last_mouse_position_;
        move(position.x(), position.y());
        if(bodybar != nullptr){
            auto bodySize = this->size();
            auto bodyPos = this->pos();

            bodybar->move(bodyPos.x()+bodySize.width()+10, bodyPos.y());
        }
        last_mouse_position_ = event->globalPos();
    }
}
