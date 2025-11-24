#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>
#include <QProcess>
#include <QLabel>

#include <QApplication>
#include <QWidget>
#include <QPushButton>
#include <QLineEdit>
#include <QVBoxLayout>


#include "./Ship.h"
#include "./Algos.h"

#include "./ui_cargo.h"

//#include <string>

class QPushButton;
class QTextBrowser;



static const char* liftingPlaceholder = "Грзоподъёмность судна (в тоннах)";
static const char* liftingErr = "Максимальная грузоподъёмность судна не должа превышать 10 000 тонн";

static const char* boxWeightPLaceholder = "Вес груза.";
static const char* boxPriceLaceholder = "Цена груза";



class CustomInput : public QWidget {
  Q_OBJECT
public:
  CustomInput(const QString& placeholder, QWidget* parent)
    : QWidget(parent), placeholder{placeholder}
  {
        layout = new QHBoxLayout(this);
        //layout->addStretch(0);

        // Создаем текстовое поле
        lineEdit = new QLineEdit(this);
        lineEdit->setPlaceholderText(placeholder);
        layout->addWidget(lineEdit);

        button = new QPushButton("Обновить", this);
        layout->addWidget(button);

         connect(this->button, &QPushButton::pressed, this, &CustomInput::saveText);
  }

private slots:
  virtual void updateText() {
        int extractedNumber = Algos::firstIntFromStr(this->lineEdit->text().toUtf8().constData());

        QString filledPLaceholder = QString(placeholder + ": %1").arg(extractedNumber);
        lineEdit->setText(filledPLaceholder);

        qDebug() << "Текущий PLACEHOLDER:" << filledPLaceholder;
    }

    virtual void saveText() {
      lastQlineState = this->lineEdit->text();

      qDebug() << "Текущий СТАТ:" << lastQlineState;

    }

protected:
  QString lastQlineState;
  const QString placeholder;

  QLineEdit* lineEdit;
  QPushButton* button;
  QHBoxLayout* layout;
};



class SecondRow : public CustomInput {
    Q_OBJECT
public:
    SecondRow(const QString& placeholder, QWidget* parent)
    : CustomInput(placeholder, parent)
    {
        // Подключаем сигнал clicked() к нашему слоту обновления текста
        connect(this->button, &QPushButton::clicked, this, &SecondRow::updateText);
    }

private slots:
    void updateText() override {
        int extractedShipCap = Algos::firstIntFromStr(this->lineEdit->text().toUtf8().constData());
        if (extractedShipCap > 10000) {
          throw LogicErr(liftingErr);
        }
        ship.updateCap(extractedShipCap);

        QString liftingInfo = QString(placeholder + ": %1").arg(extractedShipCap);
        lineEdit->setText(liftingInfo);

        qDebug() << "Текущий КАП:" << ship.getCap();
    }

private:
    Ship ship;
};


class ThirdRow : public QWidget {
    Q_OBJECT
public:
    ThirdRow(QWidget* parent)
    : QWidget(parent)
    {
      //QHBoxLayout* layout = new QHBoxLayout(this);
      ui.setupUi(this);
    }

private:
    Ui::Form ui;
};


class ShipInfo : public QLabel {
    Q_OBJECT

public:
        explicit ShipInfo(const QString& str, QWidget* parent = 0);
        ~ShipInfo();

private:
        //path to picture. :) just fun task for me
        QString modelName;
};

// This is the declaration of our MainWidget class
// The definition/implementation is in mainwidget.cpp
class MainWidget : public QWidget {
  Q_OBJECT

public:
  explicit MainWidget(QWidget *parent = 0); //Constructor
  ~MainWidget(); // Destructor

private slots:
  void onButtonReleased(); // Handler for button presses
  void onCaptureProcessOutput(); // Handler for Process output

private:
  QPushButton*  button_;
  QTextBrowser* textBrowser_;
  QProcess      process_;   // This is the process the button will fire off

  SecondRow* secRow;
  ThirdRow* thirdRow;

  ShipInfo* shipData_;
};

#endif // MAINWIDGET_H
