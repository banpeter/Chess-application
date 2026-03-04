#pragma once

#include <QWidget>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QPushButton>

class GameScreen : public QWidget {
    Q_OBJECT

public:
    explicit GameScreen(QWidget *parent = nullptr);

signals:
    void backToMenuRequested(); 

private:
    QPushButton *backButton;
    QGraphicsView *boardView;
    QGraphicsScene *boardScene;

    void drawBoard();
};