#pragma once

#include <QWidget>
#include <QPushButton>

class StartScreen : public QWidget {
    Q_OBJECT

public:
    explicit StartScreen(QWidget *parent = nullptr);

signals:
    void startGameRequested(); 

private:
    QPushButton *playButton;
    QPushButton *quitButton;
};