#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "../game/gamewindow.h"
#include <QApplication>
#include <QScreen>
#include <QStyle>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setFixedSize(800,600);
    this->setWindowFlags(Qt::Window | Qt::WindowMinimizeButtonHint | Qt::WindowCloseButtonHint);
    this->setGeometry(
        QStyle::alignedRect(
            Qt::LeftToRight,
            Qt::AlignCenter,
            this->size(),
            QApplication::primaryScreen()->availableGeometry()
            )
        );
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_HumanBtn_clicked()
{
    gameWindow *myGame = new gameWindow();

    myGame->setAttribute(Qt::WA_DeleteOnClose);

    //show gameplay and hide the menu until the player returns or quits
    myGame->show();

    this->hide();
}


void MainWindow::on_quitBtn_clicked()
{
    QApplication::quit();
}


void MainWindow::on_rulesBtn_clicked()
{
    QMessageBox ruleBox(this);

    ruleBox.setWindowTitle("Quoridor Rules");
    ruleBox.setText(QUORIDOR_RULES);
    ruleBox.setTextFormat(Qt::RichText);


    ruleBox.setWindowFlags(Qt::Dialog | Qt::CustomizeWindowHint | Qt::WindowTitleHint | Qt::WindowCloseButtonHint);
    ruleBox.exec();


}

