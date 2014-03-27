#ifndef TOYRENDERENGINE_H
#define TOYRENDERENGINE_H

#include <toymatrix.h>
#include "toygeometry.h"

#include<QList>

#define PIXEL_SIZE 32

struct ToySizei {
  int Width;
  int Height;
};

struct ToySizef {
  float Width;
  float Height;
};

struct ToyPoint {
  int X;
  int Y;
};

class ToyCamera {
public:
  ToyMatrix<float> Basis;
  ToyVector<float> Position;
  struct ToySizef  ViewPort;
  float            FocalLength; 
};

class ToyRenderEngine {
public:
  explicit ToyRenderEngine();
  ~ToyRenderEngine();

  void render(const ToyCamera& camera, char* buffer, const struct ToySizei& bufferSize);
  void addGeometry(ToyGeometry* geometry);

protected:
  ToyVector<int>** projectGeometry(const ToyGeometry& geometry, const ToyCamera& camera, const struct ToySizei& bufferSize);
  void rasterizeLine(ToyVector<int>** projectedPoints, char* buffer, struct ToySizei buffersize);
  QList<ToyGeometry*> Geometries;

private:
};

#endif // TOYRENDERENGINE_H
