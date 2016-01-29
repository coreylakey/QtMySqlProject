//Yo yo yo

#include "demographics.h"
#include "ui_demographics.h"

Demographics::Demographics(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Demographics)
{
    ui->setupUi(this);

    this->setMaximumSize(450,450);
    this->setMinimumSize(450,450);

//Create Window / connections
    this->setWindowTitle("South Coast Family Harbor");

//Labels Creation
    fNamelbl        = new QLabel("First Name",this );
    lNamelbl        = new QLabel("Last Name", this );
    addresslbl      = new QLabel("Address", this );
    citylbl         = new QLabel("City", this );
    childInfolbl    = new QLabel("Child Info", this );
    childAgelbl     = new QLabel("Child Age", this );
    childGenderlbl  = new QLabel("Child Gender", this );
    clientInfolbl   = new QLabel("Client Info", this );
    livSitlbl       = new QLabel("Living Situation", this );
    houseTypelbl    = new QLabel("Housing Type", this );
    incSrclbl       = new QLabel("Income Source", this );
    heardlbl        = new QLabel("How did you hear about us?", this );
//Labels Position
    fNamelbl->setGeometry(QRect(20,20,300,30));
    lNamelbl->setGeometry(QRect(20,50,300,30));
    addresslbl->setGeometry(QRect(20,80,300,30));
    citylbl->setGeometry(QRect(20,110,300,30));
    childInfolbl->setGeometry(QRect(30,140,300,30));
    childAgelbl->setGeometry(QRect(20,170,300,30));
    childGenderlbl->setGeometry(QRect(20,200,300,30));
    clientInfolbl->setGeometry(QRect(30,230,300,30));
    livSitlbl->setGeometry(QRect(20,260,300,30));
    houseTypelbl->setGeometry(QRect(20,290,300,30));
    incSrclbl->setGeometry(QRect(20,320,300,30));
    heardlbl->setGeometry(QRect(20,350,300,30));
//LineEdits Creation
    fNameEdit       = new QLineEdit(this);
    lNameEdit       = new QLineEdit(this);
    addressEdit     = new QLineEdit(this);

//LineEdits Position
    fNameEdit->setGeometry(QRect(230,20,200,30));
    lNameEdit->setGeometry(QRect(230,50,200,30));
    addressEdit->setGeometry(QRect(230,80,200,30));


}

Demographics::~Demographics()
{
    delete ui;
}
