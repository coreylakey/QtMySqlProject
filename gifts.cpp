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

    //Bottom Image
    bottomImg   = new QLabel(this);
    QPixmap bottom_pixmap("/home/corey/Desktop/SCFHCOPY/bottom.png");
    bottomImg->setPixmap(bottom_pixmap);
    bottomImg->setMaximumWidth(1440);
    bottomImg->setMinimumWidth(1440);
    bottomImg->setGeometry(QRect(0,663,1440,237));



//Label Creation    (Theres alot of labels..)
    giftslbl = new QLabel("Gifts",this);
    diapers = new QLabel("Diapers",this);
    diapSize = new QLabel("Diaper Size", this);
    wipes = new QLabel("Wipes", this);
    blankets = new QLabel("Blankets", this);
    bbyLotion = new QLabel("Baby Lotion", this);
    bbyWash = new QLabel("Baby Wash", this);
    bbyPwder = new QLabel("Baby Powder", this);
    rshCreme = new QLabel("Rash Creme", this);
    tthBrsh = new QLabel("ToothBrushes", this);
    tthPste = new QLabel("ToothPaste", this);
    bottles = new QLabel("Bottles", this);
    sippCups = new QLabel("Sippy Cups", this);
    plstcPlates = new QLabel("Plastic Plates", this);
    bthClothes = new QLabel("Bath Clothes", this);
    bthSponges = new QLabel("Bath Sponges", this);
    clothes = new QLabel("Clothes", this);
    clotheSize = new QLabel("Clothes Size", this);
    newClothes = new QLabel("New", this);
    usedClothes = new QLabel("Used", this);
    socks = new QLabel("Socks", this);
    shoes = new QLabel("Shoes", this);
    misc = new QLabel("Miscellaneous", this);

//Label Position
    giftslbl->setGeometry(QRect(400,50,300,30));
    diapers->setGeometry(QRect(490,90,300,30));
    diapSize->setGeometry(QRect(720,90,300,30));
    wipes->setGeometry(QRect(490,120,170,30));
    blankets->setGeometry(QRect(490, 150, 300, 30));
    bbyLotion->setGeometry(QRect(490, 180, 300, 30));
    bbyWash->setGeometry(QRect(490, 210, 300, 30));
    bbyPwder->setGeometry(QRect(490, 240, 300, 30));
    rshCreme->setGeometry(QRect(490, 270, 300, 30));
    tthBrsh->setGeometry(QRect(490, 300, 300, 30));
    tthPste->setGeometry(QRect(490, 330, 300, 30));
    bottles->setGeometry(QRect(490, 360, 300, 30));
    sippCups->setGeometry(QRect(490, 390, 300, 30));
    plstcPlates->setGeometry(QRect(490, 420, 300, 30));
    bthClothes->setGeometry(QRect(490, 450, 300, 30));
    bthSponges->setGeometry(QRect(490, 480, 300, 30));
    clothes->setGeometry(QRect(490, 510, 300, 30));
    clotheSize->setGeometry(QRect(720, 510, 300, 30));
    newClothes->setGeometry(QRect(510, 540, 300, 30));
    usedClothes->setGeometry(QRect(510, 560, 300, 30));
    socks->setGeometry(QRect(490, 590, 300, 30));
    shoes->setGeometry(QRect(490, 620, 300, 30));
    misc->setGeometry(QRect(490, 650, 300, 30));

//Spin Box Creation
    diaperNum = new QSpinBox(this);
    wipeNum = new QSpinBox(this);
    blanketNum = new QSpinBox(this);
    lotionNum = new QSpinBox(this);
    washNum = new QSpinBox(this);
    pwderNum = new QSpinBox(this);
    cremeNum = new QSpinBox(this);
    tthBrshNum = new QSpinBox(this);
    tthPsteNum = new QSpinBox(this);
    bottleNum = new QSpinBox(this);
    sippCupNum = new QSpinBox(this);
    plateNum = new QSpinBox(this);
    bthClothesNum = new QSpinBox(this);
    bthSpongeNum = new QSpinBox(this);
    clthesNum = new QSpinBox(this);
    socksNum = new QSpinBox(this);
    shoesNum = new QSpinBox(this);
    miscNum = new QSpinBox(this);

//Spin Box Position
    diaperNum->setGeometry(QRect(610, 90, 60, 30));
    wipeNum->setGeometry(QRect(610, 120, 60, 30));
    blanketNum->setGeometry(QRect(610, 150, 60, 30));
    lotionNum->setGeometry(QRect(610, 180, 60, 30));
    washNum->setGeometry(QRect(610, 210, 60, 30));
    pwderNum->setGeometry(QRect(610, 240, 60, 30));
    cremeNum->setGeometry(QRect(610, 270, 60, 30));
    tthBrshNum->setGeometry(QRect(610, 300, 60, 30));
    tthPsteNum->setGeometry(QRect(610, 330, 60, 30));
    bottleNum->setGeometry(QRect(610, 360, 60, 30));
    sippCupNum->setGeometry(QRect(610, 390, 60, 30));
    plateNum->setGeometry(QRect(610, 420, 60, 30));
    bthClothesNum->setGeometry(QRect(610, 450, 60, 30));
    bthSpongeNum->setGeometry(QRect(610, 480, 60, 30));
    clthesNum->setGeometry(QRect(610, 510, 60, 30));
    socksNum->setGeometry(QRect(610, 590, 60, 30));
    shoesNum->setGeometry(QRect(610, 620, 60, 30));
    miscNum->setGeometry(QRect(610, 650, 60, 30));

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
    diapersBox->addItems(diapersList);
//ComboBoxes Position
    clothesBox->setGeometry(QRect(830,510,100,30));
    diapersBox->setGeometry(QRect(830,90,100,30));
//CheckBoxes Creation
    newBox   = new QCheckBox(this);
    usedBox = new QCheckBox(this);
//CheckBoxes Position
    newBox->setGeometry(QRect(610, 543, 50, 20));
    usedBox->setGeometry(QRect(610, 565, 50, 20));


//Make Gender Exclusive
    clothesGroup = new QButtonGroup(this);
    clothesGroup->addButton(newBox);
    clothesGroup->addButton(usedBox);
    clothesGroup->setExclusive(true);


//Cancel/Ok buttons Creation
    okBtn       = new QPushButton(this);
    cancelBtn   = new QPushButton(this);

//Cancel/Ok buttons attributes
    okBtn->setText("Submit");
    cancelBtn->setText("Cancel");


//Cancel/Ok buttons Position
    okBtn->setGeometry(QRect(720, 650, 130, 40));
    cancelBtn->setGeometry(QRect(890, 650, 130, 40));

//Button signal/slots
    connect(cancelBtn,SIGNAL(clicked()),this,SLOT( close() ));
    connect(okBtn,SIGNAL( clicked() ),this,SLOT( giftSubmit() ));





//Fonts
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

    //Applied Fonts
    giftslbl->setFont(font);
    diapers->setFont(font2);
    diapSize->setFont(font2);
    wipes->setFont(font2);
    blankets->setFont(font2);
    bbyLotion->setFont(font2);
    bbyWash->setFont(font2);
    bbyPwder->setFont(font2);
    rshCreme->setFont(font2);
    tthBrsh->setFont(font2);
    tthPste->setFont(font2);
    bottles->setFont(font2);
    sippCups->setFont(font2);
    plstcPlates->setFont(font2);
    bthClothes->setFont(font2);
    bthSponges->setFont(font2);
    clothes->setFont(font2);
    clotheSize->setFont(font2);
    newClothes->setFont(font2);
    usedClothes->setFont(font2);
    socks->setFont(font2);
    shoes->setFont(font2);
    misc->setFont(font2);

}

gifts::~gifts()
{
    delete ui;
}

void gifts::giftSubmit()
{


    qDebug() << "Got user input";

    //Todays Date
        QDateTime today;
        today = QDateTime::currentDateTime();

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

    //This value is what I am working on at the moment.
        query.bindValue(":date", today);

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
        this->hide();
        return;
}
