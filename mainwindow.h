#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <QtSql/QSqlDatabase>
#include "dialog.h"
#include "demographics.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

    QPushButton *quitBtn ;
    QPushButton *conBtn ;
    QLabel *banner ;
    QLabel *cloud  ;
    QLabel *dbUserLb ;
    QLabel *dbPwdLb ;
    QLabel *dbNameLb ;
    QLabel *conStatuLb ;
    QLabel *dbAddressLb ;
    QLabel *dbPortLb ;
    QLineEdit *dbUserInput ;
    QLineEdit *dbPwdInput ;
    QLineEdit *dbNameInput ;
    QLineEdit *dbAddressInput ;
    QLineEdit *dbPortInput ;
    QSqlDatabase database ;
    Dialog login ;
private slots:

    void connect_db();
    void connect_quit();
};

#endif // MAINWINDOW_H
