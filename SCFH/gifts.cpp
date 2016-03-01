#include "gifts.h"
#include "ui_gifts.h"

gifts::gifts(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::gifts)
{
    ui->setupUi(this);

//Table Creation
    table = new QTableView(this);
    table->setHorizontalHeader();
}

gifts::~gifts()
{
    delete ui;
}
