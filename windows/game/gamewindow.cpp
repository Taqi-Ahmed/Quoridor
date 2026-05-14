#include "gamewindow.h"
#include "ui_gamewindow.h"

#include <QAbstractButton>
#include <QPushButton>
#include <QToolButton>
#include <QPainter>
#include <QPixmap>
#include <QIcon>
#include <QRectF>

namespace {

gameWindow::BoardStyleSheets defaultBoardStyles()
{
    gameWindow::BoardStyleSheets s;
    s.container = QStringLiteral(
        "QWidget#boardContainer { background-color: #e2e8f0; }");

    s.playableCell = QStringLiteral(
        "QToolButton { background-color: #ffffff; border-radius: 5px; "
        "padding: 0px; margin: 0px; border: none; }");

    s.playableCellMoveHighlight = QStringLiteral(
        "QToolButton { background-color: #ffffff; border-radius: 5px; "
        "padding: 0px; margin: 0px; "
        "border: 2px solid #22c55e; }"
    "QToolButton:hover { background-color: #26e76d; }");

    s.wallSlot = QStringLiteral(
        "QPushButton { background-color: transparent; border: none; }"
        "QPushButton:hover { background-color: transparent; }"
        "QPushButton:pressed { background-color: transparent; }"
        "QPushButton:focus { outline: none; }");

    s.intersection = QStringLiteral(
        "QPushButton {"
        "  background-color: #9a9a9a;"
        "  border: none;"
        "  border-radius: 3px;"
        "  margin: 3px;"
        "}"
        "QPushButton:hover {"
        "  background-color: #9a9a9a;"
        "}"
        "QPushButton:pressed {"
        "  background-color: #9a9a9a;"
        "}"
        "QPushButton:focus { outline: none; }");

    return s;
}

} // namespace

gameWindow::gameWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::gameWindow)
{
    ui->setupUi(this);

    boardStyles = defaultBoardStyles();
    ui->boardContainer->setStyleSheet(boardStyles.container);

    renderBoard(); // Render the board

    renderPawn(8, 4, QColor("#4285F4")); // Blue Pawn at "e9"
    renderPawn(0, 4, QColor("#EA4335")); // Red Pawn at "e1"

    renderValidPawnMoveHighlights(QList<QPoint>() << QPoint(8, 5) << QPoint(8, 3) << QPoint(7, 4));
}

gameWindow::~gameWindow()
{
    delete ui;
}

QIcon gameWindow::createPawnIcon(const QColor &color) const
{
    QPixmap pixmap(cellSize, cellSize);
    pixmap.fill(Qt::transparent);

    QPainter painter(&pixmap);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setBrush(color);
    painter.setPen(Qt::NoPen);
    const QRectF bounds = QRectF(pixmap.rect());
    const qreal side = qreal(pawnSize);
    const QRectF ellipse(bounds.center().x() - side / 2.0,
                         bounds.center().y() - side / 2.0,
                         side,
                         side);
    painter.drawEllipse(ellipse);

    return QIcon(pixmap);
}

QAbstractButton *gameWindow::getCell(int row, int col) const {
    QLayoutItem *item = ui->boardLayout->itemAtPosition(row, col);
    if (item) {
        return qobject_cast<QAbstractButton *>(item->widget());
    }
    return nullptr;
};

QAbstractButton *gameWindow::getPlayableCell(int row, int col) const {
    if (row < 0 || row >= 9 || col < 0 || col >= 9) {
        return nullptr;
    }

    row = row * 2;
    col = col * 2;

    return getCell(row, col);
};

QAbstractButton *gameWindow::getWallCell(int row, int col) const {
    if (row < 0 || row >= 17 || col < 0 || col >= 17) {
        return nullptr;
    }

    row = row * 2;
    col = col * 2;

    return getCell(row, col);
}

void gameWindow::applyBoardStyles()
{
    ui->boardContainer->setStyleSheet(boardStyles.container);

    for (int row = 0; row < 17; ++row) {
        for (int col = 0; col < 17; ++col) {
            QAbstractButton *cell = getCell(row, col);
            if (!cell) {
                continue;
            }
            if (row % 2 == 0 && col % 2 == 0) {
                cell->setStyleSheet(boardStyles.playableCell);
            } else if ((row % 2 != 0 && col % 2 == 0)
                       || (row % 2 == 0 && col % 2 != 0)) {
                cell->setStyleSheet(boardStyles.wallSlot);
            } else {
                cell->setStyleSheet(boardStyles.intersection);
            }
        }
    }
}

void gameWindow::renderBoard() {
    // Populate the grid layout created in Qt Designer
    for (int row = 0; row < 17; ++row) {
        for (int col = 0; col < 17; ++col) {

            QAbstractButton *cell = nullptr;

            // Example sizing logic:
            if (row % 2 == 0 && col % 2 == 0) {
                // Playable cell (9x9) — QToolButton centers icon-only artwork reliably
                auto *tb = new QToolButton(this);
                tb->setToolButtonStyle(Qt::ToolButtonIconOnly);
                tb->setAutoRaise(false);
                tb->setFixedSize(cellSize, cellSize);
                tb->setStyleSheet(boardStyles.playableCell);
                cell = tb;
            } else if (row % 2 != 0 && col % 2 == 0) {
                // Horizontal wall slot (transparent until a wall is shown)
                auto *wallBtn = new QPushButton(this);
                wallBtn->setFlat(true);
                wallBtn->setAutoDefault(false);
                wallBtn->setDefault(false);
                wallBtn->setFixedSize(cellSize, wallSize);
                wallBtn->setStyleSheet(boardStyles.wallSlot);
                cell = wallBtn;
            } else if (row % 2 == 0 && col % 2 != 0) {
                auto *wallBtn = new QPushButton(this);
                wallBtn->setFlat(true);
                wallBtn->setAutoDefault(false);
                wallBtn->setDefault(false);
                wallBtn->setFixedSize(wallSize, cellSize);
                wallBtn->setStyleSheet(boardStyles.wallSlot);
                cell = wallBtn;
            } else {
                // Intersection — small grey dot, no hover/press feedback
                auto *dotBtn = new QPushButton(this);
                dotBtn->setFlat(true);
                dotBtn->setAutoDefault(false);
                dotBtn->setDefault(false);
                dotBtn->setFixedSize(wallSize, wallSize);
                dotBtn->setStyleSheet(boardStyles.intersection);
                cell = dotBtn;
            }

            // Add the cell to the layout created in Qt Designer
            ui->boardLayout->addWidget(cell, row, col);
        }
    }
}

void gameWindow::renderPawn(int row, int col, QColor color) {    
    QAbstractButton *cell = getPlayableCell(row, col);
    if (cell) {
        cell->setIcon(createPawnIcon(color));
        cell->setIconSize(QSize(cellSize, cellSize));
    }
}

void gameWindow::renderValidPawnMoveHighlights(const QList<QPoint> &moveTargets)
{
    clearValidPawnMoveHighlights();
    for (const QPoint &p : moveTargets) {
        if (QAbstractButton *cell = getPlayableCell(p.x(), p.y())) {
            cell->setStyleSheet(boardStyles.playableCellMoveHighlight);
        }
    }
}

void gameWindow::clearValidPawnMoveHighlights()
{
    for (int r = 0; r < 9; ++r) {
        for (int c = 0; c < 9; ++c) {
            if (QAbstractButton *cell = getPlayableCell(r, c)) {
                cell->setStyleSheet(boardStyles.playableCell);
            }
        }
    }
}