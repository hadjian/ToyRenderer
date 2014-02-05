#ifndef TOYRENDERENGINE_H
#define TOYRENDERENGINE_H

// #include <ToyMatrix>

#define PIXEL_SIZE 32

struct ToySize {
  int width;
  int height;
};

struct ToyPoint {
  int x;
  int y;
};

class ToyRenderEngine {

public:
  explicit ToyRenderEngine();
//  void render(ToyMatrix& viewMatrix, );
  void rasterizeLine(struct ToyPoint p1, struct ToyPoint p2, char* buffer, struct ToySize buffersize);

protected:
};

#endif // TOYRENDERENGINE_H
