#ifndef DEMOGRAPHICS_H
#define DEMOGRAPHICS_H

#include <QDialog>

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
};

#endif // DEMOGRAPHICS_H
