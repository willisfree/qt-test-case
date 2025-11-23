#include <QtWidgets>
#include "../include/mainwidget.h"
#include "../include/Ship.h"

int main(int argc, char *argv[])
{

    //Ship ship(10);  // 10 тонн

    //CargoBox(-234324, 434);
    CargoBox(1, 434);


  // Creates an instance of QApplication
  QApplication app(argc, argv);


  //MainWidget w = MainWidget(nullptr);

  // This is our MainWidget class containing our GUI and functionality
  MainWidget widget;

  //ShipInfo("Emerald", &widget);

  widget.show(); // Show main window

  // run the application and return execs() return value/code
  return app.exec();
}
