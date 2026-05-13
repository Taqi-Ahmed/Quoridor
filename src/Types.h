#ifndef TYPES_H
#define TYPES_H
struct Position {
private:
    int x;
    int y;

    bool operator==(const Position& other) const;
    bool operator<(const Position& other) const;
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

#endif // TYPES_H
