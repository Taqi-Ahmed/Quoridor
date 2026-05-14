#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

private slots:
    void on_HumanBtn_clicked();

    void on_quitBtn_clicked();

    void on_rulesBtn_clicked();

private:
    Ui::MainWindow *ui;
    const QString QUORIDOR_RULES = R"(
    <h2>Quoridor Game Rules</h2>

    <h3><b>Objective</b></h3>
    <p>Be the first player to move your pawn to any square on the opposite side of the board.</p>

    <h3><b>Setup & Pieces</b></h3>
    <ul>
      <li>The game is played on a 9x9 square board.</li>
      <li>Each player has a pawn that begins at the center of their respective base line.</li>
      <li>Each player has 10 walls.</li>
    </ul>

    <h3><b>Movement</b></h3>
    <p>On each turn, a player must either move their pawn or place a wall.</p>
    <ul>
      <li>Pawns move one square orthogonally (not diagonally).</li>
      <li>Players cannot move through walls or opponent pawns.</li>
      <li>If a player's pawn is adjacent to an opponent's pawn, the player can jump over the opponent's pawn (if there's no wall blocking).</li>
      <li>If a jump is blocked by a wall, the player can move diagonally around the opponent's pawn.</li>
    </ul>

    <h3><b>Wall Placement</b></h3>
    <ul>
      <li>Walls are two squares long and are placed on the edges between squares.</li>
      <li>Walls cannot overlap or cross other walls.</li>
      <li><span style="color: #D32F2F;"><b>Critical Rule:</b></span> Walls cannot be placed to completely block a player's path to the goal (there must always be a valid path to the goal for each player).</li>
      <li>Once placed, walls cannot be moved.</li>
    </ul>
    )";
};
#endif // MAINWINDOW_H
