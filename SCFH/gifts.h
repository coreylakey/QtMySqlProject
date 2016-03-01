#ifndef GIFTS_H
#define GIFTS_H

#include <QDialog>
#include <QTableView>

namespace Ui {
class gifts;
}

class gifts : public QDialog
{
    Q_OBJECT
    
public:
    explicit gifts(QWidget *parent = 0);
    ~gifts();
    
private:
    Ui::gifts *ui;

    QTableView *table;

};

#endif // GIFTS_H
