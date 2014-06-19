#include "toyrenderhelper.h"

ToyRotationMatrix::ToyRotationMatrix(float degreeX /*=0*/, float degreeY /*=0*/, float degreeZ /*=0*/):ToyMatrix<float>(),
                                                                                                       DegreeX(degreeX),
                                                                                                       DegreeY(degreeY),
                                                                                                       DegreeZ(degreeZ) {
  makeIdentity();
  // Efficiency: Try to initialize in one go if possible
  // Out of convenience the default C'tor will init with
  // zero, then the identity matrix is written (only
  // five entries) and then rotation is constructed and
  // multiplied.
  if (DegreeX) {
    rotateX(DegreeX);
  }
  if (DegreeY) {
    rotateY(DegreeY);
  }
  if (DegreeZ) {
    rotateZ(DegreeZ);
  }
}

ToyRotationMatrix::~ToyRotationMatrix() {
}

void ToyRotationMatrix::rotateX(float degree) {
  // TODO: Throw exception here
  if (Rows!=4 || Columns!=4) {
    assert(false);
  }
  DegreeX=degree;
  float rotationElements[16] = {1.0,          0.0,          0.0, 0.0,
                                0.0,  cos(degree), -sin(degree), 0.0,
                                0.0,  sin(degree),  cos(degree), 0.0,
                                0.0,          0.0,          0.0, 1.0};
  float *rotationElementsP = new float[16];
  memcpy(rotationElementsP, &rotationElements, 16*sizeof(float));
  ToyMatrix<float> rotationX(4, 4, rotationElementsP);
  (*this) *= rotationX;
}

void ToyRotationMatrix::rotateY(float degree) {
  // TODO: Throw exception here
  if (Rows!=4 || Columns!=4) {
    assert(false);
  }
  DegreeY=degree;
  float rotationElements[16] = { cos(degree), 0.0,  sin(degree), 0.0,
                                         0.0, 1.0,          0.0, 0.0,
                                -sin(degree), 0.0,  cos(degree), 0.0,
                                         0.0, 0.0,          0.0, 1.0};
  float *rotationElementsP = new float[16];
  memcpy(rotationElementsP, &rotationElements, 16*sizeof(float));
  ToyMatrix<float> rotationY(4, 4, rotationElementsP);
  (*this) *= rotationY;
}

void ToyRotationMatrix::rotateZ(float degree) {
  // TODO: Throw exception here
  if (Rows!=4 || Columns!=4) {
    assert(false);
  }
  DegreeZ=degree;
  float rotationElements[16] = { cos(degree), -sin(degree), 0.0, 0.0,
                                 sin(degree),  cos(degree), 0.0, 0.0,
                                         0.0,          0.0, 1.0, 0.0,
                                         0.0,          0.0, 0.0, 1.0};
  float *rotationElementsP = new float[16];
  memcpy(rotationElementsP, &rotationElements, 16*sizeof(float));
  ToyMatrix<float> rotationZ(4, 4, rotationElementsP);
  (*this) *= rotationZ;
}

