#pragma once
#include "cprocessing.h"
#include "../Inc/structs.h"

CP_Vector enemyMovement(CP_Vector position, CP_Vector target, float speed, float units);

CP_Vector getDirection(Character* character);

CP_Vector characterMovement(CP_Vector position, CP_Vector direction, float speed, float units);

int isMoving(CP_Vector movDirection);