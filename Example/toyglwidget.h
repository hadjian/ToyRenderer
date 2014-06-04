#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QGLWidget>
#include <QPoint>
class QMouseEvent;

class ToyRenderEngine;
class ToyCamera;
struct ToyPoint;

class ToyGLWidget : public QGLWidget
{
public:
  explicit ToyGLWidget(ToyRenderEngine* engine, QWidget *parent = 0);
  ~ToyGLWidget();
    
signals:
    
protected:
  ToyCamera*       Camera;
  ToyRenderEngine* Engine;

  struct ToySizei* BufferSize;
  GLuint*          FrontBackBuffers;
  int              CurrentFront;

  QPoint      LastMousePosition;
  float       RotX, RotY;
  const float Pixel2Degree;
 
  void mousePressEvent(QMouseEvent* e);
  void mouseMoveEvent(QMouseEvent* e);
  void mouseReleaseEvent(QMouseEvent* e);

  void initializeGL();
  void resizeGL(int width, int height);
  void paintGL();
  void draw();
};

#endif // GLWIDGET_H
