#ifndef GIFTS_H
#define GIFTS_H

#include <QDialog>
#include <QTableView>
#include <QLabel>
#include <QSpinBox>
#include <QCheckBox>
#include <QButtonGroup>
#include <QPushButton>

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
    QLabel *banner;
//Spin Boxes
    QSpinBox *diaperNum;
    QSpinBox *wipeNum;
    QSpinBox *blanketNum;
    QSpinBox *lotionNum;
    QSpinBox *washNum;
    QSpinBox *pwderNum;
    QSpinBox *cremeNum;
    QSpinBox *tthBrshNum;
    QSpinBox *tthPsteNum;
    QSpinBox *bottleNum;
    QSpinBox *sippCupNum;
    QSpinBox *plateNum;
    QSpinBox *bthClothesNum;
    QSpinBox *bthSpongeNum;
    QSpinBox *clthesNum;
    QSpinBox *socksNum;
    QSpinBox *shoesNum;
    QSpinBox *miscNum;
//CheckBoxes
    QCheckBox* newBox;
    QCheckBox* usedBox;
//CheckBox Button Group (For exclusive checking)
    QButtonGroup* clothesGroup;
//Cancel/Ok buttons
    QPushButton* okBtn;
    QPushButton* cancelBtn;


};

#endif // GIFTS_H
