#include <QApplication>

#include "model/facade/facade.h"
#include "view/main_window/mainwindow.h"

using namespace s21;
int main(int argc, char *argv[]) {
  QApplication a(argc, argv);

  Facade first_model;
  Controller first_controller(&first_model);
  MainWindow w(&first_controller);

  Facade second_model;
  Controller second_controller(&second_model);
  SecondWindow second_w(&second_controller);

  w.SetSecondWindow(&second_w);

  w.show();
  return a.exec();
}
