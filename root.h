#ifndef ROOT_H
#define ROOT_H

#include <QWidget>
#include "body.h"
namespace Ui {
class root;
}

class root : public QWidget
{
    Q_OBJECT

public:
    explicit root(QWidget *parent = nullptr);
    ~root();

private:
    Ui::root *ui;
};

#endif // ROOT_H
