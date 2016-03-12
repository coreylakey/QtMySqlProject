#include "demographics.h"
#include "ui_demographics.h"
#include <QSqlQuery>
#include <QDebug>
#include <QSqlDatabase>
#include <QSqlRecord>

Demographics::Demographics(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Demographics)
{
    ui->setupUi(this);
    this->setContentsMargins(0,0,0,0);
    //Sets fixed size for entire window
    this->setMaximumSize(1440,900);
    this->setMinimumSize(1440,900);
    this->setWindowTitle("South Coast Family Harbor");   //NOTE: Window Titles is not changing properly.


    //Tiles background image
    QPalette *Palette = new QPalette();
    QPixmap *Pixmap = new QPixmap("/home/corey/Desktop/SCFHCOPY/bg_tile.jpg");
    Palette->setBrush(QPalette::Background,QBrush(*Pixmap));
    setPalette(*Palette);


//fonts
    //titles
    QFont font;
    font.setBold(true);
    font.setUnderline(true);
    font.setPointSize(24);
    //labels
    QFont font2;
    font2.setBold(true);
    font2.setPointSize(12);
    //checkboxes
    QFont font3;
    font3.setBold(true);

//Labels Creation
    fNamelbl        = new QLabel("First Name",this );
    lNamelbl        = new QLabel("Last Name", this );
    addresslbl      = new QLabel("Address", this );
    citylbl         = new QLabel("City", this );
    childInfolbl    = new QLabel("    Child Info    ", this );
    childAgelbl     = new QLabel("Child Age", this );
    childGenderlbl  = new QLabel("Child Gender", this );
    clientInfolbl   = new QLabel("    Client Info    ", this );
    livSitlbl       = new QLabel("Living Situation", this );
    houseTypelbl    = new QLabel("Housing Type", this );
    incSrclbl       = new QLabel("Income Source", this );
    heardlbl        = new QLabel("How did you hear about us?", this );
    bottomImg       = new QLabel(this);

    //Bottom Image
    QPixmap bottom_pixmap("/home/corey/Desktop/SCFHCOPY/bottom.png");
    bottomImg->setPixmap(bottom_pixmap);
    bottomImg->setMaximumWidth(1440);
    bottomImg->setMinimumWidth(1440);

//Labels Position
    clientInfolbl->setGeometry(QRect(400,50,300,30));
    clientInfolbl->setFont(font);
    fNamelbl->setGeometry(QRect(490,90,300,30));
    fNamelbl->setFont(font2);
    lNamelbl->setGeometry(QRect(490,130,300,30));
    lNamelbl->setFont(font2);
    addresslbl->setGeometry(QRect(490,170,300,30));
    addresslbl->setFont(font2);
    citylbl->setGeometry(QRect(490,210,300,30));
    citylbl->setFont(font2);
    livSitlbl->setGeometry(QRect(490,250,300,30));
    livSitlbl->setFont(font2);
    houseTypelbl->setGeometry(QRect(490,290,300,30));
    houseTypelbl->setFont(font2);
    incSrclbl->setGeometry(QRect(490,330,300,30));
    incSrclbl->setFont(font2);
    heardlbl->setGeometry(QRect(490,370,300,30));
    heardlbl->setFont(font2);
    childInfolbl->setGeometry(QRect(400,470,300,30));
    childInfolbl->setFont(font);
    childAgelbl->setGeometry(QRect(490,510,300,30));
    childAgelbl->setFont(font2);
    childGenderlbl->setGeometry(QRect(490,550,300,30));
    childGenderlbl->setFont(font2);
    bottomImg->setGeometry(QRect(0,663,1440,237));
//LineEdits Creation
    fNameEdit       = new QLineEdit(this);
    lNameEdit       = new QLineEdit(this);
    addressEdit     = new QLineEdit(this);

//LineEdits Position
    fNameEdit->setGeometry(QRect(700,90,200,30));
    lNameEdit->setGeometry(QRect(700,130,200,30));
    addressEdit->setGeometry(QRect(700,170,200,30));

//ComboBoxes Creation
    cityEdit        = new QComboBox(this);
    childAgeEdit    = new QComboBox(this);
    livSitEdit      = new QComboBox(this);
    houseTypeEdit   = new QComboBox(this);
    incSrcEdit      = new QComboBox(this);
    howHeardEdit    = new QComboBox(this);
//ComboBox String Creation
    QStringList cityList;
    QStringList childAgeList;
    QStringList livSitList;
    QStringList houseTypeList;
    QStringList incSrcList;
    QStringList howHeardList;
    cityList << "CB" << "NB" << "MP" << "CQ" << "BN" << "LKS" << "REED" << "P.O." << "Powers" << "Other";
    childAgeList << "Prenatal" << "1mo" << "2mo" << "3mo" << "4mo" << "5mo" << "6mo" << "24mo" << "3 years" << "4 years" << "5 years" << "6 years";
    livSitList << "Friends" << "Family" << "Self";
    houseTypeList << "HVD" << "Rent" << "Own";
    incSrcList << "TANF" << "Work" << "SNAP" << "Child Support" << "Foster Care" << "Disability" << "Self-Employed" << "Unemployment" << "Alimony" << "None";
    howHeardList << "Friend" << "Family" << "Newmark Center" << "HeadStart" << "Maslow" << "Local Ads" << "Facebook" << "Other";
//ComboBoxes attributes
    cityEdit->addItems(cityList);
    cityEdit->setGeometry(QRect(700, 210, 200, 30));
    childAgeEdit->addItems(childAgeList);
    childAgeEdit->setGeometry(QRect(700, 510, 200, 30));
    livSitEdit->addItems(livSitList);
    livSitEdit->setGeometry(QRect(700, 250, 200, 30));
    houseTypeEdit->addItems(houseTypeList);
    houseTypeEdit->setGeometry(QRect(700, 290, 200, 30));
    incSrcEdit->addItems(incSrcList);
    incSrcEdit->setGeometry(QRect(700, 330, 200, 30));
    howHeardEdit->addItems(howHeardList);
    howHeardEdit->setGeometry(QRect(700, 370, 200, 30));
//CheckBoxes Creation
    maleBox   = new QCheckBox(this);
    femaleBox = new QCheckBox(this);
//CheckBoxes Attributes
    maleBox->setGeometry(QRect(700, 550, 200, 30));
    maleBox->setText("Male");
    maleBox->setFont(font3);
    femaleBox->setGeometry(QRect(790, 550, 200, 30));
    femaleBox->setText("Female");
    femaleBox->setFont(font3);
//Make Gender Exclusive
    genderGroup = new QButtonGroup(this);
    genderGroup->addButton(maleBox);
    genderGroup->addButton(femaleBox);
    genderGroup->setExclusive(true);
//Cancel/Ok buttons Creation
    okBtn       = new QPushButton(this);
    cancelBtn   = new QPushButton(this);
//Cancel/Ok buttons attributes
    okBtn->setText("OK");
    cancelBtn->setText("Cancel");
//Cancel/Ok buttons Position
    okBtn->setGeometry(QRect(680, 640, 130, 40));
    cancelBtn->setGeometry(QRect(860, 640, 130, 40));

//Make Button Connections
    connect(okBtn,SIGNAL( clicked() ),this,SLOT( sendInfo() ));
    connect(cancelBtn,SIGNAL(clicked()),this,SLOT(close()));

}

Demographics::~Demographics()
{
    delete ui;
}

void Demographics::sendInfo()
{
    qDebug() << "Got info";
    if( fNameEdit->text() == "" || lNameEdit->text() == "" || addressEdit->text() == "" )
    {
        //Client Info Missing
        QMessageBox::information(this,qApp->tr("warning"),qApp->tr("Client Info Missing."),QMessageBox::Ok);
        return;
    }
    else if( !maleBox->isChecked() && !femaleBox->isChecked() )
    {
        //Child Info Missing
        QMessageBox::information(this,qApp->tr("warning"),qApp->tr("Child Info Missing."),QMessageBox::Ok);
        return;
    }
    else
    {
        qDebug() << "all fields complete. Query initiated.";

        //Insert Values from form
        startQuery();

        this->hide();
        giftWindow.open();
        giftWindow.setWindowTitle("South Coast Family Harbor");
        giftWindow.idExists = existingID;
    }
}

void Demographics::startQuery()
{
    QString gender;

    if( existingClient() )
    {
        existingID = getExistingId();
        this->hide();
        giftWindow.open();
        giftWindow.setWindowTitle("South Coast Family Harbor");
        giftWindow.idExists = existingID;
    }
    else
    {
        if(maleBox->isChecked())
            gender = "M";
        else
            gender = "F";

            QSqlQuery query;
            query.prepare("INSERT INTO clients VALUES( null , :fName, :lName, :address,"
                          ":city, :livingSit, :housingType, :incomeSource, :childAge, :childGender,"
                          ":howHeard );");
            query.bindValue(":fName", fNameEdit->text() );
            query.bindValue(":lName", lNameEdit->text() );
            query.bindValue(":address", addressEdit->text() );
            query.bindValue(":city", cityEdit->currentText() );
            query.bindValue(":livingSit", livSitEdit->currentText() );
            query.bindValue(":housingType", houseTypeEdit->currentText() );
            query.bindValue(":incomeSource", incSrcEdit->currentText() );
            query.bindValue(":childAge", childAgeEdit->currentText() );
            query.bindValue(":childGender", gender );
            query.bindValue(":howHeard", howHeardEdit->currentText() );
            query.exec();
            qDebug() << query.lastQuery();

            query.prepare("SELECT clientID FROM clients WHERE fName = :firstName AND lName = :lastName;");
            query.bindValue(":firstName", fNameEdit->text() );
            query.bindValue(":lastName", lNameEdit->text() );
            query.exec();

            QSqlRecord rec = query.record();
            int clientID = rec.indexOf("clientID"); // index of the field "clientID"

            //Get query results
            while(query.next())
            {
                //Put query results into QStrings.
                qDebug() << "New user had ID of " + query.value(clientID).toString(); // clientID
                existingID = query.value(clientID).toInt();

            }

            qDebug() << "No query for inserting :(";
            return;
    }


}

int Demographics::existingClient()
{
    QSqlQuery existCheck;
    QString firstCheck, lastCheck;

    existCheck.prepare("SELECT fName, lName FROM clients WHERE fName = :first AND lName = :last;");
    existCheck.bindValue(":first", fNameEdit->text() );
    existCheck.bindValue(":last", lNameEdit->text() );
    existCheck.exec();

    QSqlRecord rec = existCheck.record();
    int firstCol = rec.indexOf("fName"); // index of the field "clientID"
    int lastCol = rec.indexOf("lName");

//Get query results
    while(existCheck.next())
    {
        //Put query results into QStrings.
            qDebug() << existCheck.value(firstCol).toString(); // output all names
            qDebug() << existCheck.value(lastCol).toString();
            firstCheck = existCheck.value(firstCol).toString();
            lastCheck = existCheck.value(lastCol).toString();
        //If User is found.. go back
            if( firstCheck == fNameEdit->text() && lastCheck == lNameEdit->text() )
            {
                qDebug() << "User was found in database";
                return -1;
            }
    }

    qDebug() << "User not in database yet.";
    return 0;

}

int Demographics::getExistingId()
{
    QSqlQuery existCheck;
    int retID;

    existCheck.prepare("SELECT clientID FROM clients WHERE fName = :first AND lName = :last;");
    existCheck.bindValue(":first", fNameEdit->text() );
    existCheck.bindValue(":last", lNameEdit->text() );
    existCheck.exec();

    QSqlRecord rec = existCheck.record();
    int clientID = rec.indexOf("clientID"); // index of the field "clientID"

    //Get query results
    while(existCheck.next())
    {
        //Put query results into QStrings.
            qDebug() << existCheck.value(clientID).toString(); // clientID
            retID = existCheck.value(clientID).toInt();
            qDebug() << retID;
            if( retID != 0 )
                break;
    }

    return retID;

}

void Demographics::cancel()
{
    qDebug() << "Got Cancel";
}
