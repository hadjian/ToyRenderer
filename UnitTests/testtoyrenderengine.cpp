#include "toyrenderengine.h"
#include "toygeometry.h"

#include <gtest/gtest.h>

#include <limits>
#include <cstdio>
using namespace std;

// Expose protected interface for testing.
class XToyRenderEngine: public ToyRenderEngine {
public:
  ToyVector<int>** projectGeometry(const ToyGeometry& geometry, const ToyCamera& camera, const struct ToySizei& bufferSize) {
    return ToyRenderEngine::projectGeometry(geometry, camera, bufferSize);
  }

  QList<ToyGeometry*>* getGeometries() {
    return &Geometries;
  }
};

class ProjectionTest : public ::testing::Test {
protected:
  ProjectionTest():Engine(new XToyRenderEngine()) {
    initBuffer(800, 600);
    //--------------------------------------------------
    // The first test geometry will be two triangles.
    //--------------------------------------------------
    ToyVector<float> **vertices = new ToyVector<float>*[6];

    float *coords = new float[4];
    coords[0]=0.5; coords[1]=0.5; coords[2]=0.5; coords[3]=1.0;
    vertices[0]= new ToyVector<float>(4, coords);

    coords = new float[4];
    coords[0]=0.5; coords[1]=-0.5; coords[2]=0.5; coords[3]=1.0;
    vertices[1]= new ToyVector<float>(4, coords);

    coords = new float[4];
    coords[0]=-0.5; coords[1]=-0.5; coords[2]=0.5; coords[3]=1.0;
    vertices[2]= new ToyVector<float>(4, coords);

    coords = new float[4];
    coords[0]=0.5; coords[1]=0.5; coords[2]=-0.5; coords[3]=1.0;
    vertices[3]= new ToyVector<float>(4, coords);

    coords = new float[4];
    coords[0]=0.5; coords[1]=-0.5; coords[2]=-0.5; coords[3]=1.0;
    vertices[4]= new ToyVector<float>(4, coords);

    coords = new float[4];
    coords[0]=-0.5; coords[1]=-0.5; coords[2]=-0.5; coords[3]=1.0;
    vertices[5]= new ToyVector<float>(4, coords);

    ToyMatrix<float> modelMatrix;
    modelMatrix(0,0)=1;
    modelMatrix(1,1)=1;
    modelMatrix(2,2)=1;
    modelMatrix(3,3)=1;

    ToyGeometry *testGeometry = new ToyGeometry(modelMatrix, 6, vertices);
    Engine->addGeometry(testGeometry);
  }

  ~ProjectionTest() {
    delete Engine;
  }

  XToyRenderEngine *Engine; 
  char *Buffer;
  ToySizei BufferSize;

  // Construction helpers.
  void initBuffer(int width, int height) {
    BufferSize.Width=width;
    BufferSize.Height=height;
    Buffer = new char[BufferSize.Width*BufferSize.Height]; 
  }

};

ToyCamera* setupCamera() {
  ToyCamera *camera = new ToyCamera();
  float *position = new float[4];
  position[0]=0.0; position[1]=0.0; position[2]=2.0; position[3]=1.0;
  camera->Position = ToyVector<float>(4, position);
  camera->FocalLength = 0.5;
  camera->ViewPort.Width = 1.77;
  camera->ViewPort.Height = 1.0;
  float *baseVectors = new float[4*4];
  baseVectors[0] =1.0; baseVectors[1] =0.0; baseVectors[2] =0.0; baseVectors[3] =0.0;
  baseVectors[4] =0.0; baseVectors[5] =1.0; baseVectors[6] =0.0; baseVectors[7] =0.0;
  baseVectors[8] =0.0; baseVectors[9] =0.0; baseVectors[10]=1.0; baseVectors[11]=0.0;
  baseVectors[12]=0.0; baseVectors[13]=0.0; baseVectors[14]=0.0; baseVectors[15]=1.0;
  camera->Basis = ToyMatrix<float>(4, 4, baseVectors);
  return camera;
}

TEST_F(ProjectionTest, TranslationOnly) {
    // Setup the camera. No rotation, only two units translated 
    // in pos z-direction.
    ToyCamera * camera = setupCamera();
 
    QList<ToyGeometry*> *geometries = Engine->getGeometries();
    ToyGeometry *geometry =  (*geometries)[0];

    ToyVector<int>** projectedCoordinates = Engine->projectGeometry(*geometry, *camera, BufferSize);
    // Test first triangle
    ToyVector<int> v = *(projectedCoordinates[0]);
    EXPECT_EQ(475, v(0)); EXPECT_EQ(400, v(1));
    v = *(projectedCoordinates[1]);
    EXPECT_EQ(475, v(0)); EXPECT_EQ(200, v(1));
    v = *(projectedCoordinates[2]);
    EXPECT_EQ(325, v(0)); EXPECT_EQ(200, v(1));
    // Test second triangle
    v = *(projectedCoordinates[3]);
    EXPECT_EQ(445, v(0)); EXPECT_EQ(360, v(1));
    v = *(projectedCoordinates[4]);
    EXPECT_EQ(445, v(0)); EXPECT_EQ(240, v(1));
    v = *(projectedCoordinates[5]);
    EXPECT_EQ(355, v(0)); EXPECT_EQ(240, v(1));
}


TEST_F(ProjectionTest, TranslateAndRotate) {
    // Setup the camera. Rotate around each axis separately. 
    ToyCamera *camera = setupCamera();
    camera->rotateX(15);
 
    QList<ToyGeometry*> *geometries = Engine->getGeometries();
    ToyGeometry *geometry =  (*geometries)[0];

    ToyVector<int>** projectedCoordinates = Engine->projectGeometry(*geometry, *camera, BufferSize);
    // Test first triangle
    ToyVector<int> v = *(projectedCoordinates[0]);
    EXPECT_EQ(475, v(0)); EXPECT_EQ(400, v(1));
    v = *(projectedCoordinates[1]);
    EXPECT_EQ(475, v(0)); EXPECT_EQ(200, v(1));
    v = *(projectedCoordinates[2]);
    EXPECT_EQ(325, v(0)); EXPECT_EQ(200, v(1));
    // Test second triangle
    v = *(projectedCoordinates[3]);
    EXPECT_EQ(445, v(0)); EXPECT_EQ(360, v(1));
    v = *(projectedCoordinates[4]);
    EXPECT_EQ(445, v(0)); EXPECT_EQ(240, v(1));
    v = *(projectedCoordinates[5]);
    EXPECT_EQ(355, v(0)); EXPECT_EQ(240, v(1));
}
