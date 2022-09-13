#include "cprocessing.h"
#include "../Inc/structs.h"

/*
* @brief: calculates the movement of a position relative to the target. Imitates a chasing movement
* @param: CP_Vector position - The position of the object to move
*		  CP_Vector target - The position of the target object
*		  float speed - The number of units to move per frame
*		  float units - The length of each unit
* @return: CP_Vector newPosition - The new position of the object after movement calculation.
*/
CP_Vector enemyMovement(CP_Vector position, CP_Vector target, float speed, float units) {

	//Number of units to move in the time elasped between the alst frame and the current frame.
	float unitSpeed = speed * CP_System_GetDt();

	//Direction vector from position to the target.
	CP_Vector directionNorm = CP_Vector_Normalize(CP_Vector_Subtract(target, position));

	//Scale the direction by the length of each unit.
	directionNorm = CP_Vector_Scale(directionNorm, units);

	//Set the new position.
	CP_Vector newPosition = CP_Vector_Add(position, CP_Vector_Scale(directionNorm, speed));

	return newPosition;
}

/*
* @brief: Calculates the direction vector based on the keypress of the user (WASD), by adding the direction vectors of up down
* left and right.
* @param: No inputs required.
* @return: CP_Vector direction - The direction vector based on the keypress.
*/
CP_Vector getDirection(Character* character) {
	float dirX = 0;
	float dirY = 0;

	if (CP_Input_KeyDown(KEY_W)) {
		dirY += -1;
	}

	if (CP_Input_KeyDown(KEY_A)) {
		dirX += -1;
		character->facing = 0;
	}

	if (CP_Input_KeyDown(KEY_S)) {
		dirY += 1;
	}

	if (CP_Input_KeyDown(KEY_D)) {
		dirX += 1;
		character->facing = 1;
	}

	CP_Vector direction = CP_Vector_Set(dirX, dirY);

	return direction;
}

/*
* @brief: Moves a position based on a direction vector at a specific speed.
* @param: CP_Vector position - The position of the character to move
*		  CP_Vector direction - The vector direction
*		  float speed - The number of units to move per frame
*		  float units - The length of each unit
* @return: CP_Vector newPosition - The new position of the object after movement calculation.
*/
CP_Vector characterMovement(CP_Vector position, CP_Vector direction, float speed, float units) {
	float unitSpeed = speed * CP_System_GetDt();

	CP_Vector directionNorm = CP_Vector_Normalize(direction);

	directionNorm = CP_Vector_Scale(directionNorm, units);

	CP_Vector newPosition = CP_Vector_Add(position, CP_Vector_Scale(directionNorm, speed));

	return newPosition;
}


int isMoving(CP_Vector movDirection) {
	if (movDirection.x != 0 || movDirection.y != 0) {
		return 1;
	}
	else return 0;
}