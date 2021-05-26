#include "imagegame.h"
#include "ui_imagegame.h"

ImageGame::ImageGame(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::ImageGame)
{
    ui->setupUi(this);
}

ImageGame::~ImageGame()
{
    delete ui;
}

