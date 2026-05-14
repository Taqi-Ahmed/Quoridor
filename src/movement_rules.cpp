#include "game.h"

bool GameBoard::isWallBlocking(Wall wall, Player player, Position target){
    Position playerPos = player.pos;
    Position move = target - playerPos;

    if (!isOneStepMove(move)) {
        return false;
    }
    //moving up
    if(move == Position{0,1}) {
        if(wall.pos == (playerPos + Position{-1,0}) && wall.isHorizontal){
            return true;
        }
        else if(wall.pos == playerPos && wall.isHorizontal){
            return true;
        }
    }
    //moving down
    else if(move == Position{0,-1}){
        if(wall.pos == (playerPos + Position{-1,-1}) && wall.isHorizontal){
            return true;
        }
        else if(wall.pos == (playerPos + Position{0,-1}) && wall.isHorizontal){
            return true;
        }
    }
    //moving right
    else if(move == Position{1,0}){
        if(wall.pos == (playerPos + Position{0,-1}) && !wall.isHorizontal){
            return true;
        }
        else if(wall.pos == playerPos && !wall.isHorizontal){
            return true;
        }
    }
    
    //moving left
    else if(move == Position{-1,0}){
        if(wall.pos == (playerPos + Position{-1,-1}) && !wall.isHorizontal){
            return true;
        }
        else if(wall.pos == (playerPos + Position{-1,0}) && !wall.isHorizontal){
            return true;
        }
    }

    return false;
}

bool GameBoard::isOutOfBounds(Position pos){
    return pos.x < 0 || pos.x >= size || pos.y < 0 || pos.y >= size;
}

bool GameBoard::isOneStepMove(Position move){
    return move == Position{0,1} ||
           move == Position{0,-1} ||
           move == Position{1,0} ||
           move == Position{-1,0};
}

bool GameBoard::wallBlocksMove(Player player, Position target) {
    for (Wall wall : walls) {
        if (isWallBlocking(wall, player, target)) {
            return true;
        }
    }
    return false;
}

bool GameBoard::isDiagonalValid(Player player, Position target, Player opp){
    Position toOpponent = opp.pos - player.pos;
    Position jumpTarget = opp.pos + toOpponent;

    if (!isOneStepMove(toOpponent)) {
        return false;
    }

    if (wallBlocksMove(player, opp.pos)) {
        return false;
    }

    if (!isOutOfBounds(jumpTarget) && !wallBlocksMove(opp, jumpTarget)) {
        return false;
    }

    Position diagonal1 = opp.pos + Position{-toOpponent.y, toOpponent.x};
    Position diagonal2 = opp.pos + Position{toOpponent.y, -toOpponent.x};

    if (!(target == diagonal1) && !(target == diagonal2)) {
        return false;
    }

    return !wallBlocksMove(opp, target);
}

bool GameBoard::is_valid_pawn_move(Player p, Position target,Player opp){
    Position playerPos = p.pos;
    Position move = target - playerPos;

    if(isOutOfBounds(target)){
        return false;
    }

    //check if target doesn't have an opp on it
    if(target == opp.pos){
        return false;
    }

    //normal move
    if(isOneStepMove(move)){
        return !wallBlocksMove(p, target);
    }

    Position toOpponent = opp.pos - playerPos;

    //jump and diagonal moves are only valid when the opponent is beside the player
    if(!isOneStepMove(toOpponent)){
        return false;
    }

    if(wallBlocksMove(p, opp.pos)){
        return false;
    }

    //straight jump over the opponent
    Position jumpTarget = opp.pos + toOpponent;

    if(target == jumpTarget){
        return !isOutOfBounds(jumpTarget) && !wallBlocksMove(opp, jumpTarget);
    }

    //diagonal move around the opponent
    return isDiagonalValid(p, target, opp);
}
