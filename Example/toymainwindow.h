#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class ToyRenderEngine;

namespace Ui {
class MainWindow;
}

class ToyMainWindow : public QMainWindow {
    
public:
  explicit ToyMainWindow(ToyRenderEngine* engine, QWidget *parent = 0);
  ~ToyMainWindow();

private:
  Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
