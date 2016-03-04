#include "dialog.h"
#include "ui_dialog.h"
#include <QMessageBox>
#include <QPushButton>
#include <QSqlTableModel>
#include <QSqlQuery>
#include <QDebug>
#include <QSqlDatabase>
#include <QSqlRecord>

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    this->setMaximumSize(350,150);
    this->setMinimumSize(350,150);

//Main Background Image
    QPixmap bkgnd("/home/corey/Desktop/QtProjects/SCFH/bg_tile.jpg");
    bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio);
    QPalette palette;
    palette.setBrush(QPalette::Background, bkgnd);
    this->setPalette(palette);


//Create Window / connections
    this->setWindowTitle("South Coast Family Harbor");

    userLbl = new QLabel("Username", this );
    userEdit = new QLineEdit("", this );
    passLbl = new QLabel("Password", this );
    passEdit = new QLineEdit("", this );
    userLbl->setGeometry(QRect(20,40,80,30));
    userEdit->setGeometry(QRect(100,40,200,30));
    passLbl->setGeometry(QRect(20,80,80,30));
    passEdit->setGeometry(QRect(100,80,200,30));
    passEdit->setEchoMode(QLineEdit::Password);
    okBtn = new QPushButton("OK", this );
    okBtn->setGeometry(QRect(250, 120, 80, 30));

//Set Button Connections
    connect(okBtn,SIGNAL( clicked() ),this,SLOT( getUser() ));

}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::getUser()
{
    QString userName;  //Used for validation
    QString password;  //Used for validation

    qDebug() << "Got user input";

    if( userEdit->text() == "" || passEdit->text() == "" )  //If a field is empty
    {
            QMessageBox::critical(this,qApp->tr("warning"),qApp->tr("No Text Entered in a field."),QMessageBox::Ok);
    }
    else    //Both fields have text
    {
            qDebug() << "Checking Database";

            //Check With Databse
            QSqlQuery query;
            query.prepare("select username, password from login where username = :user and password = :password");
            query.bindValue(":user", userEdit->text() );
            query.bindValue(":password", passEdit->text());
            query.exec();
            //Get query result indexes for reading
            QSqlRecord rec = query.record();
            int userCol = rec.indexOf("username"); // index of the field "name"
            int passCol = rec.indexOf("password");
            //Get query results
            while(query.next())
            {
                //Put query results into QStrings.
                qDebug() << query.value(userCol).toString(); // output all names
                qDebug() << query.value(passCol).toString();
                userName = query.value(userCol).toString();
                password = query.value(passCol).toString();
            }
            //Right now only two users are in the database, admin or guest.
            if( userName == "admin" && passEdit->text() == password )   //Admin Account
            {
                QMessageBox::information(this,qApp->tr("warning"),qApp->tr("Admin privelages activated."),QMessageBox::Ok);
            }
            else if( userName == "guest" && passEdit->text() == password )  //Guest Account
            {
                QMessageBox::information(this,qApp->tr("warning"),qApp->tr("Guest Account activated."),QMessageBox::Ok);
            }
            else
            {
                qDebug() << "User not defined in database";
                QMessageBox::critical(this,qApp->tr("warning"),qApp->tr("User not defined."),QMessageBox::Ok);
                return;
            }

            demoGraph.open();
            demoGraph.setWindowTitle("South Coast Family Harbor");


    }


}
