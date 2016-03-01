/********************************************************************************
** Form generated from reading UI file 'demographics.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DEMOGRAPHICS_H
#define UI_DEMOGRAPHICS_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>

QT_BEGIN_NAMESPACE

class Ui_Demographics
{
public:

    void setupUi(QDialog *Demographics)
    {
        if (Demographics->objectName().isEmpty())
            Demographics->setObjectName(QStringLiteral("Demographics"));
        Demographics->resize(400, 300);

        retranslateUi(Demographics);

        QMetaObject::connectSlotsByName(Demographics);
    } // setupUi

    void retranslateUi(QDialog *Demographics)
    {
        Demographics->setWindowTitle(QApplication::translate("Demographics", "Dialog", 0));
    } // retranslateUi

};

namespace Ui {
    class Demographics: public Ui_Demographics {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DEMOGRAPHICS_H
