#ifndef _STRUCT_TILE_H_
#define _STRUCT_TILE_H_

#include <stdio.h>

#include "tile.h"
#include "struct_color.h"

//Struct for tile
struct tile{
	struct color *color_direction[MAX_DIRECTION];
	 

}; 



#endif //_STRUCT_TILE_H_