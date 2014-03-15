#include<iostream>

#include <GL/glew.h>
#include "toyglwidget.h"
#include "toyrenderengine.h"
//#include <toymatrix.h>

#include <QGLWidget>
#include <QMouseEvent>
#include <assert.h>

ToyGLWidget::ToyGLWidget(ToyRenderEngine* engine, QWidget *parent) :
  QGLWidget(parent),
  LState(LINE_BEGIN)
{
  Camera = new ToyCamera();
  float *position = new float[4];
  position[0]=0.0; position[1]=0.0; position[2]=1.0; position[3]=1.0;
  Camera->Position = ToyVector<float>(4, position);
  Camera->FocalLength = 0.5;
  Camera->ViewPort.Width = 1.77;
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
  StartPoint = new ToyPoint();
  EndPoint = new ToyPoint();
  StartPoint->X = EndPoint->X = -1;
  StartPoint->Y = EndPoint->Y = -1;
  Engine = engine;
}

ToyGLWidget::~ToyGLWidget()
{
  if (Camera) delete Camera;
  if (FrontBackBuffers) delete[] FrontBackBuffers;
}

void ToyGLWidget::initializeGL()
{
  GLenum err = glewInit();
  //Check for extension availability.
  if (GLEW_OK != err)
  {
    /* Problem: glewInit failed, something is seriously wrong. */
    fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
    delete this;
  }
  if ( glewGetExtension("GL_ARB_vertex_buffer_object") )
          {
              std::cout << "VBO supported." << std::endl;
          }
      else
          {
              std::cerr << "ARB_vertex_buffer_object not supported!" << std::endl;
          }
  

  glClearColor(0.0, 0.0, 0.0, 0.0);

  // Create and initialize first buffer.
  glGenBuffers(2,FrontBackBuffers);
  glBindBuffer(GL_PIXEL_UNPACK_BUFFER, FrontBackBuffers[0]);
  glBufferData(GL_PIXEL_UNPACK_BUFFER, 800*600*(PIXEL_SIZE>>3), NULL, GL_STREAM_DRAW);
  glBindBuffer(GL_PIXEL_UNPACK_BUFFER_ARB, 0);

  // Create and initialize second buffer.
  glBindBuffer(GL_PIXEL_UNPACK_BUFFER, FrontBackBuffers[1]);
  glBufferData(GL_PIXEL_UNPACK_BUFFER, 800*600*(PIXEL_SIZE>>3), NULL, GL_STREAM_DRAW);
  glBindBuffer(GL_PIXEL_UNPACK_BUFFER, 0);
}

void ToyGLWidget::resizeGL(int width, int height)
{
  if ((width <= 0)||(height <= 0)) return; 
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
  glDrawPixels(800, 600, GL_RGBA, GL_UNSIGNED_BYTE, 0);
  glBindBuffer(GL_PIXEL_UNPACK_BUFFER, 0);
}

void ToyGLWidget::mouseMoveEvent(QMouseEvent *e)
{
  if (LState == LINE_FOLLOW)
  {
    // Start point has been set. Follow with a line.
    EndPoint->X = e->pos().x();
    EndPoint->Y = height() - 1 - e->pos().y();
    drawLine();
  }
}

void ToyGLWidget::mousePressEvent(QMouseEvent *e)
{

}

void ToyGLWidget::mouseReleaseEvent(QMouseEvent *e)
{
  if (LState == LINE_BEGIN)
  {
    StartPoint->X = e->pos().x();
    StartPoint->Y = height() - 1 - e->pos().y();
    LState = LINE_FOLLOW;
  } else
  {
    EndPoint->X = e->pos().x();
    EndPoint->Y = height() - 1 - e->pos().y();
    LState = LINE_BEGIN;
    drawLine();
  }
}

void ToyGLWidget::drawLine()
{
  makeCurrent();
  glBindBuffer(GL_PIXEL_UNPACK_BUFFER, FrontBackBuffers[(CurrentFront+1)%2]);
  char* buffer = (char*) glMapBuffer(GL_PIXEL_UNPACK_BUFFER, GL_READ_WRITE);
  assert(buffer != NULL);
  struct ToySizei bufferSize = {800, 600};
//  Engine->rasterizeLine(*StartPoint, *EndPoint, buffer, bufferSize);
  glUnmapBufferARB(GL_PIXEL_UNPACK_BUFFER_ARB);
  CurrentFront = (CurrentFront+1)%2;
  updateGL();
}
