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
        connect(cancelBtn, SIGNAL( clicked() ),this, SLOT( cancel() ));


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
        giftWindow.open();
        giftWindow.setWindowTitle("South Coast Family Harbor");
    }
}

void Demographics::cancel()
{
    qDebug() << "Got Cancel";
}
