#ifndef GIFTS_H
#define GIFTS_H

#include <QDialog>
#include <QTableView>
#include <QLabel>

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

//Labels
    QLabel *diapers;
    QLabel *wipes;
    QLabel *blankets;
    QLabel *bbyLotion;
    QLabel *bbyWash;
    QLabel *bbyPwder;
    QLabel *rshCreme;
    QLabel *tthBrsh;
    QLabel *tthPste;
    QLabel *bottles;
    QLabel *sippCups;
    QLabel *plstcPlates;
    QLabel *bthClothes;
    QLabel *bthSponges;
    QLabel *clothes;
    QLabel *newClothes;
    QLabel *usedClothes;
    QLabel *socks;
    QLabel *shoes;
    QLabel *misc;
    QLabel *banner ;

};

#endif // GIFTS_H
