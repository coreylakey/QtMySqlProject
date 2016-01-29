#ifndef DEMOGRAPHICS_H
#define DEMOGRAPHICS_H

#include <QDialog>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <QtSql/QSqlDatabase>

namespace Ui {
class Demographics;
}

class Demographics : public QDialog
{
    Q_OBJECT

public:
    explicit Demographics(QWidget *parent = 0);
    ~Demographics();

private:
    Ui::Demographics *ui;

//Labels
    QLabel* fNamelbl;
    QLabel* lNamelbl;
    QLabel* addresslbl;
    QLabel* citylbl;
    QLabel* childInfolbl;
    QLabel* childAgelbl;
    QLabel* childGenderlbl;
    QLabel* clientInfolbl;
    QLabel* livSitlbl;
    QLabel* houseTypelbl;
    QLabel* incSrclbl;
    QLabel* heardlbl;
//LineEdits
    QLineEdit* fNameEdit;
    QLineEdit* lNameEdit;
    QLineEdit* addressEdit;
    //QLineEdit* cityEdit;          //Needs to be drop down menu
    //QLineEdit* childAgeEdit;      //Needs to be drop down menu
    //QLineEdit* childGenderEdit;   //Needs to be check boxes
    //QLineEdit* livSitEdit;        //Needs to be drop down menu
    //QLineEdit* houseTypeEdit;     //Needs to be drop down menu
    //QLineEdit* incSrcEdit;        //Needs to be drop down menu




};

#endif // DEMOGRAPHICS_H
