#include "dbmanager.h"
#include "mainwindow.h"
#include "xmlcreator.h"
#include "onemonthcompanydata.h"
#include <QApplication>

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);

  //DbManager::CreateInstance("db/bazodanowa.db");
  //MainWindow w;
  //w.show();
  OneMonthCompanyData data("hue", "zybki", 1,2001);
  XmlCreator creator(data);
  creator.CreateXml();

  return a.exec();
}
