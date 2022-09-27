#pragma once
#include "cprocessing.h"

typedef struct Character
{
	CP_Vector position;
	CP_Vector movDirection;
	CP_Image sprite;
	int facing; // 0 or 1 (left or right)
	int state; // 0 or 1 (still or moving)
	float health;
} Character;

typedef struct SpriteSheet {
	int frames;//number of sprites
	int height;//image height
	int width;//image width
	int stepHeight;//sprite height
	int stepWidth;//sprite width
	int interval;
} SpriteSheet;