#include "gifts.h"
#include "ui_gifts.h"

gifts::gifts(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::gifts)
{
    ui->setupUi(this);



//Create Window / connections
    this->setWindowTitle("South Coast Family Harbor");













}

gifts::~gifts()
{
    delete ui;
}
