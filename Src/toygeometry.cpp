#include "toygeometry.h"

ToyGeometry::ToyGeometry(const ToyMatrix<float>& modelMatrix /*=ToyMatrix<float>()*/, 
                         int numVertices /* =0 */,
                         ToyVector<float> **vertices /*=NULL*/) : 
  ModelMatrix(modelMatrix),
  NumVertices(numVertices),
  Vertices(vertices)
{

}

ToyGeometry::~ToyGeometry()
{
  for (int i=0; i<NumVertices; i++)
  {
    delete Vertices[i];
  }
  delete[] Vertices;
}

