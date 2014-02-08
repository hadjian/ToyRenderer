
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
  setMouseTracking(true);
  setAutoFillBackground(false);
  CurrentFront=0;
  FrontBackBuffers = new GLuint[2];
  StartPoint = new ToyPoint();
  EndPoint = new ToyPoint();
  StartPoint->x = EndPoint->x = -1;
  StartPoint->y = EndPoint->y = -1;
  Engine = engine;
}

ToyGLWidget::~ToyGLWidget()
{
  delete[] FrontBackBuffers;
}

void ToyGLWidget::initializeGL()
{
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
  if ((width <= 0)||(height <= 0)) return; // Avoid GL_INVALID_VALUE with glOrtho! Happens with MPR displays at first show.
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
    EndPoint->x = e->pos().x();
    EndPoint->y = height() - 1 - e->pos().y();
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
    StartPoint->x = e->pos().x();
    StartPoint->y = height() - 1 - e->pos().y();
    LState = LINE_FOLLOW;
  } else
  {
    EndPoint->x = e->pos().x();
    EndPoint->y = height() - 1 - e->pos().y();
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
  struct ToySize bufferSize = {800, 600};
  Engine->rasterizeLine(*StartPoint, *EndPoint, buffer, bufferSize);
  glUnmapBufferARB(GL_PIXEL_UNPACK_BUFFER_ARB);
  CurrentFront = (CurrentFront+1)%2;
  updateGL();
}
