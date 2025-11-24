#include <QtWidgets>
#include "../include/mainwidget.h"
#include "../include/Ship.h"




// debugging
#include <execinfo.h>
#include <stdio.h>

void printStackTrace() {
    const int maxFrames = 100;
    void *frames[maxFrames];
    int frameCount = backtrace(frames, maxFrames);
    char **frameStrings = backtrace_symbols(frames, frameCount);

    for (int i = 0; i < frameCount; ++i) {
        printf("%s\n", frameStrings[i]);
    }
    free(frameStrings);
}
//

int main(int argc, char *argv[])
{
  //Ship ship;

  // Creates an instance of QApplication
  QApplication app(argc, argv);


  //MainWidget w = MainWidget(nullptr);

  // This is our MainWidget class containing our GUI and functionality
  MainWidget widget(nullptr);

  widget.show(); // Show main window

  // run the application and return execs() return value/code
  return app.exec();
}
