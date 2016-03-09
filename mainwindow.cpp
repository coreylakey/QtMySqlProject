#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlError>
#include <QtSql>
//#include <QWidget>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setMaximumSize(365,550);
    this->setMinimumSize(365,550);

//Create Window / connections
    this->setWindowTitle("South Coast Family Harbor");


//Main Background Image
    QPixmap bkgnd("/home/corey/Desktop/SCFHCOPY/bg_tile.jpg");
    bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio);
    QPalette palette;
    palette.setBrush(QPalette::Background, bkgnd);
    this->setPalette(palette);

//Banner
    banner = new QLabel(this);
    QPixmap banner_pixmap("/home/corey/Desktop/SCFHCOPY/banner.png");
    banner->setPixmap(banner_pixmap);
    banner->setMinimumSize(180, 161);
    //banner->setAlignment(Qt::AlignBaseline);
    banner->setGeometry(QRect(100,10,0,0));


    QLabel *mysql = new QLabel("Database Info",this);
    mysql->setStyleSheet("QLabel {font : bold;}");
//  mysql->setStyleSheet("QLabel {background-color : yellow; color : green;}"); //this sets Qlabel colors.
    mysql->setGeometry(QRect(20,180,300,30));
    dbUserLb = new QLabel("User",this);
    dbUserLb->setStyleSheet("QLabel {font : bold;}");
//  dbUserLb->setStyleSheet("QLabel { background-color : yellow; color : green; }");
    dbUserInput = new QLineEdit("root",this);
    dbPwdLb = new QLabel("Pwd",this);
    dbPwdLb->setStyleSheet("QLabel {font : bold;}");
//  dbPwdLb->setStyleSheet("QLabel { background-color : yellow; color : green; }");
    dbPwdInput = new QLineEdit("shoogadabob",this);
    dbUserLb->setGeometry(QRect(40,220,80,30));
    dbUserInput->setGeometry(QRect(120,220,200,30));
    dbPwdLb->setGeometry(QRect(40,260,80,30));
    dbPwdInput->setGeometry(QRect(120,260,200,30));
    dbPwdInput->setEchoMode(QLineEdit::Password);
    dbNameLb = new QLabel("DB Name",this);
    dbNameLb->setStyleSheet("QLabel {font : bold;}");
//  dbNameLb->setStyleSheet("QLabel { background-color : yellow; color : green; }");
    dbNameLb->setGeometry(QRect(40,300,200,30));
    dbNameInput = new QLineEdit("scfh",this);
    dbNameInput->setGeometry(QRect(120,300,200,30));
    dbAddressLb = new QLabel("DB Address",this);
    dbAddressLb->setStyleSheet("QLabel {font : bold;}");
//  dbAddressLb->setStyleSheet("QLabel { background-color : yellow; color : green; }");
    dbAddressLb->setGeometry(QRect(40,340,200,30));
    dbAddressInput = new QLineEdit("localhost",this);
    dbAddressInput->setGeometry(QRect(120,340,200,30));
    dbPortLb = new QLabel("DB Port",this);
    dbPortLb->setStyleSheet("QLabel {font : bold;}");
//  dbPortLb->setStyleSheet("QLabel { background-color : yellow; color : green; }");
    dbPortLb->setGeometry(QRect(40,380,200,30));
    dbPortInput = new QLineEdit("3306",this);
    dbPortInput->setGeometry(QRect(120,380,200,30));
    conBtn = new QPushButton("Connect",this);
    quitBtn = new QPushButton("Quit",this);
    conBtn->setGeometry(QRect(40,480,140,30));
    quitBtn->setGeometry(QRect(190,480,140,30));
    connect(conBtn,SIGNAL(clicked()),this,SLOT(connect_db()));
    connect(quitBtn,SIGNAL(clicked()),this,SLOT(close()));
    conStatuLb = new QLabel("Status: Not Connected ",this);
    conStatuLb->setStyleSheet("QLabel {font : bold;}");
    conStatuLb->setStyleSheet("QLabel {font : bold;}");
//  conStatuLb->setStyleSheet("QLabel { background-color : yellow; color : green; }");
    conStatuLb->setGeometry(QRect(100,440,200,30));

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::connect_db()
{
    if(dbUserInput->text() == "" || dbPwdInput->text()==""||dbNameInput->text()=="")
    {
        QMessageBox::critical(this,qApp->tr("warning"),qApp->tr("Can't accept blank fields"),QMessageBox::Ok);
        return ;
    }
    if(database.isValid())
    {
        //If database has a valid driver already
        // (Do nothing. you're good)
    }
    else
    {
        database = QSqlDatabase::addDatabase("QMYSQL");
    }
    database.setDatabaseName(dbNameInput->text());
    database.setHostName(dbAddressInput->text());
    database.setPassword(dbPwdInput->text());
    database.setUserName(dbUserInput->text());
    database.setPort(dbPortInput->text().toInt());

    if(!database.open())
    {
        QMessageBox::warning(this,"warning","Can not connect to database ");
        return ;
    }

    dbUserInput->setEnabled(false);
    dbPwdInput->setEnabled(false);
    dbPortInput->setEnabled(false);
    dbNameInput->setEnabled(false);
    dbAddressInput->setEnabled(false);
    conStatuLb->setText("Status : Connecting to "+dbNameInput->text());
    conBtn->setText("Disconnect");
    disconnect(conBtn,SIGNAL(clicked()),this,SLOT(connect_db()));
    connect(conBtn,SIGNAL(clicked()),this,SLOT(connect_quit()));
    if(database.isOpen())
         QMessageBox::information(this,qApp->tr("Success"),qApp->tr("Successfully connected to database."),QMessageBox::Ok);
    this->hide();
    login.show();
    login.setWindowTitle(dbNameInput->text());
}
void MainWindow::connect_quit()
{
    database.close();
    disconnect(conBtn,SIGNAL(clicked()),this,SLOT(connect_quit()));
    conStatuLb->setText("Status: Not connected");

    dbUserInput->setEnabled(true);
    dbPwdInput->setEnabled(true);
    dbPortInput->setEnabled(true);
    dbNameInput->setEnabled(true);
    dbAddressInput->setEnabled(true);
    conBtn->setText("connect");
    connect(conBtn,SIGNAL(clicked()),this,SLOT(connect_db()));
    login.close();
}
