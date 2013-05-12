#ifndef MAZE_H
#define MAZE_H

#include <m8c.h>        // part specific constants and macros
#include "PSoCAPI.h"    // PSoC API definitions for all User Modules
#include "PSoCGPIOINT.h"
#include "MicromouseModules.h"

typedef unsigned char CellFlags;  // Represents a cell and it's associated flags
typedef unsigned char CellIndex;
typedef unsigned char Direction;

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
#define WALL_WEST  0x40
#define WALL_SOUTH 0x10
#define WALL_EAST  0x04
#define WALL_NORTH 0x01

#define WALL_MASK  0x55  // A mask that allows only WALL flags

#define MOUSE_LEFT   0x40
#define MOUSE_BEHIND 0x10
#define MOUSE_RIGHT  0x04
#define MOUSE_FRONT  0x01

#define CELL_IN_QUEUE 0x02

#define cellWallExists(c, d)   (mazeFlags[c] &  d)
#define cellSetFlags(c, f)     (mazeFlags[c] |= f)

#define cellIsInQueue(c)       (mazeFlags[c] & CELL_IN_QUEUE)

#define cellGetColumn(c)       (c & 0x0F)
#define cellGetRow(c)          (c >> 4)

void Maze_Init(void);

//Cell Maze_GetRelativeWalls
//void Maze_SetRealtiveWalls

void Maze_AddWall(CellIndex c, Direction d);
void Maze_AddBorders(void);

void Maze_Enqueue(CellIndex c);
CellIndex Maze_Dequeue(void);

#endif
