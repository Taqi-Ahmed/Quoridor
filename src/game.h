#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <vector>
#include "Types.h"
using namespace std;

class GameBoard
{
private:
    // Wall placements (8 grooves x 8 grooves)
    int size;
    vector<Wall> walls;
    vector<Position> Grid;
    // Player state
    Player p1;
    Player p2;

    // Turn tracking (e.g., 1 for P1, 2 for P2)
    int current_turn;
    bool BFS_search();
    bool isWallbetween(Wall wall);
    bool isWallBlocking(Wall wall,Player player, Position target);
    bool isOutOfBounds(Position pos);
    bool isOneStepMove(Position move);
    bool wallBlocksMove(Player player, Position target);
    bool isDiagonalValid(Player player, Position target, Player opp);

public:
    // Methods you'll need to implement Phase 1 & 3:
    bool is_valid_pawn_move(Player p, Position target,Player opp);
    vector<Position> getValidMoves();
    bool is_valid_wall_placement(bool is_horizontal, int r, int c);
    void movePlayer(Player &player, Position pos);
    void placeWall(Position pos, bool isHorizontal);
    
};
#endif
