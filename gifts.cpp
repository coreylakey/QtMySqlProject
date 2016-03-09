#include "gifts.h"
#include "ui_gifts.h"
#include <QSqlQuery>
#include <QDebug>
#include <QSqlDatabase>
#include <QSqlRecord>

gifts::gifts(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::gifts)
{
    ui->setupUi(this);



//Create Window / connections
    this->setWindowTitle("South Coast Family Harbor");
    this->setMaximumSize(365,600);
    this->setMinimumSize(365,600);


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
    banner->setGeometry(QRect(100,10,0,0));

//Label Creation    (Theres alot of labels..)
    diapers = new QLabel("Diapers",this);
    diapers->setStyleSheet("QLabel {font : bold;}");
    diapers->setGeometry(QRect(20,180,300,30));
    diapSize = new QLabel("Diaper Size", this);
    diapSize->setGeometry(QRect(200,180,300,30));
    wipes = new QLabel("Wipes", this);
    wipes->setStyleSheet("QLabel {font : bold;}");
    wipes->setGeometry(QRect(20,200,300,30));
    blankets = new QLabel("Blankets", this);
    blankets->setStyleSheet("QLabel {font : bold;}");
    blankets->setGeometry(QRect(20, 220, 300, 30));
    bbyLotion = new QLabel("Baby Lotion", this);
    bbyLotion->setStyleSheet("QLabel {font : bold;}");
    bbyLotion->setGeometry(QRect(20, 240, 300, 30));
    bbyWash = new QLabel("Baby Wash", this);
    bbyWash->setStyleSheet("QLabel {font : bold;}");
    bbyWash->setGeometry(QRect(20, 260, 300, 30));
    bbyPwder = new QLabel("Baby Powder", this);
    bbyPwder->setStyleSheet("QLabel {font : bold;}");
    bbyPwder->setGeometry(QRect(20, 280, 300, 30));
    rshCreme = new QLabel("Rash Creme", this);
    rshCreme->setStyleSheet("QLabel {font : bold;}");
    rshCreme->setGeometry(QRect(20, 300, 300, 30));
    tthBrsh = new QLabel("ToothBrushes", this);
    tthBrsh->setStyleSheet("QLabel {font : bold;}");
    tthBrsh->setGeometry(QRect(20, 320, 300, 30));
    tthPste = new QLabel("ToothPaste", this);
    tthPste->setStyleSheet("QLabel {font : bold;}");
    tthPste->setGeometry(QRect(20, 340, 300, 30));
    bottles = new QLabel("Bottles", this);
    bottles->setStyleSheet("QLabel {font : bold;}");
    bottles->setGeometry(QRect(20, 360, 300, 30));
    sippCups = new QLabel("Sippy Cups", this);
    sippCups->setStyleSheet("QLabel {font : bold;}");
    sippCups->setGeometry(QRect(20, 380, 300, 30));
    plstcPlates = new QLabel("Plastic Plates", this);
    plstcPlates->setStyleSheet("QLabel {font : bold;}");
    plstcPlates->setGeometry(QRect(20, 400, 300, 30));
    bthClothes = new QLabel("Bath Clothes", this);
    bthClothes->setStyleSheet("QLabel {font : bold;}");
    bthClothes->setGeometry(QRect(20, 420, 300, 30));
    bthSponges = new QLabel("Bath Sponges", this);
    bthSponges->setStyleSheet("QLabel {font : bold;}");
    bthSponges->setGeometry(QRect(20, 440, 300, 30));
    clothes = new QLabel("Clothes", this);
    clothes->setStyleSheet("QLabel {font : bold;}");
    clothes->setGeometry(QRect(20, 460, 300, 30));
    clotheSize = new QLabel("Clothes Size", this);
    clotheSize->setGeometry(QRect(200, 460, 300, 30));
    newClothes = new QLabel("New", this);
    newClothes->setStyleSheet("QLabel {font : bold;}");
    newClothes->setGeometry(QRect(40, 480, 300, 30));
    usedClothes = new QLabel("Used", this);
    usedClothes->setStyleSheet("QLabel {font : bold;}");
    usedClothes->setGeometry(QRect(40, 500, 300, 30));
    socks = new QLabel("Socks", this);
    socks->setStyleSheet("QLabel {font : bold;}");
    socks->setGeometry(QRect(20, 520, 300, 30));
    shoes = new QLabel("Shoes", this);
    shoes->setStyleSheet("QLabel {font : bold;}");
    shoes->setGeometry(QRect(20, 540, 300, 30));
    misc = new QLabel("Miscellaneous", this);
    misc->setStyleSheet("QLabel {font : bold;}");
    misc->setGeometry(QRect(20, 560, 300, 30));
//Spin Box Creation
    diaperNum = new QSpinBox(this);
    diaperNum->setGeometry(QRect(140, 180, 50, 20));
    wipeNum = new QSpinBox(this);
    wipeNum->setGeometry(QRect(140, 200, 50, 20));
    blanketNum = new QSpinBox(this);
    blanketNum->setGeometry(QRect(140, 220, 50, 20));
    lotionNum = new QSpinBox(this);
    lotionNum->setGeometry(QRect(140, 240, 50, 20));
    washNum = new QSpinBox(this);
    washNum->setGeometry(QRect(140, 260, 50, 20));
    pwderNum = new QSpinBox(this);
    pwderNum->setGeometry(QRect(140, 280, 50, 20));
    cremeNum = new QSpinBox(this);
    cremeNum->setGeometry(QRect(140, 300, 50, 20));
    tthBrshNum = new QSpinBox(this);
    tthBrshNum->setGeometry(QRect(140, 320, 50, 20));
    tthPsteNum = new QSpinBox(this);
    tthPsteNum->setGeometry(QRect(140, 340, 50, 20));
    bottleNum = new QSpinBox(this);
    bottleNum->setGeometry(QRect(140, 360, 50, 20));
    sippCupNum = new QSpinBox(this);
    sippCupNum->setGeometry(QRect(140, 380, 50, 20));
    plateNum = new QSpinBox(this);
    plateNum->setGeometry(QRect(140, 400, 50, 20));
    bthClothesNum = new QSpinBox(this);
    bthClothesNum->setGeometry(QRect(140, 420, 50, 20));
    bthSpongeNum = new QSpinBox(this);
    bthSpongeNum->setGeometry(QRect(140, 440, 50, 20));
    clthesNum = new QSpinBox(this);
    clthesNum->setGeometry(QRect(140, 460, 50, 20));
    socksNum = new QSpinBox(this);
    socksNum->setGeometry(QRect(140, 520, 50, 20));
    shoesNum = new QSpinBox(this);
    shoesNum->setGeometry(QRect(140, 540, 50, 20));
    miscNum = new QSpinBox(this);
    miscNum->setGeometry(QRect(140, 560, 50, 20));
//ComboBoxes Creation
    clothesBox = new QComboBox(this);
    diapersBox = new QComboBox(this);
//ComboBox String Creation
    QStringList clothesList;
    QStringList diapersList;
    clothesList << "Premie" << "0-3" << "3-6" << "6-9" << "9-12" << "12-18" << "2T" << "3T" << "4T" << "5T";
    diapersList << "Newborn" << "1" << "2" << "3" << "4" << "5" << "6";
//ComboBoxes attributes
    clothesBox->addItems(clothesList);
    clothesBox->setGeometry(QRect(230,480,100,30));
    diapersBox->addItems(diapersList);
    diapersBox->setGeometry(QRect(230,200,100,30));
//CheckBoxes Creation
    newBox   = new QCheckBox(this);
    usedBox = new QCheckBox(this);
//CheckBoxes Attributes
    newBox->setGeometry(QRect(140, 480, 50, 20));
    //newBox->setText("New");
    usedBox->setGeometry(QRect(140, 500, 50, 20));
    //usedBox->setText("Used");
//Make Gender Exclusive
    clothesGroup = new QButtonGroup(this);
    clothesGroup->addButton(newBox);
    clothesGroup->addButton(usedBox);
    clothesGroup->setExclusive(true);
//Cancel/Ok buttons Creation
    okBtn       = new QPushButton(this);
    cancelBtn   = new QPushButton(this);
//Cancel/Ok buttons attributes
    okBtn->setText("SUBMIT");
    cancelBtn->setText("Cancel");
//Cancel/Ok buttons Position
    okBtn->setGeometry(QRect(230, 520, 100, 30));
    cancelBtn->setGeometry(QRect(230, 550, 100, 30));
//Button signal/slots
    connect(cancelBtn,SIGNAL(clicked()),this,SLOT( close() ));
    connect(okBtn,SIGNAL( clicked() ),this,SLOT( giftSubmit() ));

}

gifts::~gifts()
{
    delete ui;
}

void gifts::giftSubmit()
{

    qDebug() << "Got user input";

    QString condition;
    //If condition for New clothes is checked, place New into database.
    if( newBox->isChecked() )
        condition = "New";
    else
        condition = "Used";

    QSqlQuery query;

    query.prepare("INSERT INTO gifts VALUES( null, :date, :diapers, :diaperSize, :wipes, :blankets, :babyLotion, :babyWash, "
                              " :babyPowder, :diaperCream, :toothbrushes, :toothpaste, :bottles, :sippyCups, :plasticPlates, :clothes, "
                              ":clothesSize, :clothesCond, :socks, :shoes, :misc, :id );");
    query.bindValue(":id", idExists );

    //These next two values are what I am working on at the moment.
        query.bindValue(":date", "2016-08-07 00:00:00");
    //***************************************************************


        query.bindValue(":diapers", diaperNum->text() );
        query.bindValue(":diaperSize", diapersBox->currentText() );
        query.bindValue(":wipes", wipeNum->text() );
        query.bindValue(":blankets", blanketNum->text() );
        query.bindValue(":babyLotion", lotionNum->text() );
        query.bindValue(":babyWash", washNum->text() );
        query.bindValue(":babyPowder", pwderNum->text() );
        query.bindValue(":diaperCream", cremeNum->text() );
        query.bindValue(":toothbrushes", tthBrshNum->text() );
        query.bindValue(":toothpaste", tthPsteNum->text() );
        query.bindValue(":bottles", bottleNum->text() );
        query.bindValue(":sippyCups", sippCupNum->text() );
        query.bindValue(":plasticPlates", plateNum->text() );
        query.bindValue(":clothes", bthClothesNum->text() );
        query.bindValue(":clothesSize", clothesBox->currentText() );
        query.bindValue(":clothesCond", condition );
        query.bindValue(":socks", socksNum->text() );
        query.bindValue(":shoes", shoesNum->text() );
        query.bindValue(":misc", miscNum->text() );
        query.exec();

        qDebug() << query.lastQuery();


        return;
}
