#include "movement.h"
#include "field.h"

bool
checkIfWalkable(enum WalkDirection direction)
{
  // In case something unexpected happens, assume it won't work
  enum FieldPieces piece = eWall;
  switch(direction) {
    case eWalkUp:
      if (player_y > 0)
        piece = field.pieces[player_y-1][player_x];
      break;
    case eWalkDown:
      if (player_y+1 < Y_SIZE)
        piece = field.pieces[player_y+1][player_x];
      break;
    case eWalkLeft:
      if (player_x > 0)
        piece = field.pieces[player_y][player_x-1];
      break;
    case eWalkRight:
      if (player_x+1 < X_SIZE)
        piece = field.pieces[player_y][player_x+1];
      break;
  }
  
  bool isWalkable = false;
  switch(piece) {
    case eGround:
      isWalkable = true;
      break;
    default:
      isWalkable = false;
      break;
  }
  
  return isWalkable;
}

void
tryWalk(enum WalkDirection direction)
{
  if (checkIfWalkable(direction)) {
    switch(direction) {
      case eWalkUp:
        player_y -= 1;
        break;
      case eWalkDown:
        player_y += 1;
        break;
      case eWalkLeft:
        player_x -= 1;
        break;
      case eWalkRight:
        player_x += 1;
        break;
    }    
  }
}
