/********************************************************************************
** Form generated from reading UI file 'imagegame.ui'
**
** Created by: Qt User Interface Compiler version 6.0.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_IMAGEGAME_H
#define UI_IMAGEGAME_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QScrollBar>
#include <QtWidgets/QTimeEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ImageGame
{
public:
    QWidget *centralwidget;
    QTimeEdit *timeEdit;
    QWidget *gridLayoutWidget;
    QGridLayout *gridLayout;
    QScrollBar *horizontalScrollBar;

    void setupUi(QMainWindow *ImageGame)
    {
        if (ImageGame->objectName().isEmpty())
            ImageGame->setObjectName(QString::fromUtf8("ImageGame"));
        ImageGame->resize(800, 600);
        centralwidget = new QWidget(ImageGame);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        centralwidget->setEnabled(true);
        centralwidget->setAutoFillBackground(false);
        timeEdit = new QTimeEdit(centralwidget);
        timeEdit->setObjectName(QString::fromUtf8("timeEdit"));
        timeEdit->setGeometry(QRect(700, 550, 71, 21));
        gridLayoutWidget = new QWidget(centralwidget);
        gridLayoutWidget->setObjectName(QString::fromUtf8("gridLayoutWidget"));
        gridLayoutWidget->setGeometry(QRect(10, 10, 781, 521));
        gridLayout = new QGridLayout(gridLayoutWidget);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        horizontalScrollBar = new QScrollBar(centralwidget);
        horizontalScrollBar->setObjectName(QString::fromUtf8("horizontalScrollBar"));
        horizontalScrollBar->setGeometry(QRect(230, 550, 381, 31));
        horizontalScrollBar->setOrientation(Qt::Horizontal);
        ImageGame->setCentralWidget(centralwidget);

        retranslateUi(ImageGame);

        QMetaObject::connectSlotsByName(ImageGame);
    } // setupUi

    void retranslateUi(QMainWindow *ImageGame)
    {
        ImageGame->setWindowTitle(QCoreApplication::translate("ImageGame", "ImageGame", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ImageGame: public Ui_ImageGame {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_IMAGEGAME_H
