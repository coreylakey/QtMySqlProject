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

    this->setMaximumSize(450,450);
    this->setMinimumSize(450,450);

//Create Window / connections
    this->setWindowTitle("South Coast Family Harbor");

//Main Background Image
    QPixmap bkgnd("/home/mycoal/Desktop/QtProjects/SCFH/bg_tile.jpg");
    bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio);
    QPalette palette;
    palette.setBrush(QPalette::Background, bkgnd);
    this->setPalette(palette);


//ClientInfo/ChildInfo fonts
    QFont font;
    font.setBold(true);
    font.setUnderline(true);
    font.setPointSize(14);
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
//Labels Position
    clientInfolbl->setGeometry(QRect(30,20,300,30));
    clientInfolbl->setFont(font);
    fNamelbl->setGeometry(QRect(20,50,300,30));
    lNamelbl->setGeometry(QRect(20,80,300,30));
    addresslbl->setGeometry(QRect(20,110,300,30));
    citylbl->setGeometry(QRect(20,140,300,30));
    livSitlbl->setGeometry(QRect(20,170,300,30));
    houseTypelbl->setGeometry(QRect(20,200,300,30));
    incSrclbl->setGeometry(QRect(20,230,300,30));
    heardlbl->setGeometry(QRect(20,260,300,30));
    childInfolbl->setGeometry(QRect(30,290,300,30));
    childInfolbl->setFont(font);
    childAgelbl->setGeometry(QRect(20,320,300,30));
    childGenderlbl->setGeometry(QRect(20,350,300,30));
//LineEdits Creation
    fNameEdit       = new QLineEdit(this);
    lNameEdit       = new QLineEdit(this);
    addressEdit     = new QLineEdit(this);

//LineEdits Position
    fNameEdit->setGeometry(QRect(230,50,200,30));
    lNameEdit->setGeometry(QRect(230,80,200,30));
    addressEdit->setGeometry(QRect(230,110,200,30));

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
    cityEdit->setGeometry(QRect(230, 140, 200, 30));
    childAgeEdit->addItems(childAgeList);
    childAgeEdit->setGeometry(QRect(230, 320, 200, 30));
    livSitEdit->addItems(livSitList);
    livSitEdit->setGeometry(QRect(230, 170, 200, 30));
    houseTypeEdit->addItems(houseTypeList);
    houseTypeEdit->setGeometry(QRect(230, 200, 200, 30));
    incSrcEdit->addItems(incSrcList);
    incSrcEdit->setGeometry(QRect(230, 230, 200, 30));
    howHeardEdit->addItems(howHeardList);
    howHeardEdit->setGeometry(QRect(230, 260, 200, 30));
//CheckBoxes Creation
    maleBox   = new QCheckBox(this);
    femaleBox = new QCheckBox(this);
//CheckBoxes Attributes
    maleBox->setGeometry(QRect(230, 350, 200, 30));
    maleBox->setText("Male");
    femaleBox->setGeometry(QRect(230, 380, 200, 30));
    femaleBox->setText("Female");
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
    okBtn->setGeometry(QRect(230, 410, 80, 30));
    cancelBtn->setGeometry(QRect(320, 410, 80, 30));

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
