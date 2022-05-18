#include "body.h"
#include "ui_body.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowFlags(Qt::FramelessWindowHint | Qt::Tool);
    setWindowFlag(Qt::WindowStaysOnTopHint, true);
    setAttribute(Qt::WA_TranslucentBackground);
    log("[MainWindow::MainWindow] start up");
    resizeBtn = new ResizeBtn();
    resizeBtn->init(this->GetMe());
    resizeBtn->move(this->pos().x()+this->width()+5, this->pos().y()+this->height() + 5);
    resizeBtn->show();
}

MainWindow *MainWindow::GetMe()
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
    painter.setBrush(QBrush(QColor(224, 224, 224,30)));
    painter.setPen(QColor(224, 224, 224));
    QRect rect = this->rect();
    rect.setWidth(rect.width() - 1);
    rect.setHeight(rect.height() - 1);
    painter.drawRoundedRect(rect, 3, 3);
    painter.end();
}

void MainWindow::LeftmousePress(QMouseEvent* event)
{
    last_mouse_position_ = event->globalPos();
    log("[MainWindow::LeftmousePress] LeftmousePress");

}

void MainWindow::RightmousePress(QMouseEvent *event)
{
    log("[MainWindow::RightmousePress] RightmousePress");
    if(bodybar != nullptr && !bodybar->isclose()){
        log("[MainWindow::RightmousePress] remove sidebar");
        bodybar->barhidden();
    }else{
        delete bodybar;
        bodybar = nullptr;
        log("[MainWindow::RightmousePress] create sidebar");
        bodybar = new sidebar();
        bodybar->show();
        bodybar->init(GetMe());
    }

}

void MainWindow::setbrowser(QUrl url)
{
    view = new QWebEngineView(this);
    view->setUrl(url);
    view->page()->setBackgroundColor(QColor(0,0,0,0));
    view->setContentsMargins(5,5,5,5);
//    view->setContextMenuPolicy(Qt::NoContextMenu);
    this->setCentralWidget(view);
    view->setAttribute(Qt::WA_TransparentForMouseEvents, true);
}

void MainWindow::ChangeLock(bool Lock)
{
    isLock = (Lock)? BODY_LOCKED : BODY_RELEASE;

    log(QString("[MainWindow::ChangeLock] change clock to %1").arg(Lock));
    update();
    if(Lock){
//        this->setFixedSize(this->geometry().size());
        if(bodybar != nullptr && !bodybar->isclose()){
            log("[MainWindow::ChangeLock] remove sidebar");
            resizeBtn->hide();
            bodybar->barhidden();
            update();
        }
    }else{
        resizeBtn->show();
//        this->setFixedSize(QSize(9999999,9999999));

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
//    drawScale();
    log("[MainWindow::paintEvent] paintEvent");
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    this->resizeBtn->close();
    this->bodybar->close();
    this->close();
    log("[MainWindow::closeEvent] close");
}
void MainWindow::resizeEvent(QResizeEvent *event)
{

//    log(QString("w:%1, h:%2").arg(this->width()).arg(this->height()));
    if(bodybar != nullptr){
        auto bodySize = this->size();
        auto bodyPos = this->pos();

        bodybar->move(bodyPos.x()+bodySize.width()+10, bodyPos.y());
        resizeBtn->move(bodyPos.x()+bodySize.width()+5, bodyPos.y()+bodySize.height() + 5);
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
        auto bodySize = this->size();
        auto bodyPos = this->pos();
        if(bodybar != nullptr){


            bodybar->move(bodyPos.x()+bodySize.width()+10, bodyPos.y());

        }
        resizeBtn->move(bodyPos.x()+bodySize.width()+5, bodyPos.y()+bodySize.height() + 5);
        last_mouse_position_ = event->globalPos();
    }
}
