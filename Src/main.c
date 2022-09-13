#include <stdio.h>
#include <stdlib.h>
#include "cprocessing.h"
#include "../Inc/movement.h"
#include "../Inc/animation.h"
#include "../Inc/structs.h"

CP_Image omegalul;
CP_Image character;

CP_Vector enemy;
float speed;
int interation;

Character protag;

CP_Matrix scale;
CP_Matrix transform;
CP_Matrix rotate;
CP_Matrix translate;

void game_init(void)
{
	omegalul = CP_Image_Load("Assets/character/geyfeg.png");
	character = CP_Image_Load("Assets/character/run/run_1.png");

	//create main character at 0,0 with no direction facing the right.
	protag.position = CP_Vector_Zero();
	protag.movDirection = CP_Vector_Zero();
	protag.facing = 1;
	protag.state = 0;

	interation = 1;

	CP_BOOL cursor = FALSE;
	CP_System_ShowCursor(cursor);
	CP_System_SetFrameRate(60.0f);

	speed = 10 * CP_System_GetDt();

	CP_Settings_ImageWrapMode(CP_IMAGE_WRAP_CLAMP);
	enemy = CP_Vector_Set(CP_Random_RangeFloat(-960, 960), CP_Random_RangeFloat(-540, 540));

	CP_System_Fullscreen();
}

void game_update(void)
{
	if (CP_Input_KeyDown(KEY_Q)) {
		CP_Engine_Terminate();
	}

	protag.movDirection = getDirection(&protag);
	protag.state = isMoving(protag.movDirection);

	CP_Graphics_ClearBackground(CP_Color_Create(255, 255, 255, 255));

	//Transforming the matrix to the center

	//Set the scale of the canvas (zoom)
	scale = CP_Matrix_Scale(CP_Vector_Set(1, 1));
	//Set the offset of the canvas (0,0 is top left by default)
	translate = CP_Matrix_Translate(CP_Vector_Set(CP_System_GetDisplayWidth() / 2, CP_System_GetDisplayHeight() / 2));
	//Rotation of the matrix
	rotate = CP_Matrix_Rotate(0);
	//Multiply matrix by settings
	transform = CP_Matrix_Multiply(translate, CP_Matrix_Multiply(rotate, scale));

	CP_Settings_ApplyMatrix(transform);

	//End matrix transformation.

	CP_Image_Draw(omegalul, enemy.x, enemy.y, 25, 24, 255);

	CP_Settings_Fill(CP_Color_Create(0, 0, 0, 255));
	CP_Settings_TextSize(20.0f);

	char coords[50] = { 0 };
	sprintf_s(coords, _countof(coords), "%f, %f", protag.position.x, protag.position.y);
	CP_Font_DrawText(coords, 0, 0);

	protag.position = characterMovement(protag.position, protag.movDirection, speed, 10);

	//animate running animation
	interation = getFrameInteration(interation);
	character = animateRun(interation, protag.facing, protag.state);
	
	CP_Image_Draw(character, protag.position.x, protag.position.y, CP_Image_GetWidth(character), CP_Image_GetHeight(character), 255);

	enemy = enemyMovement(enemy, protag.position, speed, 5);

}

void game_exit(void)
{
	CP_Image_Free(&omegalul);
	CP_Image_Free(&character);
}

int main(void)
{
	CP_Engine_SetNextGameState(game_init, game_update, game_exit);
	CP_Engine_Run();
	return 0;
}
