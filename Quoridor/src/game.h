#include <iostream>
#include <vector>
using namespace std;

struct Position {
    int x;
    int y;
};

struct Wall {
    Position pos;
    bool isHorizontal;
};

struct Player {
    Position pos;
    bool won_game;
    int walls_left; // Starts at 10 for a 2-player game
    int goal_row;   // P1's goal is row 8 (or 9 in 1-index), P2's is row 0 (or 1)
};

class GameBoard {
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
    bool isWallbetween(Position from, Position to);

public:
    // Methods you'll need to implement Phase 1 & 3:
    bool is_valid_pawn_move(Player p, Position target);
    bool is_valid_wall_placement(bool is_horizontal, int r, int c);
    void movePlayer(Player &player,Position pos);
    void placeWall(Position pos, bool isHorizontal);

};

struct game{

    private:
        
    public:
};