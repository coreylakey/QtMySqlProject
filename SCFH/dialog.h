#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <QtSql/QSqlDatabase>

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
    Ui::Dialog *ui;

    QLabel *userLbl;
    QLabel *passLbl;
    QLineEdit *userEdit;
    QLineEdit *passEdit;
    QPushButton *okBtn;

private slots:

    void getUser();
};

#endif // DIALOG_H
