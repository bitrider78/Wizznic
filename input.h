#ifndef INPUT_H_INCLUDED
#define INPUT_H_INCLUDED

/************************************************************************
 * This file is part of Wizznic.                                        *
 * Copyright 2009-2011 Jimmy Christensen <dusted@dusted.dk>             *
 * Wizznic is free software: you can redistribute it and/or modify      *
 * it under the terms of the GNU General Public License as published by *
 * the Free Software Foundation, either version 3 of the License, or    *
 * (at your option) any later version.                                  *
 *                                                                      *
 * Wizznic is distributed in the hope that it will be useful,           *
 * but WITHOUT ANY WARRANTY; without even the implied warranty of       *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the        *
 * GNU General Public License for more details.                         *
 *                                                                      *
 * You should have received a copy of the GNU General Public License    *
 * along with Foobar.  If not, see <http://www.gnu.org/licenses/>.      *
 ************************************************************************/

#include <SDL/SDL.h>
#include "board.h"

#define C_UP 0
#define C_DOWN 1
#define C_LEFT 2
#define C_RIGHT 3
#define C_BTNY 4
#define C_BTNX 5
#define C_BTNA 6
#define C_BTNB 7
#define C_SHOULDERA 8
#define C_SHOULDERB 9
#define C_BTNMENU 10
#define C_BTNSELECT 11
#define C_BTNVOLUP 12
#define C_BTNVOLDOWN 13
#define C_NUM 14

typedef struct {
  int startX, startY;
  int curX, curY;
  int vpX, vpY; // "virtual"/scaled pixel positions
  int downTime;
  int timeSinceMoved;
  int isDown;
} inpPointerState_t;

inline void setButton(int btn); //Nasty
inline int getButton(int btn);
inline int getBtnTime(int btn);
inline void resetBtnTimer(int btn);
inline void resetBtn(int btn);
inline void resetMouseBtn();
void resetBtnAll();
int runControls();
void initControls();

inline inpPointerState_t* getInpPointerState();

#endif // INPUT_H_INCLUDED
