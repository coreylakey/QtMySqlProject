#include "adminreports.h"
#include "ui_adminreports.h"
#include <QSqlQuery>
#include <QDebug>
#include <QSqlDatabase>
#include <QSqlRecord>


AdminReports::AdminReports(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AdminReports)
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




//Labels
    adminlbl = new QLabel("Admin Reports",this);
    clientLbl = new QLabel("How many clients", this);
    secClientLbl = new QLabel("", this);
    giftLbl = new QLabel("got", this);
    result = new QLabel("Total: 0", this);
    fromLbl = new QLabel("From:", this);
    toLbl = new QLabel("To:", this);
    dateLbl = new QLabel("Use Dates?", this);


//Labels Positions
    adminlbl->setGeometry(QRect(400,50,300,30));
    clientLbl->setGeometry(QRect(490,90,300,30));
    secClientLbl->setGeometry(QRect(490,130,300,30));
    giftLbl->setGeometry(QRect(490,170,300,30));
    result->setGeometry(QRect(430,600,300,30));
    fromLbl->setGeometry(QRect(560, 270, 50, 30));
    toLbl->setGeometry(QRect(910, 270, 50, 30));
    dateLbl->setGeometry(QRect(490, 210, 300, 30));
//Label Fonts
    adminlbl->setStyleSheet("QLabel{font : bold 24px}");
    clientLbl->setStyleSheet("QLabel {font : bold 15px;}");
    secClientLbl->setStyleSheet("QLabel {font : bold 15px;}");
    giftLbl->setStyleSheet("QLabel {font : bold 15px;}");
    result->setStyleSheet("QLabel {font : bold 24px;}");
    fromLbl->setStyleSheet("QLabel {font : bold 18px;}");
    toLbl->setStyleSheet("QLabel {font : bold 18px;}");
    dateLbl->setStyleSheet("QLabel {font : bold 15px;}");
//CheckBoxes Creation
    yesBox   = new QCheckBox(this);
    noBox = new QCheckBox(this);
//CheckBoxes Attributes
    yesBox->setGeometry(QRect(650, 210, 50, 30));
    yesBox->setText("Yes");
    noBox->setGeometry(QRect(710, 210, 50, 30));
    noBox->setText("No");
//Make Gender Exclusive
    dateGroup = new QButtonGroup(this);
    dateGroup->addButton(yesBox);
    dateGroup->addButton(noBox);
    dateGroup->setExclusive(true);
//ComboBoxes
    clientEdit = new QComboBox(this);
    secClientEdit = new QComboBox(this);
    giftEdit = new QComboBox(this);
//ComboBox Positions
    clientEdit->setGeometry(QRect(650,90,300,30));
    secClientEdit->setGeometry(QRect(650,130,300,30));
    giftEdit->setGeometry(QRect(650,170,300,30));
//Populate the ComboBoxes
    QStringList clientList;
    QStringList giftList;
//One of these lists will populate secCLientList once they have chosen a criteria in clientList
    clientList      << "Total" << "City" << "Living Situation" << "Housing Type" << "Income Source" << "How Heard" << "Child Age" << "Child Gender";
//Gifts they can query by:
    giftList << "Total" << "Diapers" << "Wipes" << "Blankets" << "Baby Lotion" << "Baby Wash" << "Baby Powder" << "Diaper Cream" << "Toothbrushes" << "Toothpaste" << "Bottles" << "Sippy Cups" << "Plastic Plates"
             << "Clothes" << "Socks" << "Shoes" << "Misc.";
//Put strings into ComboBoxes
    clientEdit->addItems(clientList);
    giftEdit->addItems(giftList);
    // secClientEdit will be populated depending on which criteria is entered in cliendEdit.

//Calendar Creation and Position
    fromCalendar = new QCalendarWidget(this);
    fromCalendar->setGeometry(QRect(430, 300, 300, 250));
    toCalendar = new QCalendarWidget(this);
    toCalendar->setGeometry(QRect(780, 300, 300, 250));

//Buttons
    run = new QPushButton(this);
    cancel = new QPushButton(this);
    csvExport = new QPushButton(this);
//Button Positions
    run->setGeometry(QRect(800,600,150,30));
    cancel->setGeometry(QRect(950,600,150,30));
    csvExport->setGeometry(QRect(1100,600,150,30));
//Button Text
    run->setText("Run Query");
    cancel->setText("Cancel");
    csvExport->setText("Export");

//Prepare for usage.
    secClientLbl->hide();
    giftLbl->hide();
    secClientEdit->hide();
    giftEdit->hide();
    dateLbl->hide();
    fromLbl->hide();
    toLbl->hide();
    fromCalendar->hide();
    toCalendar->hide();
    yesBox->hide();
    noBox->hide();

//CONNECTIONS
    connect(this->clientEdit,SIGNAL( currentIndexChanged(int)),this,SLOT( firstClientChange() ));
    connect(this->run, SIGNAL( clicked()), this, SLOT( runQuery() ));
    connect(this->cancel, SIGNAL( clicked()),this, SLOT(close() ));
    connect(this->dateGroup, SIGNAL(buttonClicked(int)),this, SLOT( setCalendar() ));
    connect(this->csvExport, SIGNAL(clicked()),this, SLOT( exportToCSV() ));
}

void AdminReports::exportToCSV()
{
    // MySql only has access to tmp folder. the query is : SELECT * INTO OUTFILE '/tmp/result.csv' FIELDS TERMINATED BY ',' OPTIONALLY ENCLOSED BY '"' LINES TERMINATED BY '\n' FROM clients;
    // You can only do csv dumps like this one table at a time.. so each table will need to be dumped and then individually loaded to excel.

    QSqlQuery exQuery;
    exQuery.prepare("SELECT * INTO OUTFILE '/tmp/clientTable.csv' FIELDS TERMINATED BY ',' OPTIONALLY ENCLOSED BY '\"' LINES TERMINATED BY '\n' FROM clients;");
    exQuery.exec();
    exQuery.prepare("SELECT * INTO OUTFILE '/tmp/giftsTable.csv' FIELDS TERMINATED BY ',' OPTIONALLY ENCLOSED BY '\"' LINES TERMINATED BY '\n' FROM gifts;");
    exQuery.exec();

    return;

}

void AdminReports::runQuery()
{
    if( yesBox->isChecked())
    {
        runDateQuery();
    }
    else if( noBox->isChecked())
    {
        runNonDateQuery();
    }

    return;
}

void AdminReports::setCalendar()
{
    if( yesBox->isChecked() )
    {
        fromCalendar->show();
        toCalendar->show();
        fromLbl->show();
        toLbl->show();
    }
    else if( noBox->isChecked() )
    {
        fromCalendar->hide();
        toCalendar->hide();
        fromLbl->hide();
        toLbl->hide();
    }

    return;

}
void AdminReports::runDateQuery()
{
    QSqlQuery       dateQuery;
    QDate           fromDate;
    QDate           toDate;
    QString         firstArgText, secondArgText, giftText;
    QString         fromDateString, toDateString;
    int             firstArgIndex, giftIndex;
//Get Dates
    fromDate    = fromCalendar->selectedDate();
    toDate      = toCalendar->selectedDate();
    fromDateString  = fromDate.toString("yyyy-MM-dd");
    toDateString    = toDate.toString("yyyy-MM-dd");
    qDebug() << "From Date is " + fromDateString + " and To Date is " + toDateString;

//Get sql database text equivalent to what user sees
    firstArgIndex   = clientEdit->currentIndex();
    giftIndex       = giftEdit->currentIndex();

    switch( firstArgIndex )
    {
        case 0:
            break;
        case 1:
            firstArgText = "clients.city";
            break;
        case 2:
            firstArgText = "clients.livingSit";
            break;
        case 3:
            firstArgText = "clients.housingType";
            break;
        case 4:
            firstArgText = "clients.incomeSource";
            break;
        case 5:
            firstArgText = "clients.howHeard";
            break;
        case 6:
            firstArgText = "clients.childAge";
            break;
        case 7:
            firstArgText = "clients.childGender";
            break;
        default:
            break;

    }
    //Text as user sees it is same that goes into database.
            if( secClientEdit->currentText() == "Male")
                secondArgText = "'M'";
            else if( secClientEdit->currentText() == "Female")
                secondArgText = "'F'";
            else
                secondArgText = '"' +  secClientEdit->currentText() + '"';
//Now for gifts text as it is in database.
    giftIndex = giftEdit->currentIndex();

    switch( giftIndex )
    {
        case 0:
            break;
        case 1:
            giftText = "diapers";
            break;
        case 2:
            giftText = "wipes";
            break;
        case 3:
            giftText = "blankets";
            break;
        case 4:
            giftText = "babyLotion";
            break;
        case 5:
            giftText = "babyWash";
            break;
        case 6:
            giftText = "babyPowder";
            break;
        case 7:
            giftText = "diaperCream";
            break;
        case 8:
            giftText = "toothbrushes";
            break;
        case 9:
            giftText = "toothpaste";
            break;
        case 10:
            giftText = "bottles";
            break;
        case 11:
            giftText = "sippyCups";
            break;
        case 12:
            giftText = "plasticPlates";
            break;
        case 13:
            giftText = "clothes";
            break;
        case 14:
            giftText = "socks";
            break;
        case 15:
            giftText = "shoes";
            break;
        case 16:
            giftText = "misc";
            break;
        default:
            break;

    }
    if( giftEdit->currentIndex() == 0  && clientEdit->currentIndex() != 0 )
    {
        qDebug() << "firstArgText is: " + firstArgText + " and secondArgText is: " + secondArgText;
            qDebug() << "From Date is " + fromDateString + " and To Date is " + toDateString;

        dateQuery.prepare(QString("SELECT COUNT(*) FROM clients LEFT JOIN gifts ON clients.clientID = gifts.clientID WHERE gifts.giftDate between :fromDate and :toDate AND %1 = %2;").arg(firstArgText).arg(secondArgText));
        dateQuery.bindValue(":fromDate", fromDateString);
        dateQuery.bindValue(":toDate", toDateString);
        dateQuery.exec();

        qDebug() << "Last Query Was " + dateQuery.lastQuery();
        qDebug() << "Executed Query Was " + dateQuery.executedQuery();
        //Deal with the query
        QSqlRecord rec = dateQuery.record();
        int countIndex = rec.indexOf("COUNT(*)"); // index of the field "clientID"
        QString count;

        //Get query results
        while(dateQuery.next())
        {
            //Put query results into ints.
            count = dateQuery.value(countIndex).toString();
            qDebug() << count;
        }

        result->setText("Total: " +  count );
    }
    else if( giftEdit->currentIndex() != 0 && clientEdit->currentIndex() != 0 )
    {
        dateQuery.prepare(QString("SELECT COUNT(*) FROM clients LEFT JOIN gifts ON clients.clientID = gifts.clientID WHERE gifts.giftDate between :fromDate and :toDate AND %1 > 0 AND %2 = %3;").arg("gifts." + giftText).arg(firstArgText).arg(secondArgText));
        dateQuery.bindValue(":fromDate", fromDateString);
        dateQuery.bindValue(":toDate", toDateString);
        dateQuery.exec();
        qDebug() << "Last Query Was " + dateQuery.lastQuery();
        qDebug() << "Executed Query Was " + dateQuery.executedQuery();
        //Deal with the query
        QSqlRecord rec = dateQuery.record();
        int countIndex = rec.indexOf("COUNT(*)"); // index of the field "clientID"
        QString count;

        //Get query results
        while(dateQuery.next())
        {
            //Put query results into ints.
            count = dateQuery.value(countIndex).toString();
        }

        result->setText("Total: " +  count );
    }
    else if( giftEdit->currentIndex() == 0 && clientEdit->currentIndex() == 0 )
    {
        dateQuery.prepare("SELECT COUNT(*) FROM clients LEFT JOIN gifts ON clients.clientID = gifts.clientID WHERE gifts.giftDate between :fromDate and :toDate;");
        dateQuery.bindValue(":fromDate", fromDateString);
        dateQuery.bindValue(":toDate", toDateString);
        dateQuery.exec();
        qDebug() << "Last Query Was " + dateQuery.lastQuery();
        qDebug() << "Executed Query Was " + dateQuery.executedQuery();

        //Deal with the query
        QSqlRecord rec = dateQuery.record();
        int countIndex = rec.indexOf("COUNT(*)"); // index of the field "clientID"
        QString count;

        //Get query results
        while(dateQuery.next())
        {
            //Put query results into ints.
            count = dateQuery.value(countIndex).toString();
        }
        qDebug() << "The count is " + count;
        result->setText("Total: " +  count );
    }
    else if( giftEdit->currentIndex() != 0 && clientEdit->currentIndex() == 0 )
    {
        dateQuery.prepare(QString("SELECT COUNT(*) FROM clients LEFT JOIN gifts ON clients.clientID = gifts.clientID WHERE gifts.giftDate between :fromDate and :toDate and %1 > 0;").arg("gifts." + giftText));
        dateQuery.bindValue(":fromDate", fromDateString);
        dateQuery.bindValue(":toDate", toDateString);
        dateQuery.exec();
        qDebug() << "Last Query Was " + dateQuery.lastQuery();
        qDebug() << "Executed Query Was " + dateQuery.executedQuery();
        qDebug() << "giftText is " + giftText;


        //Deal with the query
        QSqlRecord rec = dateQuery.record();
        int countIndex = rec.indexOf("COUNT(*)"); // index of the field "clientID"
        QString count;

        //Get query results
        while(dateQuery.next())
        {
            //Put query results into strings
            count = dateQuery.value(countIndex).toString();
        }

        result->setText("Total: " +  count );

    }
}

void AdminReports::runNonDateQuery()
{
    QSqlQuery nonDateQuery;
    QDate       fromDate;
    QDate       toDate;
    QString     firstArgText, secondArgText, giftText;
    int         firstArgIndex, giftIndex;


//Get sql database text equivalent to what user sees
    firstArgIndex   = clientEdit->currentIndex();
    giftIndex       = giftEdit->currentIndex();

    switch( firstArgIndex )
    {
        case 0:
            break;
        case 1:
            firstArgText = "clients.city";
            break;
        case 2:
            firstArgText = "clients.livingSit";
            break;
        case 3:
            firstArgText = "clients.housingType";
            break;
        case 4:
            firstArgText = "clients.incomeSource";
            break;
        case 5:
            firstArgText = "clients.howHeard";
            break;
        case 6:
            firstArgText = "clients.childAge";
            break;
        case 7:
            firstArgText = "clients.childGender";
            break;
        default:
            break;

    }

//Text as user sees it is same that goes into database.
        if( secClientEdit->currentText() == "Male")
            secondArgText = "'M'";
        else if( secClientEdit->currentText() == "Female")
            secondArgText = "'F'";
        else
            secondArgText = '"' +  secClientEdit->currentText() + '"';
//Now for gifts text as it is in database.
    giftIndex = giftEdit->currentIndex();

    switch( giftIndex )
    {
        case 0:
            break;
        case 1:
            giftText = "gifts.diapers";
            break;
        case 2:
            giftText = "gifts.wipes";
            break;
        case 3:
            giftText = "gifts.blankets";
            break;
        case 4:
            giftText = "gifts.babyLotion";
            break;
        case 5:
            giftText = "gifts.babyWash";
            break;
        case 6:
            giftText = "gifts.babyPowder";
            break;
        case 7:
            giftText = "gifts.diaperCream";
            break;
        case 8:
            giftText = "gifts.toothbrushes";
            break;
        case 9:
            giftText = "gifts.toothpaste";
            break;
        case 10:
            giftText = "gifts.bottles";
            break;
        case 11:
            giftText = "gifts.sippyCups";
            break;
        case 12:
            giftText = "gifts.plasticPlates";
            break;
        case 13:
            giftText = "gifts.clothes";
            break;
        case 14:
            giftText = "gifts.socks";
            break;
        case 15:
            giftText = "gifts.shoes";
            break;
        case 16:
            giftText = "gifts.misc";
            break;
        default:
            break;

    }
    if( clientEdit->currentIndex() == 0 && giftEdit->currentIndex() == 0 )
    {
        nonDateQuery.prepare("SELECT COUNT(*) FROM clients LEFT JOIN gifts ON clients.clientID = gifts.clientID;");
        nonDateQuery.exec();

        qDebug() << "Last Query Was " + nonDateQuery.lastQuery();

        //Deal with the query
        QSqlRecord rec = nonDateQuery.record();
        int countIndex = rec.indexOf("COUNT(*)"); // index of the field "clientID"
        QString count;

        //Get query results
        while(nonDateQuery.next())
        {
            //Put query results into ints.
            count = nonDateQuery.value(countIndex).toString();
        }

        result->setText("Total: " +  count );
    }
    else if( clientEdit->currentIndex() == 0 && giftEdit->currentIndex() != 0 )
    {
        nonDateQuery.prepare(QString("SELECT COUNT(*) FROM clients LEFT JOIN gifts ON clients.clientID = gifts.clientID WHERE %1 > 0;").arg(giftText));
        nonDateQuery.exec();

        qDebug() << "Last Query Was " + nonDateQuery.lastQuery();

        //Deal with the query
        QSqlRecord rec = nonDateQuery.record();
        int countIndex = rec.indexOf("COUNT(*)"); // index of the field "clientID"
        QString count;

        //Get query results
        while(nonDateQuery.next())
        {
            //Put query results into ints.
            count = nonDateQuery.value(countIndex).toString();
        }

        result->setText("Total: " +  count );

    }
    else if( clientEdit->currentIndex() != 0 && giftEdit->currentIndex() == 0 )
    {
        nonDateQuery.prepare(QString("SELECT COUNT(*) FROM clients LEFT JOIN gifts ON clients.clientID = gifts.clientID WHERE %1 = %2;").arg(firstArgText).arg(secondArgText));
        nonDateQuery.exec();

        qDebug() << "Last Query Was " + nonDateQuery.lastQuery();

        //Deal with the query
        QSqlRecord rec = nonDateQuery.record();
        int countIndex = rec.indexOf("COUNT(*)"); // index of the field "clientID"
        QString count;

        //Get query results
        while(nonDateQuery.next())
        {
            //Put query results into ints.
            count = nonDateQuery.value(countIndex).toString();
        }

        result->setText("Total: " +  count );
    }
    else if( clientEdit->currentIndex() != 0 && giftEdit->currentIndex() != 0 )
    {
        nonDateQuery.prepare(QString("SELECT COUNT(*) FROM clients LEFT JOIN gifts ON clients.clientID = gifts.clientID WHERE %1 = %2 AND %3 > 0;").arg(firstArgText).arg(secondArgText).arg(giftText));
        nonDateQuery.exec();

        qDebug() << "Last Query Was " + nonDateQuery.lastQuery();

        //Deal with the query
        QSqlRecord rec = nonDateQuery.record();
        int countIndex = rec.indexOf("COUNT(*)"); // index of the field "clientID"
        QString count;

        //Get query results
        while(nonDateQuery.next())
        {
            //Put query results into ints.
            count = nonDateQuery.value(countIndex).toString();
        }

        result->setText("Total: " +  count );
    }

    return;

}

void AdminReports::firstClientChange()
{
    QStringList cityList;
    QStringList childAgeList;
    QStringList livSitList;
    QStringList houseTypeList;
    QStringList incSrcList;
    QStringList howHeardList;
    QStringList childGenderList;
    cityList        << "CB" << "NB" << "MP" << "CQ" << "BN" << "LKS" << "REED" << "P.O." << "Powers" << "Other";
    childAgeList    << "Prenatal" << "1mo" << "2mo" << "3mo" << "4mo" << "5mo" << "6mo" << "24mo" << "3 years" << "4 years" << "5 years" << "6 years";
    livSitList      << "Friends" << "Family" << "Self";
    houseTypeList   << "HVD" << "Rent" << "Own";
    incSrcList      << "TANF" << "Work" << "SNAP" << "Child Support" << "Foster Care" << "Disability" << "Self-Employed" << "Unemployment" << "Alimony" << "None";
    howHeardList    << "Friend" << "Family" << "Newmark Center" << "HeadStart" << "Maslow" << "Local Ads" << "Facebook" << "Other";
    childGenderList << "Male" << "Female";

    int index = clientEdit->currentIndex();
    switch( index )
    {
        case 0:
            secClientEdit->hide();
            secClientEdit->clear();
            secClientLbl->setText("In total...");
            return;
            break;
        case 1:
            secClientLbl->setText("Are From");
            secClientEdit->clear();
            secClientEdit->addItems(cityList);
            break;
        case 2:
            secClientLbl->setText("Living Situation is");
            secClientEdit->clear();
            secClientEdit->addItems(livSitList);
            break;
        case 3:
            secClientLbl->setText("Housing Situation is");
            secClientEdit->clear();
            secClientEdit->addItems(houseTypeList);
            break;
        case 4:
            secClientLbl->setText("Income Source is");
            secClientEdit->clear();
            secClientEdit->addItems(incSrcList);
            break;
        case 5:
            secClientLbl->setText("Heard About us by");
            secClientEdit->clear();
            secClientEdit->addItems(howHeardList);
            break;
        case 6:
            secClientLbl->setText("Childs Age is");
            secClientEdit->clear();
            secClientEdit->addItems(childAgeList);
            break;
        case 7:
            secClientLbl->setText("Childs Gender is");
            secClientEdit->clear();
            secClientEdit->addItems(childGenderList);
            break;
        default:
            break;
    }

    secClientLbl->show();
    secClientEdit->show();
    giftLbl->show();
    giftEdit->show();
    dateLbl->show();
    yesBox->show();
    noBox->show();
}

AdminReports::~AdminReports()
{
    delete ui;
}
