#pragma once
#include "cprocessing.h"

typedef struct Character
{
	CP_Vector position;
	CP_Vector movDirection;
	int facing; // 0 or 1 (left or right)
	int state; // 0 or 1 (still or moving)
	CP_Image sprite;
	float health;
} Character;