/********************************************************************************
** Form generated from reading UI file 'untitled.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CARGO_H
#define UI_CARGO_H

void printStackTrace();

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Form
{
public:
    QGroupBox *groupBox;
    QLineEdit *lineEdit;
    QLineEdit *lineEdit_2;
    QPushButton *pushButton;
    QLabel *label;

    void setupUi(QWidget *Form)
    {
        //std::cout << "FOOOOOOR: " << Form->objectName().toUtf8().constData() << '\n';
        std::cout << "FOOOOOOR: " << Form->objectName().isEmpty() << '\n';


        if (Form->objectName().isEmpty())
            Form->setObjectName(QString::fromUtf8("Form"));
        //Form->resize(477, 358);
        groupBox = new QGroupBox(Form);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setGeometry(QRect(30, 60, 261, 151));
        lineEdit = new QLineEdit(groupBox);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));
        lineEdit->setGeometry(QRect(30, 50, 131, 31));
        lineEdit_2 = new QLineEdit(groupBox);
        lineEdit_2->setObjectName(QString::fromUtf8("lineEdit_2"));
        lineEdit_2->setGeometry(QRect(30, 100, 131, 31));
        pushButton = new QPushButton(groupBox);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(190, 20, 41, 31));
        label = new QLabel(Form);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(290, 260, 151, 31));

        QVBoxLayout *vbox = new QVBoxLayout;
        vbox->addStretch(1);
        groupBox->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        groupBox->setLayout(vbox);

        //groupBox->show();

        //printStackTrace();

        retranslateUi(Form);

        //QMetaObject::connectSlotsByName(Form);
    } // setupUi

    void retranslateUi(QWidget *Form)
    {
        Form->setWindowTitle(QCoreApplication::translate("Form", "Form", nullptr));
        groupBox->setTitle(QCoreApplication::translate("Form", "\320\223\321\200\321\203\320\267", nullptr));
        pushButton->setText(QCoreApplication::translate("Form", "+", nullptr));
        label->setText(QCoreApplication::translate("Form", "\320\232\320\276\320\273\320\270\321\207\320\265\321\201\321\202\320\262\320\276 \320\263\321\200\321\203\320\267\320\276\320\262: ", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Form: public Ui_Form {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CARGO_H
