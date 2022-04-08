#ifndef BOARDS_H__
#define BOARDS_H__

#if defined(BOARD_V100)
    #include "board_v100.h"
#elif defined(BOARD_V001)
    #include "board_v001.h"
#else
    #error "board is not defined"
#endif

#endif
