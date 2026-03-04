#include "MainWindow.h"
#include <QStackedWidget>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent) {
    
    setWindowTitle("Chess app");
    resize(800, 600);

    stackedWidget = new QStackedWidget(this);

    startScreen = new StartScreen(this);
    gameScreen = new GameScreen(this);

    stackedWidget->addWidget(startScreen);
    stackedWidget->addWidget(gameScreen);

    setCentralWidget(stackedWidget);

    connect(startScreen, &StartScreen::startGameRequested, this, &MainWindow::showGameScreen);
    connect(gameScreen, &GameScreen::backToMenuRequested, this, &MainWindow::showStartScreen);
}

MainWindow::~MainWindow() {
}


void MainWindow::showGameScreen() {
    stackedWidget->setCurrentWidget(gameScreen);
}

void MainWindow::showStartScreen() {
    stackedWidget->setCurrentWidget(startScreen);
}