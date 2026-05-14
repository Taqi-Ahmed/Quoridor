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



