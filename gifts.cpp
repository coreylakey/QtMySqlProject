#include "gifts.h"
#include "ui_gifts.h"

gifts::gifts(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::gifts)
{
    ui->setupUi(this);



//Create Window / connections
    this->setWindowTitle("South Coast Family Harbor");



//Main Background Image
    QPixmap bkgnd("/home/corey/Desktop/QtProjects/SCFH/bg_tile.jpg");
    bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio);
    QPalette palette;
    palette.setBrush(QPalette::Background, bkgnd);
    this->setPalette(palette);

//Banner
    banner = new QLabel(this);
    QPixmap banner_pixmap("/home/corey/Desktop/QtProjects/SCFH/banner.png");
    banner->setPixmap(banner_pixmap);
    banner->setMinimumSize(180, 161);
    banner->setGeometry(QRect(100,10,0,0));









}

gifts::~gifts()
{
    delete ui;
}
