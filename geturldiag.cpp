#include "geturldiag.h"
#include "ui_geturldiag.h"
#pragma execution_character_set("utf-8")
GetUrlDiag::GetUrlDiag(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::GetUrlDiag)
{
    ui->setupUi(this);

    init();
}

void GetUrlDiag::init()
{
    setWindowFlags(Qt::FramelessWindowHint | Qt::Tool);
    setWindowFlag(Qt::WindowStaysOnTopHint, true);
    setAttribute(Qt::WA_TranslucentBackground);
//    setAttribute(Qt::WA_DeleteOnClose);
    this->resize(320, 180);

    setCheckable(WEBSITEURL);
}

void GetUrlDiag::setCheckable(int index)
{
    currentIndex = index;
    // website url
    ui->webradio->setChecked(WEBSITEURL == currentIndex);
    ui->weblineEdit->setEnabled(WEBSITEURL == currentIndex);

    // local html
    ui->localradio->setChecked(LOCALHTMLURL == currentIndex);
    ui->locallineEdit->setEnabled(LOCALHTMLURL == currentIndex);
    ui->toolButton->setEnabled(LOCALHTMLURL == currentIndex);
}

int GetUrlDiag::GetType()
{
    return currentIndex;
}

QUrl GetUrlDiag::GetUrl()
{
    return currentUrl;
}

GetUrlDiag::~GetUrlDiag()
{
    delete ui;
}

void GetUrlDiag::paintEvent(QPaintEvent *event)
{
drawbody();
}

void GetUrlDiag::on_webradio_clicked()
{
    setCheckable(WEBSITEURL);
}


void GetUrlDiag::on_localradio_clicked()
{
    setCheckable(LOCALHTMLURL);
}

void GetUrlDiag::drawbody(){
    painter.begin(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setBrush(QBrush(QColor(224, 224, 224,190)));
    painter.setPen(QColor(224, 224, 224));
    QRect rect = this->rect();
    rect.setWidth(rect.width() - 1);
    rect.setHeight(rect.height() - 1);
    painter.drawRoundedRect(rect, 3, 3);
    painter.end();
}


void GetUrlDiag::on_toolButton_clicked()
{
    auto file_full = QFileDialog::getOpenFileName(this, tr("open html file"),QCoreApplication::applicationDirPath(), "html文件(*.html);;所有文件(*.*)");
    auto fileinfo = QFileInfo(file_full);
    auto file_path = fileinfo.absolutePath();
    //文件名
    auto file_name = fileinfo.fileName();
    //文件后缀
    auto file_suffix = fileinfo.suffix();
    ui->locallineEdit->setText(file_path+'/'+file_name);
}


void GetUrlDiag::on_Set_clicked()
{
    switch(currentIndex){
    case WEBSITEURL:{
        if(!ui->weblineEdit->text().isEmpty()){
            currentUrl = QUrl::fromPercentEncoding(ui->weblineEdit->text().toLocal8Bit());
        }else{
            QMessageBox::critical(this, "critical", "url is empty!");
        }
        break;
    }
    case LOCALHTMLURL:{
        if(!ui->locallineEdit->text().isEmpty()){
            currentUrl = QUrl::fromLocalFile(ui->locallineEdit->text());
        }else{
            QMessageBox::critical(this, "critical", "url is empty!");
        }
        break;
    }
    default:{}
    }
    done(Accepted);
}


void GetUrlDiag::on_Cancel_clicked()
{
    done(Rejected);
}

