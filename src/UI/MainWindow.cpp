#include "MainWindow.h"
#include <QStackedWidget>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent) {
    
    setWindowTitle("Chess app");
    resize(800, 600);

    stackedWidget = new QStackedWidget(this);

    homeScreen = new HomeScreen(this);
    gameScreen = new GameScreen(this);

    stackedWidget->addWidget(homeScreen);
    stackedWidget->addWidget(gameScreen);

    setCentralWidget(stackedWidget);

    connect(homeScreen, &HomeScreen::startGameRequested, this, &MainWindow::showGameScreen);
    connect(gameScreen, &GameScreen::backToMenuRequested, this, &MainWindow::showHomeScreen);
}

MainWindow::~MainWindow() {
}


void MainWindow::showGameScreen() {
    stackedWidget->setCurrentWidget(gameScreen);
}

void MainWindow::showHomeScreen() {
    stackedWidget->setCurrentWidget(homeScreen);
}