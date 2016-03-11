#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
//#include <QtWidgets>
//#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <QtSql/QSqlDatabase>
#include "demographics.h"
#include "adminreports.h"

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = 0);
    ~Dialog();

private:
    void createFormGroupBox();

    Ui::Dialog *ui;


    QLabel *banner;
    QLabel *bottom;
    QLabel *userLbl;
    QLabel *passLbl;
    QLineEdit *userEdit;
    QLineEdit *passEdit;
    QPushButton *okBtn;
    Demographics demoGraph;
    AdminReports adminPage;



private slots:

    void getUser();
};

#endif // DIALOG_H
