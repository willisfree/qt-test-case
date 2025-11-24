#include <QtWidgets>
#include "../include/mainwidget.h"

ShipInfo::ShipInfo(const QString& str, QWidget *parent) :
    QLabel(str, parent), modelName{str}
    {
        //setPic(default path)
    }

ShipInfo::~ShipInfo() {
    std::cout << "when called\nresearch";
}

// Constructor for main window
MainWidget::MainWidget(QWidget *parent) :
    QWidget(parent)
{
  button_       = new QPushButton(tr("Push Me!"), this);
  textBrowser_  = new QTextBrowser(); // pass this and see fun in left angle/ why?
  secRow       = new SecondRow(liftingPlaceholder, this);
  shipData_     = new ShipInfo("Emerald", this);
  thirdRow      = new ThirdRow(this);

  //sec_row->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
  //sec_row->setMinimumHeight(50);

  QGridLayout *mainLayout = new QGridLayout();
  mainLayout->setRowStretch(0, 1);
  //mainLayout->setColumnStretch(0, 0);
  mainLayout->setSpacing(10);
  

  mainLayout->addWidget(shipData_,0,2, Qt::AlignRight);
  mainLayout->addWidget(secRow,1,0, 1, -1);

  thirdRow->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
  mainLayout->addWidget(thirdRow,2,0);

  std::cout << "--------------visIBILITY:  " + thirdRow->isVisible() << '\n'; 

  //mainLayout->addWidget(button_,2,2);
  button_->hide();

  setLayout(mainLayout);
  setWindowTitle(tr("Connecting buttons to processes.."));

  connect(button_, SIGNAL(released()), this, SLOT(onButtonReleased()));
  connect(&process_, SIGNAL(readyReadStandardOutput()), this, SLOT(onCaptureProcessOutput()));
}

// Destructor
MainWidget::~MainWidget() {
}

// Handler for button click
void MainWidget::onButtonReleased() {
  // clear the text in the textBrowser and start the process
  textBrowser_->clear();

  // Set up our process to write to stdout and run our command
  process_.setCurrentWriteChannel(QProcess::StandardOutput); // Set the write channel
  //process_.start(QString("ls -alh ").append(QDir::homePath()).append("/Desktop")); // Start a terminal command
  //process_.start(QString("ls -alh ~/"));
}


// This is called whenever the QProcess::readyReadStandardOutput() signal is received
void MainWidget::onCaptureProcessOutput() {
  // Determine whether the object that sent the signal was a pointer to a process
  QProcess* process = qobject_cast<QProcess*>(sender());
  // If so, append the output to the textbrowser
  if (process){
    textBrowser_->append(process->readAllStandardOutput());
  }
}
