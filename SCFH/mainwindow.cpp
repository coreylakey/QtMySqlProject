#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlError>
#include <QtSql>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setMaximumSize(400,600);
    this->setMinimumSize(400,400);

//Create Window / connections
    this->setWindowTitle("South Coast Family Harbor");

    QLabel *mysql = new QLabel("Database Info",this);
    mysql->setGeometry(QRect(20,20,300,30));
    dbUserLb = new QLabel("User",this);
    dbUserInput = new QLineEdit("root",this);
    dbPwdLb = new QLabel("Pwd",this);
    dbPwdInput = new QLineEdit("shoogadabob",this);
    dbUserLb->setGeometry(QRect(20,60,80,30));
    dbUserInput->setGeometry(QRect(100,60,200,30));
    dbPwdLb->setGeometry(QRect(20,100,80,30));
    dbPwdInput->setGeometry(QRect(100,100,200,30));
    dbPwdInput->setEchoMode(QLineEdit::Password);
    dbNameLb = new QLabel("DB Name",this);
    dbNameLb->setGeometry(QRect(20,140,200,30));
    dbNameInput = new QLineEdit("scfh",this);
    dbNameInput->setGeometry(QRect(100,140,200,30));
    dbAddressLb = new QLabel("DB Address",this);
    dbAddressLb->setGeometry(QRect(20,180,200,30));
    dbAddressInput = new QLineEdit("localhost",this);
    dbAddressInput->setGeometry(QRect(100,180,200,30));
    dbPortLb = new QLabel("DB Port",this);
    dbPortLb->setGeometry(QRect(20,220,200,30));
    dbPortInput = new QLineEdit("3306",this);
    dbPortInput->setGeometry(QRect(100,220,200,30));
    conBtn = new QPushButton("connect",this);
    quitBtn = new QPushButton("quit",this);
    conBtn->setGeometry(QRect(20,300,140,30));
    quitBtn->setGeometry(QRect(170,300,140,30));
    connect(conBtn,SIGNAL(clicked()),this,SLOT(connect_db()));
    connect(quitBtn,SIGNAL(clicked()),this,SLOT(close()));
    conStatuLb = new QLabel("Status: Not Connected ",this);
    conStatuLb->setGeometry(QRect(50,260,200,30));

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
    conBtn->setText("disconnect");
    disconnect(conBtn,SIGNAL(clicked()),this,SLOT(connect_db()));
    connect(conBtn,SIGNAL(clicked()),this,SLOT(connect_quit()));
    if(database.isOpen())
         QMessageBox::information(this,qApp->tr("Success"),qApp->tr("Successfully connected to database."),QMessageBox::Ok);

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
