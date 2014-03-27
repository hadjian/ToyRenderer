#ifndef TOYGEOMETRY_H
#define TOYGEOMETRY_H

#include <toymatrix.h>
#include <toyvector.h>

class ToyGeometry {
 public:
  ToyGeometry(const ToyMatrix<float>& modelMatrix = ToyMatrix<float>(), int numVertices = 0, ToyVector<float> **vertices = NULL);
  ~ToyGeometry();

  ToyMatrix<float> ModelMatrix;
  int NumVertices;
  ToyVector<float> **Vertices;
};

#endif // TOYGEOMETRY_H

