#include "root.h"
#include "ui_root.h"
#pragma execution_character_set("utf-8")
root::root(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::root)
{
    ui->setupUi(this);
    log("[root::root] construct init");
    setWindowFlags(Qt::FramelessWindowHint | Qt::Tool | Qt::WindowStaysOnTopHint);
    setAttribute(Qt::WA_TranslucentBackground);
    SysTrayIcon();
    CreateBody();
    body_box[0]->setbrowser("D:/QT_Project/desktop_widget/res/html/index.html");
}

void root::CreateBody()
{
    log("[root::CreateBody] create new body");
    body = new MainWindow();
    body_box.append(body);
    body->show();
}

void root::SysTrayIcon()
{
    log("[root::SysTrayIcon] init mSysTrayIcon");
    mSysTrayIcon = new QSystemTrayIcon(this);
    QIcon icon = QIcon("://res/DDJ.png");
    mSysTrayIcon->setToolTip("desktop widget");
    mSysTrayIcon->setIcon(icon);
    mSysTrayIcon->show();

    auto m_menu = new QMenu(this);
    //  create a body
    auto m_action_create = new QAction(m_menu);
    m_action_create->setText("新建窗口");
    m_menu->addAction(m_action_create);


    // lock all widget body
    auto m_action_lock = new QAction(m_menu);
    m_action_lock->setCheckable(true);
    m_action_lock->setText("全部锁定");
    m_menu->addAction(m_action_lock);




    // Exit program
    auto m_action_exit = new QAction(m_menu);
    m_action_exit->setText("退出程序");
    m_menu->addAction(m_action_exit);

    // connect slots
    connect(m_action_create, &QAction::triggered, this,
            [this]{
                emit this->CreateBody();
            }
    );
    connect(m_action_lock, &QAction::triggered, this,
            [this,m_action_create]{
            root_config.isclock = (root_config.isclock == true? false:true);
            m_action_create->setDisabled(root_config.isclock);
            for(int i = 0; i < body_box.length(); i++){
                body_box[i]->ChangeLock(root_config.isclock);
            }
     });
    connect(m_action_exit, &QAction::triggered, this, &QApplication::quit);

    mSysTrayIcon->setContextMenu(m_menu);
}

root::~root()
{
    delete ui;
}
