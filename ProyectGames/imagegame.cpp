#include "imagegame.h"
#include "ui_imagegame.h"

ImageGame::ImageGame(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::ImageGame)
{
    ui->setupUi(this);
    gridLayout->setHorizontalSpacing(5)
    gridLayout->setVerticalSpacing(5)
}

ImageGame::~ImageGame()
{
    delete ui;
}

