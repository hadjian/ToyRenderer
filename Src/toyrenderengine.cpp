#include "toyrenderengine.h"

#include <assert.h>
#include <cstdio>
#include <cstdlib>
using namespace std;

ToyRenderEngine::ToyRenderEngine() {
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
void ToyRenderEngine::rasterizeLine(struct ToyPoint p1, struct ToyPoint p2, char* buffer, struct ToySize bufferSize) {
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
}
