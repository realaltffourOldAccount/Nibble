#ifndef CHSR_API
#define CHSR_API

/*
        OS Specific Includes
*/
#include "defs.h"
#if (__OS__ == __OS_WIN32__) || (__OS__ == __OS_WIN64__)
#include <Windows.h>
#elif (__OS__ == __OS_LINUX__)
#include <unistd.h>
#endif

/*
    Api Includes
*/
#include "__init.h"
#include "error_macros.h"
#include "globals.h"
#include "macros.h"
#include "univ_includes.h"

/*
    Api Graphics Engine
*/
#include "engine/GEngine.h"

/*
    Api Defines
*/
#define PCE_CELL_NUM 8
#define BOARD_W 700
#define BOARD_H 700
#define CELL_W float(float(BOARD_W) / float(PCE_CELL_NUM))
#define CELL_H float(float(BOARD_H) / float(PCE_CELL_NUM))
#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600
#define FPS_WINDOW_LIMIT 60
#define SELECT_SCALE 1.1f

#define WHITE_CHECKS_BLACK 1
#define BLACK_CHECKS_WHITE 2
#define WHITE_CHECKMATES_BLACK 3
#define BLACK_CHECKMATES_WHITE 4
#define NO_CHECKS 5

/*
    Api Functions
*/

#endif