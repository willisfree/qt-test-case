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

static const char* numberOfCargos = "\320\232\320\276\320\273\320\270\321\207\320\265\321\201\321\202\320\262\320\276 \320\263\321\200\321\203\320\267\320\276\320\262: ";
static const char* commonWeight = "Общий вес: ";
static const char* commonPrice = "Общая стоимость: ";


static const char* boxWeightPLaceholder = "Вес груза: ";
static const char* boxPricePlaceholder = "Цена груза: ";



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

        QVBoxLayout *vbox = new QVBoxLayout;

        boxLabel = new QLabel(this);

        lineEdit = new QLineEdit(this);
        lineEdit_2 = new QLineEdit(this);
        pushButton = new QPushButton(this);
        totalLabel = new QLabel(this);
        totalWeight = new QLabel(this);
        totalPrice = new QLabel(this);


        lineEdit->setPlaceholderText(boxWeightPLaceholder);
        lineEdit_2->setPlaceholderText(boxPricePlaceholder);


        vbox->addWidget(boxLabel);
        vbox->addWidget(lineEdit);
        vbox->addWidget(lineEdit_2);
        vbox->addWidget(pushButton);
        vbox->addWidget(totalLabel);
        vbox->addWidget(totalWeight);
        vbox->addWidget(totalPrice);


        setLayout(vbox);

        retranslateUi(this);

        connect(this->pushButton, &QPushButton::clicked, this, &ThirdRow::addNewCargo);

      //ui.setupUi(this);
    }

    void retranslateUi(QWidget *Form)
    {
        boxLabel->setText(QCoreApplication::translate("ThirdRow", "\320\223\321\200\321\203\320\267", nullptr));
        totalWeight->setText(commonWeight);
        totalPrice->setText(commonPrice);
        pushButton->setText(QCoreApplication::translate("ThirdRow", "+", nullptr));
        totalLabel->setText(QCoreApplication::translate("ThirdRow", numberOfCargos, nullptr));
    } // retranslateUi


private slots:
    void addNewCargo() {
        int extractedWeight = Algos::firstIntFromStr(this->lineEdit->text().toUtf8().constData());
        int extractePrice = Algos::firstIntFromStr(this->lineEdit_2->text().toUtf8().constData());


        if (extractedWeight < 0 || extractePrice < 0) {
          try {
            throw IndexErr("Вес и стоимость груза должны быть указаны числом. Проверьре корректность введённых данных");
          } catch (...) {
              std::cerr << "Ошибка при добавлении груза. Пропуск операции.\n";
              return;
            //показывать ошибку красным. // WIP
          }
        }

        boxes.push_back(CargoBox{extractedWeight, extractePrice});
        updateLabels();
    

        QString bwp = QString(QString(boxWeightPLaceholder) + ": %1").arg(extractedWeight);
        lineEdit->setText(bwp);

        QString bpp = QString(QString(boxPricePlaceholder) + ": %1").arg(extractePrice);
        lineEdit_2->setText(bpp);
    }

private:
  void updateLabels() {
      QString totalVal = QString(QString(numberOfCargos) + ": %1").arg(boxes.size());
      totalLabel->setText(QCoreApplication::translate("ThirdRow", totalVal.toUtf8().constData(), nullptr));

      totalVal = QString(QString(commonWeight) + ": %1").arg(boxes.size());
      totalWeight->setText(QCoreApplication::translate("ThirdRow", totalVal.toUtf8().constData(), nullptr));
      
      totalVal = QString(QString(commonPrice) + ": %1").arg(boxes.size());
      totalPrice->setText(QCoreApplication::translate("ThirdRow", totalVal.toUtf8().constData(), nullptr));


  }

private:
  QLabel *boxLabel;
  QLineEdit *lineEdit;
  QLineEdit *lineEdit_2;
  QPushButton *pushButton;

  QLabel *totalLabel;
  QLabel *totalWeight;
  QLabel *totalPrice;

  QVector<CargoBox> boxes;
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
