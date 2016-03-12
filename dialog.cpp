#include "dialog.h"
#include "ui_dialog.h"
#include <QMessageBox>
#include <QPushButton>
#include <QSqlTableModel>
#include <QSqlQuery>
#include <QDebug>
#include <QSqlDatabase>
#include <QSqlRecord>
//#include <QtWidgets>
//#include <QWidget>
#include <QGridLayout>


Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);

    //Sets fixed size for entire window
    this->setMaximumSize(1440,900);
    this->setMinimumSize(1440,900);
    this->setWindowTitle("South Coast Family Harbor");   //NOTE: Window Titles is not changing properly.

    //Some Declarations..
    QGridLayout *gridlayout = new QGridLayout;
    QHBoxLayout *hlayoutUser = new QHBoxLayout;
    QHBoxLayout *hlayoutPass = new QHBoxLayout;
    QHBoxLayout *hlayoutButton = new QHBoxLayout;
    QHBoxLayout *hlayoutBanner = new QHBoxLayout;
    QHBoxLayout *hlayoutBottom = new QHBoxLayout;
    QVBoxLayout *vlayout = new QVBoxLayout;
    //A few more..
    userLbl = new QLabel(this);
    userEdit = new QLineEdit("", this);
    passLbl = new QLabel(this);
    passEdit = new QLineEdit("", this);
    banner = new QLabel(this);
    bottom = new QLabel(this);
    okBtn = new QPushButton("Sign In", this);

    //Tiles background image
    QPalette *Palette = new QPalette();
    QPixmap *Pixmap = new QPixmap("/home/corey/Desktop/SCFHCOPY/bg_tile.jpg");
    Palette->setBrush(QPalette::Background,QBrush(*Pixmap));
    setPalette(*Palette);

    //Spacers are used to maintain a consistent layout
        //H Spacers
        QSpacerItem *mainHSpacer = new QSpacerItem(500,0, QSizePolicy::Fixed, QSizePolicy::Fixed);
        QSpacerItem *bannerHSpacer = new QSpacerItem(588,0, QSizePolicy::Fixed, QSizePolicy::Fixed);
        QSpacerItem *buttonHSpacer = new QSpacerItem(553,0, QSizePolicy::Fixed, QSizePolicy::Fixed);

        //V Spacers
        QSpacerItem *mainVSpacer = new QSpacerItem(0,40, QSizePolicy::Fixed, QSizePolicy::Fixed);
        QSpacerItem *bannerVSpacer = new QSpacerItem(0,150, QSizePolicy::Fixed, QSizePolicy::Fixed);
        QSpacerItem *bottomVSpacer = new QSpacerItem(0,80, QSizePolicy::Fixed, QSizePolicy::Fixed);


//Begin constructing layouts..

    //User Grid
    hlayoutUser->setContentsMargins(0,0,0,0);
    hlayoutUser->addSpacerItem(mainHSpacer);
    hlayoutUser->addWidget(userLbl);
    hlayoutUser->addWidget(userEdit);
    hlayoutUser->addStretch();

    //Password Grid
    hlayoutPass->setContentsMargins(0,0,0,0);
    hlayoutPass->addSpacerItem(mainHSpacer);
    hlayoutPass->addWidget(passLbl);
    hlayoutPass->addWidget(passEdit);
    hlayoutPass->addStretch();

    //Sign In Button Grid
    hlayoutButton->setContentsMargins(0,0,0,0);
    hlayoutButton->addSpacerItem(buttonHSpacer);
    hlayoutButton->addWidget(okBtn);
    hlayoutButton->addStretch();

    //Top Banner Grid
    hlayoutBanner->setContentsMargins(0,0,0,0);
    hlayoutBanner->addSpacerItem(bannerHSpacer);
    hlayoutBanner->addWidget(banner);
    hlayoutBanner->addStretch();

    //Bottom/Footer Grid
    hlayoutBottom->setContentsMargins(0,0,0,0);
    hlayoutBottom->addWidget(bottom);
    hlayoutBottom->addStretch();

    //Aligned and spaced vertically in layout
    vlayout->setContentsMargins(0,0,0,0);
    vlayout->addSpacerItem(bannerVSpacer);
    vlayout->addLayout(hlayoutBanner);
    vlayout->addSpacerItem(mainVSpacer);
    vlayout->addLayout(hlayoutUser);
    vlayout->addLayout(hlayoutPass);
    vlayout->addLayout(hlayoutButton);
    vlayout->addSpacerItem(bottomVSpacer);
    vlayout->addLayout(hlayoutBottom);
    vlayout->addStretch();

    //Adds complete layout at start position of grid layout
    gridlayout->setContentsMargins(0,0,0,0);
    gridlayout->addLayout(vlayout,0,0);


    //Some settings..
        //User
        userEdit->setMaximumWidth(350);
        userEdit->setMinimumWidth(350);
        userEdit->setMinimumHeight(40);
        userEdit->setMaximumHeight(40);
        userEdit->setPlaceholderText("Username");

        //Pass
        passEdit->setMaximumWidth(350);
        passEdit->setMinimumWidth(350);
        passEdit->setMinimumHeight(40);
        passEdit->setMinimumHeight(40);
        passEdit->setPlaceholderText("Password");

        //Button
        okBtn->setMinimumWidth(350);
        okBtn->setMaximumWidth(350);
        okBtn->setMaximumHeight(40);
        okBtn->setMinimumHeight(40);
        connect(okBtn, SIGNAL(clicked()), this, SLOT(getUser()));

        //Icons
        QPixmap user_pixmap("/home/corey/Desktop/SCFHCOPY/user.png");
        userLbl->setPixmap(user_pixmap);
        QPixmap pass_pixmap("/home/corey/Desktop/SCFHCOPY/pass.png");
        passLbl->setPixmap(pass_pixmap);

        //Banner
        QPixmap banner_pixmap("/home/corey/Desktop/SCFHCOPY/banner.png");
        banner->setPixmap(banner_pixmap);
        banner->setMaximumWidth(270);
        banner->setMinimumWidth(270);
        banner->setMinimumHeight(242);
        banner->setMaximumHeight(242);

        //Bottom Image
        QPixmap bottom_pixmap("/home/corey/Desktop/SCFHCOPY/bottom.png");
        bottom->setPixmap(bottom_pixmap);
        bottom->setMaximumWidth(1440);
        bottom->setMinimumWidth(1440);


    passEdit->setEchoMode(QLineEdit::Password);

    this->setWindowTitle("South Coast Family Harbor");

    setLayout(gridlayout);
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
                this->hide();
                adminPage.open();
                adminPage.setWindowTitle("Admin Reports");
            }
            else if( userName == "guest" && passEdit->text() == password )  //Guest Account
            {
                QMessageBox::information(this,qApp->tr("warning"),qApp->tr("Guest Account activated."),QMessageBox::Ok);
                this->hide();
                demoGraph.open();
                demoGraph.setWindowTitle("South Coast Family Harbor");
            }
            else
            {
                qDebug() << "User not defined in database";
                QMessageBox::critical(this,qApp->tr("warning"),qApp->tr("User not defined."),QMessageBox::Ok);
                return;
            }


    }

}
