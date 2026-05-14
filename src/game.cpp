#include "game.h"
bool GameBoard::is_valid_wall_placement(bool is_horizontal, int r, int c){
    bool valid=false;
    if (r>8 || r<1 || c>8 || c<1) return false;
        //check for any possible collisions may occur before placing the wall at this position
        // wall is horizontal then y is const ( row gives me y value , colunmn gives me x value)
        // wall is  vertival then x is const
        for (auto& wall: walls){

            if(wall.isHorizontal && is_horizontal ){
               if((wall.pos.y==r) && (wall.pos.x==c || wall.pos.x==c-1 || wall.pos.x==c+1))
                return false; }

            if (! wall.isHorizontal && ! is_horizontal) {
               if((wall.pos.x==c) && (wall.pos.y==r || wall.pos.y==r-1 || wall.pos.y==r+1))
                return false; }

            if (is_horizontal && ! wall.isHorizontal){
                if(wall.pos.y==r && wall.pos.x== c) return false;
            }

            if (!is_horizontal && wall.isHorizontal){
                if(r== wall.pos.y && c==wall.pos.x) return false;
            }

        }

        //check when the added wall blocks the opponent move or not
        Wall tempWall={{c,r}, is_horizontal};
        walls.push_back(tempWall);
        valid =BFS_search();
        walls.pop_back();

        return valid;

    }

bool GameBoard::isWallbetween(Wall newWall) {
    for (Wall& w : walls) {
        if (newWall.isHorizontal) {
            // 1. Check against other horizontal walls (Check the Xs)
            if (w.isHorizontal && w.pos.y == newWall.pos.y) {
                // If they share the same Y, check if their Xs overlap
                if (w.pos.x == newWall.pos.x ||         // Exact match
                    w.pos.x == newWall.pos.x - 1 ||     // Overlaps on the left
                    w.pos.x == newWall.pos.x + 1) {     // Overlaps on the right
                    return true; // Wall collision detected
                }
            }
            // 2. Check against vertical walls crossing it
            else if (!w.isHorizontal && w.pos.x == newWall.pos.x && w.pos.y == newWall.pos.y) {
                return true; // Plus-sign crossing detected
            }
        } 
        else { // newWall is Vertical
            // 1. Check against other vertical walls (Check the Ys)
            if (!w.isHorizontal && w.pos.x == newWall.pos.x) {
                // If they share the same X, check if their Ys overlap
                if (w.pos.y == newWall.pos.y ||         // Exact match
                    w.pos.y == newWall.pos.y - 1 ||     // Overlaps on the top
                    w.pos.y == newWall.pos.y + 1) {     // Overlaps on the bottom
                    return true; // Wall collision detected
                }
            }
            // 2. Check against horizontal walls crossing it
           else if (!w.isHorizontal && w.pos.x == newWall.pos.x && w.pos.y == newWall.pos.y) {
                return true; // Plus-sign crossing detected
            }
        }
    }
    
    return false; // No walls in the way, safe to place!
}


