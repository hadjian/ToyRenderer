#include "toymainwindow.h"
#include "ui_mainwindow.h"
#include "toyglwidget.h"

#include <QGridLayout>

class ToyRenderEngine;

ToyMainWindow::ToyMainWindow(ToyRenderEngine* engine, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow) {
  ui->setupUi(this);
  ToyGLWidget *openGL = new ToyGLWidget(engine, this);
  setCentralWidget(openGL);
  setWindowTitle(tr("My first Software Renderer"));
  setMaximumSize(800,600);
}

ToyMainWindow::~ToyMainWindow()
{
  delete ui;
}
