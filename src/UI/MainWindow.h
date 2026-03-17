#pragma once

#include "HomeScreen.h"
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
    void showHomeScreen();

private:
    QStackedWidget *stackedWidget;

    HomeScreen *homeScreen;
    GameScreen *gameScreen;
};