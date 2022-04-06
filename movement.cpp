#include "movement.h"
#include "field.h"

/* Checks if character on pos can move to new pos
 * @param new_pos is a pointer to the position that can be walked to,
 *    only filled if "not-NULL"
 */
bool
checkIfWalkable(struct Position pos, struct Position *new_pos, enum WalkDirection direction)
{
  struct Position target = pos;
  // In case something unexpected happens, assume it won't work
  enum FieldPieces piece = eWall;
  switch(direction) {
    case eWalkUp:
      if (pos.y > 0)
        target.y--;
      else
        return false;
      break;
    case eWalkDown:
      if (pos.y+1 < Y_SIZE)
        target.y++;
      else
        return false;
      break;
    case eWalkLeft:
      if (pos.x > 0)
        target.x--;
      else
        return false;
      break;
    case eWalkRight:
      if (pos.x+1 < X_SIZE)
        target.x++;
      else
        return false;
      break;
  }
  
  piece = field.pieces[target.y][target.x];
  
  bool isWalkable = false;
  switch(piece) {
    case eGround:
      isWalkable = true;
      break;
    case eEnemy:
      // Kick the enemy but stand in place
      isWalkable = false;
      struct Position enemy_pos_new;
      if (!checkIfWalkable(target, &enemy_pos_new, direction)) {
          field.pieces[target.y][target.x] = eGround;
      } else {
        // Clear old location
        field.pieces[target.y][target.x] = eGround;
        // Set enemy to new pos
        field.pieces[enemy_pos_new.y][enemy_pos_new.x] = eEnemy;
      }
      break;
    // TODO: Do something similar with the rock
    case eRock:
      isWalkable = false;
      struct Position rock_pos;
      if (checkIfWalkable(target, &rock_pos, direction)) {
        field.pieces[target.y][target.x] = eGround;
        field.pieces[rock_pos.y][rock_pos.x] = eRock;
      }
      break;
    default:
      isWalkable = false;
      break;
  }
  
  // Save new position if walkable and asked to
  if (isWalkable && new_pos) {
    *new_pos = target;
  }
  
  return isWalkable;
}

void
tryWalk(enum WalkDirection direction)
{
  struct Position target_pos;
  if (checkIfWalkable(player, &target_pos, direction)) {
    player = target_pos;
  }
}
