#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <QAbstractButton>
#include <QColor>
#include <QIcon>
#include <QList>
#include <QMainWindow>
#include <QPoint>
#include <QString>

namespace Ui {
class gameWindow;
}

class QWidget;

class gameWindow : public QMainWindow
{
    Q_OBJECT

public:
    struct BoardStyleSheets {
        QString container;
        QString playableCell;
        QString playableCellMoveHighlight;
        QString wallSlot;
        QString wallSlotHover;
        QString intersection;
        QString intersectionHover;
    };

    BoardStyleSheets boardStyles;

    explicit gameWindow(QWidget *parent = nullptr);
    ~gameWindow();

    void renderPawn(int row, int col, QColor color);
    void applyBoardStyles();

    void renderWallHoverHighlight(int gridRow, int gridCol);
    void clearWallHoverHighlight();

    void renderValidPawnMoveHighlights(const QList<QPoint> &moveTargets);
    void clearValidPawnMoveHighlights();

protected:
    bool eventFilter(QObject *watched, QEvent *event) override;

private:
    int cellSize = 45;
    int wallSize = 10;
    int pawnSize = 35;

    QIcon createPawnIcon(const QColor &color) const;

    QAbstractButton *getCell(int row, int col) const;
    QAbstractButton *getPlayableCell(int row, int col) const;
    QAbstractButton *getWallCell(int row, int col) const;

    void renderBoard();
    void installWallHoverTracking(QWidget *widget, int gridRow, int gridCol);

    QList<QPoint> m_wallHoverCells;

    Ui::gameWindow *ui;
};

#endif // GAMEWINDOW_H
