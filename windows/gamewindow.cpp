#include "gamewindow.h"
#include "ui_gamewindow.h"

#include <QAbstractButton>
#include <QPushButton>
#include <QToolButton>
#include <QPainter>
#include <QPixmap>
#include <QIcon>
#include <QRectF>

gameWindow::gameWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::gameWindow)
{
    ui->setupUi(this);

    renderBoard(); // Render the board

    renderPawn(1, 4, QColor("#4285F4")); // Blue Pawn at "e9"
    renderPawn(8, 4, QColor("#EA4335")); // Red Pawn at "e1"
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
                tb->setStyleSheet(
                    "QToolButton { background-color: white; border-radius: 5px; "
                    "padding: 0px; margin: 0px; border: none; }");
                cell = tb;
            } else if (row % 2 != 0 && col % 2 == 0) {
                // Horizontal Wall Slot
                cell = new QPushButton(this);
                cell->setFixedSize(cellSize, wallSize);
            } else if (row % 2 == 0 && col % 2 != 0) {
                // Vertical Wall Slot
                cell = new QPushButton(this);
                cell->setFixedSize(wallSize, cellSize);
            } else {
                // Intersection
                cell = new QPushButton(this);
                cell->setFixedSize(wallSize, wallSize);
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
