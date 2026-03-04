#include "MainWindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent) {
    
    setWindowTitle("Chess app");
    resize(800, 600);

    scene = new QGraphicsScene(this);
    view = new QGraphicsView(scene, this);

    setCentralWidget(view);
}

MainWindow::~MainWindow() {
}