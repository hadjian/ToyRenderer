#include "toymainwindow.h"
#include "toyrenderengine.h"
#include "toygeometry.h"

#include <cstdio>
using namespace std;

#include <QtGui/QApplication>

int main(int argc, char* argv[]) {
  QApplication a(argc, argv);
  ToyRenderEngine* engine = new ToyRenderEngine();
  //--------------------------------------------------
  // First test geometry will be two triangles.
  //--------------------------------------------------
  ToyVector<float> **vertices = new ToyVector<float>*[12];

  float *coords = new float[4];
  coords[0]=0.5; coords[1]=0.5; coords[2]=0.5; coords[3]=1.0;
  vertices[0]= new ToyVector<float>(4, coords);

  coords = new float[4];
  coords[0]=0.5; coords[1]=-0.5; coords[2]=0.5; coords[3]=1.0;
  vertices[1]= new ToyVector<float>(4, coords);

  coords = new float[4];
  coords[0]=-0.5; coords[1]=-0.5; coords[2]=0.5; coords[3]=1.0;
  vertices[2]= new ToyVector<float>(4, coords);

  coords = new float[4];
  coords[0]=0.5; coords[1]=0.5; coords[2]=-0.5; coords[3]=1.0;
  vertices[3]= new ToyVector<float>(4, coords);

  coords = new float[4];
  coords[0]=0.5; coords[1]=-0.5; coords[2]=-0.5; coords[3]=1.0;
  vertices[4]= new ToyVector<float>(4, coords);

  coords = new float[4];
  coords[0]=-0.5; coords[1]=-0.5; coords[2]=-0.5; coords[3]=1.0;
  vertices[5]= new ToyVector<float>(4, coords);

  ToyMatrix<float> modelMatrix;
  modelMatrix(0,0)=1;
  modelMatrix(1,1)=1;
  modelMatrix(2,2)=1;
  modelMatrix(3,3)=1;

  ToyGeometry *testGeometry = new ToyGeometry(modelMatrix, 6, vertices);
  engine->addGeometry(testGeometry);
  //------------------------------------------------
  // Create main window and pass rendering engine.
  //------------------------------------------------
  ToyMainWindow w(engine);
  w.show();
  int res = a.exec();
  delete engine;
  return res;
}
