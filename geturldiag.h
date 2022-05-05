#ifndef GETURLDIAG_H
#define GETURLDIAG_H

#include <QDialog>
#include <QFileDialog>
#include <QPainter>
#include <QMessageBox>
namespace Ui {
class GetUrlDiag;
}

class GetUrlDiag : public QDialog
{
    Q_OBJECT

public:
    explicit GetUrlDiag(QWidget *parent = nullptr);
    void init();
    void setCheckable(int index);
    int GetType();
    QString GetUrl();
    void drawbody();
    ~GetUrlDiag();
protected:
//    virtual void resizeEvent(QResizeEvent *event) override;
    virtual void paintEvent(QPaintEvent *event) override;

//    virtual void closeEvent(QCloseEvent *event) override;
private slots:
    void on_webradio_clicked();

    void on_localradio_clicked();



    void on_toolButton_clicked();

    void on_Set_clicked();

    void on_Cancel_clicked();

private:
    Ui::GetUrlDiag *ui;
    enum typelist{
        WEBSITEURL = 0,
        LOCALHTMLURL
    };

    QPainter painter;
    QFont font;    //颜色
    QColor color;  //字体
    QPen pen;      //画笔
    int currentIndex;
    QString currentUrl;
};

#endif // GETURLDIAG_H
