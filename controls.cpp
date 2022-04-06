#include <pspctrl.h>
#include <stdio.h>

#include "controls.h"
#include "movement.h"

// Only used once inside controls.cpp, so it's safe to make it static
// (will make it invisible for other files)
static SceCtrlData pad;

void
execControls()
{
    sceCtrlReadBufferPositive(&pad, 1);

    if (pad.Buttons != 0) {
      if (pad.Buttons & PSP_CTRL_SQUARE) {
        printf("Square pressed \n");
      }
      if (pad.Buttons & PSP_CTRL_TRIANGLE) {
        printf("Triangle pressed \n");
      }
      if (pad.Buttons & PSP_CTRL_CIRCLE) {
        printf("Cicle pressed \n");
      }
      if (pad.Buttons & PSP_CTRL_CROSS) {
        printf("Cross pressed \n");
      }

      if (pad.Buttons & PSP_CTRL_UP) {
        tryWalk(eWalkUp);
        printf("Up pressed \n");
      }
      if (pad.Buttons & PSP_CTRL_DOWN) {
        tryWalk(eWalkDown);
        printf("Down pressed \n");
      }
      if (pad.Buttons & PSP_CTRL_LEFT) {
        tryWalk(eWalkLeft);
        printf("Left pressed \n");
      }
      if (pad.Buttons & PSP_CTRL_RIGHT) {
        tryWalk(eWalkRight);
        printf("Right pressed \n");
      }

      if (pad.Buttons & PSP_CTRL_START) {
        printf("Start pressed \n");
      }
      if (pad.Buttons & PSP_CTRL_SELECT) {
        printf("Select pressed \n");
      }
      if (pad.Buttons & PSP_CTRL_LTRIGGER) {
        printf("L-trigger pressed \n");
      }
      if (pad.Buttons & PSP_CTRL_RTRIGGER) {
        printf("R-trigger pressed \n");
      }
    }
}
