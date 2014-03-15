#include "toyrenderengine.h"

#include <assert.h>
#include <cstdio>
#include <cstdlib>
using namespace std;

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
  foreach (ToyGeometry *geometry, Geometries)
  {
    ToyVector<int>** projectedVectors = projectGeometry(*(geometry), camera, bufferSize);  
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
  float viewElements[4*4] = { 1.0, 0.0, 0.0, camera.Position(0)*(-1.0),
                         0.0, 1.0, 0.0, camera.Position(1)*(-1.0),
                         0.0, 0.0, 1.0, camera.Position(2)*(-1.0),
                         0.0, 0.0, 0.0, 1.0                         };
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
void ToyRenderEngine::rasterizeLine(ToyVector<int>** projectedPoints, char* buffer, struct ToySizei bufferSize) {
/*
  assert(buffer != NULL);
  assert(p1.x >= 0 && p1.y >= 0 && p2.x < bufferSize.width && p2.y < bufferSize.height);

  printf("draw line from (%i,%i) to (%i,%i)\n", p1.x, p1.y, p2.x, p2.y);
  fflush(stdout);

  int* slow = 0x0;
  int* fast = 0x0;
  int x = p1.x;
  int y = p1.y;

  int deltaFast = p2.x-p1.x;
  int deltaSlow = p2.y-p1.y;

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
      buffer[(bytesPerPixel*(y*bufferSize.width+x)+p)] = 0xFF;
    }
    if ( error <= 0 ) {
      error += deltaErrorE;
    }
    else {
      *slow += stepSlow;
      error += deltaErrorNE;
    }
  }
*/
}
