#ifndef DEMOGRAPHICS_H
#define DEMOGRAPHICS_H

#include <QDialog>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <QtSql/QSqlDatabase>
#include <QSpinBox>
#include <QComboBox>
#include <QCheckBox>
#include <QButtonGroup>
#include <QMessageBox>
#include <QDebug>
#include "gifts.h"


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
//New Gifts Window
    gifts giftWindow;
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
//ComboBoxes
    QComboBox* cityEdit;
    QComboBox* childAgeEdit;
    QComboBox* livSitEdit;
    QComboBox* houseTypeEdit;
    QComboBox* incSrcEdit;
    QComboBox* howHeardEdit;
//CheckBoxes
    QCheckBox* maleBox;
    QCheckBox* femaleBox;
//CheckBox Button Group (For exclusive checking)
    QButtonGroup* genderGroup;
//Cancel/Ok buttons
    QPushButton* okBtn;
    QPushButton* cancelBtn;

private slots:

    void sendInfo();
    void cancel();
    void startQuery();





};

#endif // DEMOGRAPHICS_H
