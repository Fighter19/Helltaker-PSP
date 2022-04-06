#pragma once

enum WalkDirection
{
  eWalkUp,
  eWalkDown,
  eWalkLeft,
  eWalkRight
};

bool
checkIfWalkable(enum WalkDirection direction);

void
tryWalk(enum WalkDirection direction);
