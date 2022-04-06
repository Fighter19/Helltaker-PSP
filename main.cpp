/*
 * PSP Software Development Kit - http://www.pspdev.org
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * main.c - Basic Input demo -- reads from control pad and indicates button
 *          presses.
 *
 * Copyright (c) 2005 Marcus R. Brown <mrbrown@ocgnet.org>
 * Copyright (c) 2005 James Forshaw <tyranid@gmail.com>
 * Copyright (c) 2005 John Kelley <ps2dev@kelley.ca>
 * Copyright (c) 2005 Donour Sizemore <donour@uchicago.edu>
 *
 * $Id: main.c 1095 2005-09-27 21:02:16Z jim $
 */
#include <pspkernel.h>
#include <pspdebug.h>
#include <pspctrl.h>
#include <stdlib.h>
#include <string.h>

/* Define the module info section */
PSP_MODULE_INFO("CONTROLTEST", 0, 1, 1);

/* Define the main thread's attribute value (optional) */
PSP_MAIN_THREAD_ATTR(THREAD_ATTR_USER | THREAD_ATTR_VFPU);

/* Define printf, just to make typing easier */
#define printf	pspDebugScreenPrintf

void dump_threadstatus(void);

int done = 0;

/* Exit callback */
int exit_callback(int arg1, int arg2, void *common)
{
	done = 1;
	return 0;
}

/* Callback thread */
int CallbackThread(SceSize args, void *argp)
{
	int cbid;

	cbid = sceKernelCreateCallback("Exit Callback", exit_callback, NULL);
	sceKernelRegisterExitCallback(cbid);
	sceKernelSleepThreadCB();

	return 0;
}

/* Sets up the callback thread and returns its thread id */
int SetupCallbacks(void)
{
	int thid = 0;

	thid = sceKernelCreateThread("update_thread", CallbackThread,
				     0x11, 0xFA0, 0, 0);
	if(thid >= 0)
	{
		sceKernelStartThread(thid, 0, 0);
	}

	return thid;
}

static size_t player_x = 5;
static size_t player_y = 3;

// Offset of the board in characters
#define X_OFFSET 10
#define Y_OFFSET 10

#define X_SIZE 6
#define Y_SIZE 7

enum FieldPieces {
    eGround,
    eRock,
    eKey,
    eGoal,
    eLock,
    eEnemy,
    eWall
};

static struct Field {
    enum FieldPieces pieces[Y_SIZE][X_SIZE];
} field = {
    .pieces = {
        {eWall,    eWall,    eWall,    eGoal,    eGround,   eWall},
        {eWall,    eWall,    eWall,    eGround,  eLock,     eWall},
        {eGround,  eLock,    eWall,    eRock,    eRock,     eRock},
        
        {eEnemy,   eRock,    eGround,  eEnemy,   eRock,     eGround},
        {eGround,  eWall,    eEnemy,   eGround,  eGround,   eGround},
        {eGround,  eWall,    eWall,    eGround,  eWall,     eWall},
        {eGround,  eGround,  eGround,  eGround,  eWall,     eWall}
    }
};

const char *ground_symbol = " ";
const char *rock_symbol = "o";
const char *player_symbol = "1";
const char *goal_symbol = "4";
const char *key_symbol = "5";
const char *wall_symbol = "#";
const char *lock_symbol = "L";
const char *enemy_symbol = "E";

const char* look_up_symbol(enum FieldPieces piece) {
    const char *return_value = ground_symbol;
    switch(piece) {
        case eGround:
            return_value = ground_symbol;
            break;
        case eRock:
            return_value = rock_symbol;
            break;
        case eKey:
            return_value = key_symbol;
            break;
        case eGoal:
            return_value = goal_symbol;
            break;
        case eLock:
            return_value = lock_symbol;
            break;
        case eEnemy:
            return_value = enemy_symbol;
            break;
        case eWall:
            return_value = wall_symbol;
            break;
    }
    return return_value;
}

/** Prints the content of the field to screen */
void printField()
{
    pspDebugScreenSetXY(X_OFFSET-1, Y_OFFSET-1);
    for (size_t x = 0; x < X_SIZE+2; x++) {
        pspDebugScreenPuts("-");
    }
        
    for (size_t y = 0; y < Y_SIZE; y++) {
        pspDebugScreenSetXY(X_OFFSET-1, Y_OFFSET+y);
        pspDebugScreenPuts("|");
        for (size_t x = 0; x < X_SIZE; x++) {
            const char *symbol = look_up_symbol(field.pieces[y][x]);
            pspDebugScreenPuts(symbol);
        }
        pspDebugScreenPuts("|");
    }
    
    pspDebugScreenSetXY(X_OFFSET-1, Y_OFFSET+Y_SIZE);
    for (size_t x = 0; x < X_SIZE+2; x++) {
        pspDebugScreenPuts("-");
    }
    
    pspDebugScreenSetXY(X_OFFSET+player_x, Y_OFFSET+player_y);
    pspDebugScreenPuts(player_symbol);
}

int main(void)
{
	SceCtrlData pad;

	pspDebugScreenInit();
	SetupCallbacks();

	sceCtrlSetSamplingCycle(0);
	sceCtrlSetSamplingMode(PSP_CTRL_MODE_ANALOG);

	while(!done){
		pspDebugScreenSetXY(0, 2);

    		sceCtrlReadBufferPositive(&pad, 1); 

		printf("Analog X = %d ", pad.Lx);
		printf("Analog Y = %d \n", pad.Ly);
        
        printField();
        
        pspDebugScreenSetXY(0, 3);

		if (pad.Buttons != 0){
			if (pad.Buttons & PSP_CTRL_SQUARE){
				printf("Square pressed \n");
			}
			if (pad.Buttons & PSP_CTRL_TRIANGLE){
				printf("Triangle pressed \n");
			} 
			if (pad.Buttons & PSP_CTRL_CIRCLE){
				printf("Cicle pressed \n");
			} 
			if (pad.Buttons & PSP_CTRL_CROSS){
				printf("Cross pressed \n");
			} 

			if (pad.Buttons & PSP_CTRL_UP){
				printf("Up pressed \n");
			} 
			if (pad.Buttons & PSP_CTRL_DOWN){
				printf("Down pressed \n");
			} 
			if (pad.Buttons & PSP_CTRL_LEFT){
				printf("Left pressed \n");
			} 
			if (pad.Buttons & PSP_CTRL_RIGHT){
				printf("Right pressed \n");
			}      

			if (pad.Buttons & PSP_CTRL_START){
				printf("Start pressed \n");
			}
			if (pad.Buttons & PSP_CTRL_SELECT){
				printf("Select pressed \n");
			}
			if (pad.Buttons & PSP_CTRL_LTRIGGER){
				printf("L-trigger pressed \n");
			}
			if (pad.Buttons & PSP_CTRL_RTRIGGER){
				printf("R-trigger pressed \n");
			}      

		}
	}

	sceKernelExitGame();
	return 0;
}
