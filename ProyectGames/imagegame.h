#ifndef IMAGEGAME_H
#define IMAGEGAME_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class ImageGame; }
QT_END_NAMESPACE

class ImageGame : public QMainWindow
{
    Q_OBJECT

public:
    ImageGame(QWidget *parent = nullptr);
    ~ImageGame();

private:
    Ui::ImageGame *ui;
};
#endif // IMAGEGAME_H
