#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QGLWidget>
class QMouseEvent;

class ToyRenderEngine;
class ToyMatrix;
struct ToyPoint;

typedef enum {LINE_BEGIN, LINE_FOLLOW} LineState;

class ToyGLWidget : public QGLWidget
{
    Q_OBJECT
public:
  explicit ToyGLWidget(ToyRenderEngine* engine, QWidget *parent = 0);
  ~ToyGLWidget();
    
signals:
    
public slots:

protected:
  ToyRenderEngine* Engine;
  GLuint* FrontBackBuffers;
  int CurrentFront;
  struct ToyPoint* StartPoint;
  struct ToyPoint* EndPoint;
  LineState LState;

  void mousePressEvent(QMouseEvent* e);
  void mouseMoveEvent(QMouseEvent* e);
  void mouseReleaseEvent(QMouseEvent* e);

  void initializeGL();
  void resizeGL(int width, int height);
  void paintGL();

private:
  void drawLine();
};

#endif // GLWIDGET_H
