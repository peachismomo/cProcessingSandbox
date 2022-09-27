#include "cprocessing.h"
#include "structs.h"

/*
* @brief: calculates the movement of a position relative to the target. Imitates a chasing movement
* @param: CP_Vector position - The position of the object to move
*		  CP_Vector target - The position of the target object
*		  float speed - The number of units to move per frame
*		  float units - The length of each unit
* @return: CP_Vector newPosition - The new position of the object after movement calculation.
*/
CP_Vector enemyMovement(CP_Vector position, CP_Vector target, float speed) {

	//multiply speed by delta time to ensure speed is the same regardless of framerate
	float unitSpeed = speed * CP_System_GetDt();

	//Direction vector from position to the target.
	CP_Vector directionNorm = CP_Vector_Normalize(CP_Vector_Subtract(target, position));

	//Set the new position.
	CP_Vector newPosition = CP_Vector_Add(position, CP_Vector_Scale(directionNorm, unitSpeed));

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
* @return: CP_Vector newPosition - The new position of the object after movement calculation.
*/
CP_Vector characterMovement(CP_Vector position, CP_Vector direction, float speed) {
	float unitSpeed = speed * CP_System_GetDt();

	CP_Vector directionNorm = CP_Vector_Normalize(direction);

	CP_Vector newPosition = CP_Vector_Add(position, CP_Vector_Scale(directionNorm, unitSpeed));

	return newPosition;
}


/*
* @brief: Determines if the character is moving or not
* @param: CP_Vector movDirection - The CP_Vector of the object
* @return: int - 1 means the object is moving, 0 means the object is not moving 
*/
int isMoving(CP_Vector movDirection) {
	if (movDirection.x != 0 || movDirection.y != 0) {
		return 1;
	}
	else return 0;
}

/*
* @brief: Returns a BOOL value an object has collided with another object
* @param: CP_Vector character - Object 1
*		  CP_Vector enemy - Object 2
* @return: BOOL - Returns TRUE if the 2 objects collided and false if they did not collide.
*/
BOOL collided(CP_Vector character, CP_Vector enemy, float hitboxRadius) {
	BOOL collided = FALSE;
	float distance = CP_Vector_Distance(character, enemy);

	if (distance <= hitboxRadius) {
		collided = TRUE;
	}

	return collided;
}