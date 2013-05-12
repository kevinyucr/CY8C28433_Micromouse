#ifndef MAZE_H
#define MAZE_H

#include <m8c.h>        // part specific constants and macros
#include "PSoCAPI.h"    // PSoC API definitions for all User Modules
#include "PSoCGPIOINT.h"
#include "MicromouseModules.h"

typedef unsigned char CellFlags;  // Represents a cell and it's associated flags
typedef unsigned char CellIndex;

extern unsigned char mazeFlags[];

#define MAZE_HEIGHT 16
#define MAZE_WIDTH  16
#define MAZE_CELL_COUNT  (MAZE_HEIGHT * MAZE_WIDTH)
#define MAZE_UPPER_RIGHT (MAZE_CELL_COUNT - 1)
#define MAZE_LOWER_LEFT  0

#define MAZE_QUEUE_SIZE 128  // Power of two
#define MAZE_QUEUE_MASK 0x7F

#define CELLINDEX_NS 1;
#define CELLINDEX_WE MAZE_WIDTH;

#define CELL_START  0x00   // Start cell
#define CELL_CENTER 0x77   // Center of a 16x16 maze

extern CellIndex Mouse_Position;

// Cell flags
// b[7] - 
// b[6] - WALL_WEST
// b[5] - 
// b[4] - WALL_SOUTH
// b[3] - 
// b[2] - WALL_EAST
// b[1] - CELL_IN_QUEUE
// b[0] - WALL_NORTH
// Absolute wall position
#define WALL_WEST  0x40
#define WALL_SOUTH 0x10
#define WALL_EAST  0x04
#define WALL_NORTH 0x01

#define WALL_MASK  0x55  // A mask that allows only WALL flags

#define CELL_IN_QUEUE 0x02

//---- Directions -----
typedef unsigned char Direction;
// Use to designate cells relative to the current direction of the mouse
typedef Direction MouseRelative;
#define MOUSE_LEFT   0
#define MOUSE_BEHIND 1
#define MOUSE_RIGHT  2
#define MOUSE_FRONT  3

// Use for direction mouse is facing
// Use for compass-relative cell positions relative to the mouse
typedef Direction CompassRelative;
#define MOUSE_WEST   0
#define MOUSE_SOUTH  1
#define MOUSE_EAST   2
#define MOUSE_NORTH  3

extern const char _DirToFlags[];
#define CompassToWallFlags(d) _DirToFlags[d]

Direction RotateDirectionLeft(Direction d, unsigned char n);
Direction RotateDirectionRight(Direction d,  unsigned char n);

// Desired mouse-relative direction and mouse heading to compass-relative
CompassRelative MouseToCompass(MouseRelative direction, CompassRelative heading);

extern CompassRelative Mouse_Direction;

// ----------------------------

// Move 
void MoveMouseCompass(CompassRelative d);

#define cellWallExists(c, d)   (mazeFlags[c] &  d)
#define cellSetFlags(c, f)     (mazeFlags[c] |= f)
#define cellClearFlags(c, f)   (mazeFlags[c] &= (~f))

#define cellIsInQueue(c)       (mazeFlags[c] & CELL_IN_QUEUE)

#define cellGetColumn(c)       (c & 0x0F)
#define cellGetRow(c)          (c >> 4)

void Maze_Init(void);

//Cell Maze_GetRelativeWalls
//void Maze_SetRealtiveWalls

void Maze_AddWall(CellIndex c, CompassRelative d);
void Maze_AddBorders(void);

void Maze_Enqueue(CellIndex c);
CellIndex Maze_Dequeue(void);

BOOL Maze_IsFlooded(void);
void Maze_BeginFlood(void);
void Maze_FloodStep(void);

void Maze_Print(void);

#endif

