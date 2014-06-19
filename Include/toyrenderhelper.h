#ifndef TOYRENDERHELPER_H
#define TOYRENDERHELPER_H

#include <toymatrix.h>

class ToyRotationMatrix: public ToyMatrix<float> {
 public:
  ToyRotationMatrix(float degreeX=0, float degreeY=0, float degreeZ=0);
  ~ToyRotationMatrix();

  void rotateX(float degree);
  void rotateY(float degree);
  void rotateZ(float degree);

 protected:
  float DegreeX;
  float DegreeY;
  float DegreeZ;
};

#endif 
