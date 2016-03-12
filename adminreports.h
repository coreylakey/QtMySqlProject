#ifndef ADMINREPORTS_H
#define ADMINREPORTS_H

#include <QDialog>
#include <QLabel>
#include <QSpinBox>
#include <QComboBox>
#include <QPushButton>
#include <QCalendarWidget>
#include <QButtonGroup>
#include <QCheckBox>

namespace Ui {
class AdminReports;
}

class AdminReports : public QDialog
{
    Q_OBJECT

public:
    explicit AdminReports(QWidget *parent = 0);
    ~AdminReports();

    void runDateQuery();
    void runNonDateQuery();

private:
    Ui::AdminReports *ui;

//Labels
    QLabel *clientLbl;
    QLabel *secClientLbl;
    QLabel *giftLbl;
    QLabel *fromLbl;
    QLabel *toLbl;
    QLabel *dateLbl;
    QLabel *result;
    QLabel *bottomImg;
    QLabel *adminlbl;
//ComboBoxes
    QComboBox *clientEdit;
    QComboBox *secClientEdit;
    QComboBox *giftEdit;
//Buttons
    QPushButton *run;
    QPushButton *cancel;
    QPushButton *csvExport;
//Calendar Attempt
    QCalendarWidget *fromCalendar;
    QCalendarWidget *toCalendar;
//CheckBoxes
    QCheckBox *yesBox;
    QCheckBox *noBox;
//Button Groups
    QButtonGroup *dateGroup;


private slots:
    void firstClientChange();
    void setCalendar();
    void runQuery();
    void exportToCSV();

};

#endif // ADMINREPORTS_H
