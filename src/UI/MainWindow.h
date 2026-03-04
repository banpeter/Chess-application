#pragma once

#include "StartScreen.h"
#include "GameScreen.h"
#include <QMainWindow>
#include <QStackedWidget>

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void showGameScreen();
    void showStartScreen();

private:
    QStackedWidget *stackedWidget;

    StartScreen *startScreen;
    GameScreen *gameScreen;
};