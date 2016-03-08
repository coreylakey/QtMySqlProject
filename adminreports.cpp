#include "adminreports.h"
#include "ui_adminreports.h"

AdminReports::AdminReports(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AdminReports)
{
    ui->setupUi(this);
}

AdminReports::~AdminReports()
{
    delete ui;
}
