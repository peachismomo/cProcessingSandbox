#include <stdio.h>
#include <stdlib.h>
#include "cprocessing.h"
#include "movement.h"
#include "animation.h"
#include "structs.h"

float speed;
float hitboxRadius;
int interation;
int frame;

Character protag;
Character enemy;
CP_Image bg;

CP_Matrix scale;
CP_Matrix transform;
CP_Matrix rotate;
CP_Matrix translate;

void game_init(void)
{
	hitboxRadius = 10;
	bg = CP_Image_Load("Assets/background/bg.png");

	//create main character at 0,0 with no direction facing the right.
	protag.position = CP_Vector_Zero();
	protag.movDirection = CP_Vector_Zero();
	protag.facing = 1;
	protag.state = 0;

	enemy.position = CP_Vector_Set(CP_Random_RangeFloat(-480, 480), CP_Random_RangeFloat(-270, 270));
	enemy.movDirection = CP_Vector_Zero();
	enemy.facing = 1;
	enemy.state = 0;
	enemy.sprite = CP_Image_Load("Assets/sprites/enemy/idle/idle (1).png");

	interation = 1;

	CP_BOOL cursor = FALSE;
	CP_System_ShowCursor(cursor);
	CP_System_SetFrameRate(60.0f);

	speed = 100;
	frame = 0;

	CP_Settings_ImageMode(CP_POSITION_CORNER);
	CP_Settings_ImageWrapMode(CP_IMAGE_WRAP_CLAMP);

	CP_System_Fullscreen();
}

void game_update(void)
{
	if (CP_Input_KeyDown(KEY_Q)) {
		CP_Engine_Terminate();
	}
	CP_Font_DrawText("", 0, 0);
	protag.movDirection = getDirection(&protag);
	protag.state = isMoving(protag.movDirection);

	CP_Graphics_ClearBackground(CP_Color_Create(255, 255, 255, 255));
	//CP_Image_Draw(bg, 0, 0, CP_System_GetDisplayWidth(), CP_System_GetDisplayHeight(), 255);
	//Transforming the matrix to the center

	//Set the scale of the canvas (zoom)
	scale = CP_Matrix_Scale(CP_Vector_Set(2, 2));
	//Set the offset of the canvas (0,0 is top left by default)
	translate = CP_Matrix_Translate(CP_Vector_Set(CP_System_GetDisplayWidth() / 2, CP_System_GetDisplayHeight() / 2));
	//Rotation of the matrix
	rotate = CP_Matrix_Rotate(0);
	//Multiply matrix by settings
	transform = CP_Matrix_Multiply(translate, CP_Matrix_Multiply(rotate, scale));

	CP_Settings_ApplyMatrix(transform);

	//End matrix transformation.

	CP_Image_Draw(enemy.sprite, enemy.position.x, enemy.position.y, 25, 24, 255);

	//CP_Settings_Fill(CP_Color_Create(0, 0, 0, 255));
	//CP_Settings_TextSize(20.0f);

	//char coords[50] = { 0 };
	//sprintf_s(coords, _countof(coords), "%f, %f", protag.position.x, protag.position.y);
	//CP_Font_DrawText(coords, 0, 0);

	//Draw character sprites
	protag.position = characterMovement(protag.position, protag.movDirection, speed);
	enemy.position = enemyMovement(enemy.position, protag.position, 50);

	//animate running animation
	//interation = getFrameInteration(interation);
	//protag.sprite = animateRun(interation, protag.facing, protag.state);
	SpriteSheet sheet = getSpriteSheet(&protag);
	if (CP_System_GetFrameCount() % sheet.interval == 0) {
		if (frame == sheet.frames - 1) {
			frame = 0;
		}
		else frame++;
	}

	float u0 = sheet.stepWidth * frame;
	float u1 = u0 + sheet.stepWidth;
	CP_Image_DrawSubImage(protag.sprite, protag.position.x, protag.position.y, sheet.stepWidth, sheet.stepHeight, u0, 0, u1, sheet.stepHeight, 255);

	//draw character sprite
	//CP_Image_Draw(protag.sprite, protag.position.x, protag.position.y, CP_Image_GetWidth(protag.sprite), CP_Image_GetHeight(protag.sprite), 255);

	CP_Graphics_DrawLine(100, 100, 100, 200);

	//Check collision with enemy
	if (collided(protag.position, enemy.position, hitboxRadius)) {
		CP_Settings_Fill(CP_Color_Create(0, 0, 0, 255));
		CP_Settings_TextSize(20.0f);
		CP_Font_DrawText("Collision detected", 0, 0);
	}
}

void game_exit(void)
{
	CP_Image_Free(&enemy.sprite);
	CP_Image_Free(&protag.sprite);
}

int main(void)
{
	CP_Engine_SetNextGameState(game_init, game_update, game_exit);
	CP_Engine_Run();
	return 0;
}
