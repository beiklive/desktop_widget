#include "root.h"
#include "ui_root.h"

root::root(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::root)
{
    ui->setupUi(this);
    log("root system start");
    setWindowFlags(Qt::FramelessWindowHint | Qt::Tool | Qt::WindowStaysOnTopHint);
    setAttribute(Qt::WA_TranslucentBackground);
    SysTrayIcon();
    CreateBody();
}

void root::CreateBody()
{
    log("enter CreateBody()");

    log("create new");
    body = new MainWindow();
    body_box.append(body);
    body->show();
}

void root::SysTrayIcon()
{
    log("init mSysTrayIcon");
    mSysTrayIcon = new QSystemTrayIcon(this);
    QIcon icon = QIcon("://res/DDJ.png");
    mSysTrayIcon->setToolTip("desktop widget");
    mSysTrayIcon->setIcon(icon);
    mSysTrayIcon->show();

    auto m_menu = new QMenu(this);
    //  create a body
    auto m_action_create = new QAction(m_menu);
    m_action_create->setText("Create");
    m_menu->addAction(m_action_create);


    // lock all widget body
    auto m_action_lock = new QAction(m_menu);
    m_action_lock->setCheckable(true);
    m_action_lock->setText("LockAll");
    m_menu->addAction(m_action_lock);




    // Exit program
    auto m_action_exit = new QAction(m_menu);
    m_action_exit->setText("Exit");
    m_menu->addAction(m_action_exit);

    connect(m_action_create, &QAction::triggered, this,
            [this]{
                emit this->CreateBody();
            }
    );
    connect(m_action_lock, &QAction::triggered, this,
            [this, m_action_lock,m_action_create]{
            root_config.isclock = (root_config.isclock == true? false:true);
            m_action_create->setDisabled(root_config.isclock);
            for (auto iter = body_box.begin(); iter != body_box.end(); iter++)
            {
                (*iter)->ChangeLock();
            }
     });
    connect(m_action_exit, &QAction::triggered, this, &QApplication::quit);

    mSysTrayIcon->setContextMenu(m_menu);
}

root::~root()
{
    delete ui;
}
