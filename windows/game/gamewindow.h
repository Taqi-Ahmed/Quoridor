#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <QAbstractButton>
#include <QColor>
#include <QIcon>
#include <QMainWindow>

namespace Ui {
class gameWindow;
}

class gameWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit gameWindow(QWidget *parent = nullptr);
    ~gameWindow();

    void renderPawn(int row, int col, QColor color);
private:
    int cellSize = 50;
    int wallSize = 10;
    int pawnSize = 35;

    QIcon createPawnIcon(const QColor &color) const;

    QAbstractButton *getCell(int row, int col) const;
    QAbstractButton *getPlayableCell(int row, int col) const;
    QAbstractButton *getWallCell(int row, int col) const;

    void renderBoard();

    Ui::gameWindow *ui;
};

#endif // GAMEWINDOW_H
