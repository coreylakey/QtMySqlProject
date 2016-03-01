#ifndef ADMINREPORTS_H
#define ADMINREPORTS_H

#include <QDialog>

namespace Ui {
class AdminReports;
}

class AdminReports : public QDialog
{
    Q_OBJECT

public:
    explicit AdminReports(QWidget *parent = 0);
    ~AdminReports();

private:
    Ui::AdminReports *ui;
};

#endif // ADMINREPORTS_H
