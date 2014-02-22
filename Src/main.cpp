#include "toymainwindow.h"
#include "toyrenderengine.h"
#include <toymatrix.h>
#include <toyvector.h>
#include <cstdio>
using namespace std;

#include <QtGui/QApplication>

int main(int argc, char* argv[]) {
  QApplication a(argc, argv);
  ToyRenderEngine* engine = new ToyRenderEngine();
  ToyMainWindow w(engine);
  w.show();
  int res = a.exec();
  delete engine;
  return res;
}
