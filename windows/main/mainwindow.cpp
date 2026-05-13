#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "../game/gamewindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
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

