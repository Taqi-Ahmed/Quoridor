#include "game.h"

bool GameBoard::isWallbetween(Wall newWall) {
    for (Wall& w : walls) {
        if (newWall.isHorizontal) {
            // 1. Check against other horizontal walls (Check the Xs)
            if (w.isHorizontal && w.pos.get_y() == newWall.pos.get_y()) {
                // If they share the same Y, check if their Xs overlap
                if (w.pos.get_x() == newWall.pos.get_x() ||         // Exact match
                    w.pos.get_x() == newWall.pos.get_x() - 1 ||     // Overlaps on the left
                    w.pos.get_x() == newWall.pos.get_x() + 1) {     // Overlaps on the right
                    return true; // Wall collision detected
                }
            }
            // 2. Check against vertical walls crossing it
            else if (!w.isHorizontal && w.pos.get_x() == newWall.pos.get_x() && w.pos.get_y() == newWall.pos.get_y()) {
                return true; // Plus-sign crossing detected
            }
        } 
        else { // newWall is Vertical
            // 1. Check against other vertical walls (Check the Ys)
            if (!w.isHorizontal && w.pos.get_x() == newWall.pos.get_x()) {
                // If they share the same X, check if their Ys overlap
                if (w.pos.get_y() == newWall.pos.get_y() ||         // Exact match
                    w.pos.get_y() == newWall.pos.get_y() - 1 ||     // Overlaps on the top
                    w.pos.get_y() == newWall.pos.get_y() + 1) {     // Overlaps on the bottom
                    return true; // Wall collision detected
                }
            }
            // 2. Check against horizontal walls crossing it
           else if (!w.isHorizontal && w.pos.get_x() == newWall.pos.get_x() && w.pos.get_y() == newWall.pos.get_y()) {
                return true; // Plus-sign crossing detected
            }
        }
    }
    
    return false; // No walls in the way, safe to place!
}