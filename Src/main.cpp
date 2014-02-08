#include "toymainwindow.h"
#include "toyrenderengine.h"
#include <toymatrix.h>
#include <toyvector.h>
#include <cstdio>
using namespace std;

#include <QtGui/QApplication>

int main(int argc, char* argv[]) {
  ToyMatrix<int> A;
  ToyMatrix<int> B(4,3);
  for(int i=0; i < A.getRows(); i++) {
    for(int j=0; j < A.getColumns(); j++) {
      A(i,j) = i+j;
    }
  }
  for(int i=0; i < B.getRows(); i++) {
    for(int j=0; j < B.getColumns(); j++) {
      B(i,j) = (B.getRows()-1-i) + (B.getColumns()-1-j);
    }
  }
  printf("Matrix A:\n");
  A.printValues();
  printf("Matrix B:\n");
  B.printValues();
  printf("Testing C as a copy of B:\n");
  ToyMatrix<int> C(B);
  C.printValues();
  printf("Testing B assigned to C:\n");
  C = A;
  C.printValues();
  printf("Add A to itself:\n");
  (C+A).printValues();
  printf("Transpose A:\n");
  C.transpose();
  C.printValues();
  printf("Transpose B and transpose back:\n");
  B.transpose();
  B.printValues();
  B.transpose();
  B.printValues();
  printf("A*B:");
  (A*B).printValues();
  printf("Which CCTor gets called with vectors?\n");
  ToyVector<int> veca;
  ToyVector<int> vecb;
  printf("Vector CCTor should not take ToyMatrix argument:\n");
//  ToyVector<int> vecc(A); // <- Compile-time error
  printf("Odd: calling CCTor of derived class calls base-class CTor\n");
  ToyVector<int> vecd(veca);
  ToyMatrix<int> D(A);
  // Does the index operator from the base class still work?
//  printf("vecd(1,0): %i\n", vecd(1,0));
  ToyVector<float> vece;
  vece(0)=30; vece(1)=40; vece(2)=50; vece(3)=60;
  vece.printValues();
  vece.normalize();
  vece.printValues();
  ToyMatrix<float> mata(4,4);
  for (int i=0; i<4; i++)
  {
    for (int j=0; j<4; j++)
    {
      mata(i,j)=i+j;
    }
  }
  printf("mata:\n");
  mata.printValues();
  (mata*vece).printValues();
  vece.transpose();
  (vece*mata).printValues();
  fflush(stdout);
  QApplication a(argc, argv);
  ToyRenderEngine* engine = new ToyRenderEngine();
  ToyMainWindow w(engine);
  w.show();
  int res = a.exec();
  delete engine;
  return res;
}
