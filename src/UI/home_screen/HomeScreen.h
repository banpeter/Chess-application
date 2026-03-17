#pragma once

#include <QWidget>
#include <QPushButton>

class HomeScreen : public QWidget {
    Q_OBJECT

public:
    explicit HomeScreen(QWidget *parent = nullptr);

signals:
    void startGameRequested(); 

private:
    QPushButton *playButton;
    QPushButton *quitButton;
};