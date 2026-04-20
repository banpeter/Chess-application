#include "HomeScreen.h"
#include <QVBoxLayout>
#include <QLabel>
#include <QApplication>
#include <QFont>

HomeScreen::HomeScreen(QWidget *parent) : QWidget(parent) {
    QVBoxLayout *layout = new QVBoxLayout(this);

    QLabel *titleLabel = new QLabel("Chess application", this);
    titleLabel->setAlignment(Qt::AlignCenter);
    
    QFont titleFont = titleLabel->font();
    titleFont.setPointSize(32);
    titleFont.setBold(true);
    titleLabel->setFont(titleFont);

    playButton = new QPushButton("Start game", this);
    quitButton = new QPushButton("Quit", this);

    playButton->setMinimumHeight(40);
    quitButton->setMinimumHeight(40);

    layout->addStretch();
    layout->addWidget(titleLabel);
    layout->addSpacing(40);
    layout->addWidget(playButton);
    layout->addWidget(quitButton);
    layout->addStretch();


    
    connect(playButton, &QPushButton::clicked, this, &HomeScreen::startGameRequested);
    connect(quitButton, &QPushButton::clicked, qApp, &QApplication::quit);
}