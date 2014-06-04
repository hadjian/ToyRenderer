#include <iostream>
#include <cstdio>
using namespace std;

#include <GL/glew.h>
#include "toyglwidget.h"
#include <toyrenderengine.h>
#include <toyrenderhelper.h>
//#include <toymatrix.h>

#include <QGLWidget>
#include <QMouseEvent>
#include <assert.h>

ToyGLWidget::ToyGLWidget(ToyRenderEngine* engine, QWidget *parent) :
  QGLWidget(parent),
  LastMousePosition(-1,-1),
  RotX(0.0f),
  RotY(0.0f),
  Pixel2Degree(0.4f)
{
  BufferSize = new struct ToySizei;
  BufferSize->Width=800;
  BufferSize->Height=600;
  setMouseTracking(true);
  Camera = new ToyCamera();
  float *position = new float[4];
  position[0]=0.0; position[1]=0.0; position[2]=2.0; position[3]=1.0;
  Camera->Position = ToyVector<float>(4, position);
  Camera->FocalLength = 0.5;
  Camera->ViewPort.Width = 1.333333333;
  Camera->ViewPort.Height = 1.0;
  float *baseVectors = new float[4*4];
  baseVectors[0]=1.0; baseVectors[1]=0.0; baseVectors[2]=0.0; baseVectors[3]=0.0;
  baseVectors[4]=0.0; baseVectors[5]=1.0; baseVectors[6]=0.0; baseVectors[7]=0.0;
  baseVectors[8]=0.0; baseVectors[9]=0.0; baseVectors[10]=1.0; baseVectors[11]=0.0;
  baseVectors[12]=0.0; baseVectors[13]=0.0; baseVectors[14]=0.0; baseVectors[15]=1.0;
  Camera->Basis = ToyMatrix<float>(4, 4, baseVectors);
  setMouseTracking(true);
  setAutoFillBackground(false);
  CurrentFront=0;
  FrontBackBuffers = new GLuint[2];
  Engine = engine;
}

ToyGLWidget::~ToyGLWidget()
{
  if (Camera) delete Camera;
  if (FrontBackBuffers) delete[] FrontBackBuffers;
  if (BufferSize) delete BufferSize;
}

void ToyGLWidget::initializeGL()
{
  GLenum err = glewInit();
  //Check for extension availability.
  if (GLEW_OK != err) {
    /* Problem: glewInit failed, something is seriously wrong. */
    fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
    delete this;
  }
  if ( glewGetExtension("GL_ARB_vertex_buffer_object") ) {
    std::cout << "VBO supported." << std::endl;
  } else {
    std::cerr << "ARB_vertex_buffer_object not supported!" << std::endl;
  }

  glClearColor(0.0, 0.0, 0.0, 0.0);

  // Create and initialize first buffer.
  glGenBuffers(2,FrontBackBuffers);
  glBindBuffer(GL_PIXEL_UNPACK_BUFFER, FrontBackBuffers[0]);
  glBufferData(GL_PIXEL_UNPACK_BUFFER, BufferSize->Width*BufferSize->Height*(PIXEL_SIZE>>3), NULL, GL_STREAM_DRAW);
  glBindBuffer(GL_PIXEL_UNPACK_BUFFER_ARB, 0);

  // Create and initialize second buffer.
  glBindBuffer(GL_PIXEL_UNPACK_BUFFER, FrontBackBuffers[1]);
  glBufferData(GL_PIXEL_UNPACK_BUFFER, BufferSize->Width*BufferSize->Height*(PIXEL_SIZE>>3), NULL, GL_STREAM_DRAW);
  glBindBuffer(GL_PIXEL_UNPACK_BUFFER, 0);
}

void ToyGLWidget::resizeGL(int width, int height)
{
  if ((width <= 0)||(height <= 0)) return; 
  BufferSize->Width=width;
  BufferSize->Height=height;
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(0.0,(GLdouble)width,(GLdouble)height,0.0,-100.0,100.0);
  glViewport(0,0,(GLsizei)width,(GLsizei)height);
}

void ToyGLWidget::paintGL()
{
  QGLWidget::paintGL();
  glClear(GL_COLOR_BUFFER_BIT);
  glBindBuffer(GL_PIXEL_UNPACK_BUFFER, FrontBackBuffers[CurrentFront]);
  glDrawPixels(BufferSize->Width, BufferSize->Height, GL_RGBA, GL_UNSIGNED_BYTE, 0);
  glBindBuffer(GL_PIXEL_UNPACK_BUFFER, 0);
}

void ToyGLWidget::mouseMoveEvent(QMouseEvent *e)
{
  if (LastMousePosition.x()<0 || LastMousePosition.y()<0 || !(e->buttons() && Qt::LeftButton) )
  {
    LastMousePosition = e->pos();
    return;
  }
  QPoint currentPosition = e->pos();
  QPoint delta = (e->pos()-LastMousePosition);
  RotX += delta.x()*Pixel2Degree*M_PI/90.0;
  RotY += delta.y()*Pixel2Degree*M_PI/90.0;

  ToyRotationMatrix rot(RotY, RotX); 
  Camera->Basis.makeIdentity();
  Camera->Basis*=rot;
  printf("rotx=%f,roty=%f\n",RotY,RotX);
  Camera->Basis.printValues();
  Camera->Position = ToyVector<float>();
  Camera->Position(2)=2.0f;
  Camera->Position = rot * Camera->Position;
  Camera->Position.printValues();
  LastMousePosition = e->pos();
  draw();
}

void ToyGLWidget::mousePressEvent(QMouseEvent *e)
{
  draw();
}

void ToyGLWidget::mouseReleaseEvent(QMouseEvent *e)
{
}

void ToyGLWidget::draw()
{
  // Draw our first vertices
  makeCurrent();
  glBindBuffer(GL_PIXEL_UNPACK_BUFFER, FrontBackBuffers[(CurrentFront+1)%2]);
  char* buffer = (char*) glMapBuffer(GL_PIXEL_UNPACK_BUFFER, GL_READ_WRITE);
  assert(buffer != NULL);
  // TODO: Don't know how to clear the GL buffer so I memset it here.
  memset(buffer, 0, BufferSize->Width*BufferSize->Height*(PIXEL_SIZE>>3));
  Engine->render(*Camera, buffer, *BufferSize); 
  glUnmapBufferARB(GL_PIXEL_UNPACK_BUFFER_ARB);
  CurrentFront = (CurrentFront+1)%2;
  updateGL();
}
