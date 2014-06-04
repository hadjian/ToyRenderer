#include "toyrenderengine.h"

#include <assert.h>
#include <cstdio>
#include <cstdlib>
using namespace std;

// World coordinate system is right-handed
void ToyCamera::rotateX(float degree) {
  float rotationElements[16] = {1.0,          0.0,          0.0, 0.0,
                                0.0,  cos(degree), -sin(degree), 0.0, 
                                0.0,  sin(degree),  cos(degree), 0.0,
                                0.0,          0.0,          0.0, 1.0}; 
  float *rotationElementsP = new float[16];
  memcpy(rotationElementsP, &rotationElements, 16*sizeof(float));
  ToyMatrix<float> rotationX(4, 4, rotationElementsP); 
  Basis *= rotationX;
}

// World coordinate system is right-handed
void ToyCamera::rotateY(float degree) {
  float rotationElements[16] = { cos(degree), 0.0,  sin(degree), 0.0,
                                         0.0, 1.0,          0.0, 0.0, 
                                -sin(degree), 0.0,  cos(degree), 0.0,
                                         0.0, 0.0,          0.0, 1.0}; 
  float *rotationElementsP = new float[16];
  memcpy(rotationElementsP, &rotationElements, 16*sizeof(float));
  ToyMatrix<float> rotationY(4, 4, rotationElementsP); 
  Basis *= rotationY;
}

// World coordinate system is right-handed
void ToyCamera::rotateZ(float degree) {
  float rotationElements[16] = { cos(degree), -sin(degree), 0.0, 0.0,
                                 sin(degree),  cos(degree), 0.0, 0.0,
                                         0.0,          0.0, 1.0, 0.0, 
                                         0.0,          0.0, 0.0, 1.0}; 
  float *rotationElementsP = new float[16];
  memcpy(rotationElementsP, &rotationElements, 16*sizeof(float));
  ToyMatrix<float> rotationZ(4, 4, rotationElementsP); 
  Basis *= rotationZ;
}


ToyRenderEngine::ToyRenderEngine() 
{

}

ToyRenderEngine::~ToyRenderEngine()
{
  while (!Geometries.isEmpty())
  {
    delete Geometries.takeFirst();
  }
}

void ToyRenderEngine::render(const ToyCamera& camera, char* buffer, const struct ToySizei& bufferSize)
{
  ToyVector<int>** projectedVectors=NULL; 
  foreach (ToyGeometry *geometry, Geometries)
  {
    projectedVectors = projectGeometry(*(geometry), camera, bufferSize);  
    int bytesPerPixel = (int) PIXEL_SIZE >> 3;
    int x1=0, y1=0, x2=0, y2=0, x3=0, y3=0;
    for (int i=0; i<(geometry->NumVertices)/3; i++) {
      int starti = i*3;
      x1 = projectedVectors[starti]->operator()(0);
      y1 = projectedVectors[starti]->operator()(1);
      x2 = projectedVectors[starti+1]->operator()(0);
      y2 = projectedVectors[starti+1]->operator()(1);
      x3 = projectedVectors[starti+2]->operator()(0);
      y3 = projectedVectors[starti+2]->operator()(1);
      ToyPoint p1 = {x1,y1}, p2 = {x2,y2}, p3 = {x3,y3}; 
      rasterizeLine(p1, p2, buffer, bufferSize);
      rasterizeLine(p2, p3, buffer, bufferSize);
      rasterizeLine(p3, p1, buffer, bufferSize);
    }
  }
}

void ToyRenderEngine::addGeometry(ToyGeometry* geometry)
{
  Geometries.append(geometry);
}

//-----------------------------------------------------------------------------
//
// return value: Array of projected points (Owner: caller)
//
//-----------------------------------------------------------------------------
ToyVector<int>** ToyRenderEngine::projectGeometry(const ToyGeometry& geometry, const ToyCamera& camera, const struct ToySizei& bufferSize) 
{
  // Construct the modelview matrix.
  float viewElements[4*4] = {1.0, 0.0, 0.0, camera.Position(0)*(-1.0),
                             0.0, 1.0, 0.0, camera.Position(1)*(-1.0),
                             0.0, 0.0, 1.0, camera.Position(2)*(-1.0),
                             0.0, 0.0, 0.0, 1.0                       };
  float *viewElementsP = new float[4*4];
  memcpy(viewElementsP, &viewElements, 4*4*sizeof(float));  
  ToyMatrix<float> modelViewMatrix(4,4,viewElementsP);
  modelViewMatrix *= geometry.ModelMatrix;
  modelViewMatrix = ToyMatrix<float>(camera.Basis).transpose() * modelViewMatrix;

  // Calculate scaling and offset to convert to device dependent coordinates. 
  float viewPort2DeviceW = ((float) bufferSize.Width)/camera.ViewPort.Width;
  float viewPort2DeviceH = ((float) bufferSize.Height)/camera.ViewPort.Height;
  int   viewPortOffSetX  = bufferSize.Width/2;
  int   viewPortOffSetY  = bufferSize.Height/2;

  // Project all vertices of the given geometry.
  ToyVector<int>** resultVectors = new ToyVector<int>*[geometry.NumVertices];
  ToyVector<float> tmpVector;
  float w = 0.0;
  for (int i=0; i<geometry.NumVertices; i++)
  {
    tmpVector = *(geometry.Vertices[i]);
    tmpVector = modelViewMatrix*tmpVector;  
    tmpVector(2) *= -1;
    w = camera.FocalLength / (tmpVector(2)); 
    
 
    resultVectors[i] = new ToyVector<int>;
    resultVectors[i]->operator()(0) = (int) (tmpVector(0) * w * viewPort2DeviceW); 
    resultVectors[i]->operator()(0) += viewPortOffSetX;

    resultVectors[i]->operator()(1) = (int) (tmpVector(1) * w * viewPort2DeviceH); 
    resultVectors[i]->operator()(1) += viewPortOffSetY; 

    resultVectors[i]->operator()(2) = (int) tmpVector(2);
    resultVectors[i]->operator()(3) = 1;
  }
  return resultVectors;
}


//------------------------------------------------
// rasterizeLine()
//------------------------------------------------
//
// This function will only write into the
// provided buffer, but will not make any GL
// context current. This must have been done by
// the caller.
//
// Coordinate origin of the buffer is assumed to
// be on the upper left.
//
//------------------------------------------------
void ToyRenderEngine::rasterizeLine(ToyPoint& p1, ToyPoint& p2, char *buffer, struct ToySizei bufferSize) {
  assert(buffer != NULL);
  assert(p1.X >= 0 && p1.Y >= 0 && p2.X < bufferSize.Width && p2.Y < bufferSize.Height);

  int* slow = 0x0;
  int* fast = 0x0;
  int x = p1.X;
  int y = p1.Y;

  int deltaFast = p2.X-p1.X;
  int deltaSlow = p2.Y-p1.Y;

  int stepFast = 1;
  if (deltaFast < 0) {
    stepFast = -1;
  }
  deltaFast= abs(deltaFast);

  int stepSlow = 1;
  if (deltaSlow < 0) {
    stepSlow = -1;
  }
  deltaSlow = abs(deltaSlow);

  if (deltaSlow > deltaFast) {
    int tmp;
    tmp = deltaSlow;
    deltaSlow = deltaFast;
    deltaFast = tmp;
    tmp = stepSlow;
    stepSlow = stepFast;
    stepFast = tmp;
    fast = &y;
    slow = &x;
  }
  else {
    fast = &x;
    slow = &y;
  }

  int error  = (deltaSlow<<1)-deltaFast;
  int deltaErrorE  = deltaSlow<<1;
  int deltaErrorNE = (deltaSlow<<1) - (deltaFast<<1);

  int bytesPerPixel = (int) PIXEL_SIZE >> 3;

  for (int i = 0; i <=deltaFast; i++) {
    *fast += stepFast;
    for (int p=0; p<bytesPerPixel; p++) {
      buffer[(bytesPerPixel*(y*bufferSize.Width+x)+p)] = 0xFF;
    }
    if ( error <= 0 ) {
      error += deltaErrorE;
    }
    else {
      *slow += stepSlow;
      error += deltaErrorNE;
    }
  }
}
