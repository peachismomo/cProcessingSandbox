#include "cprocessing.h"
#include "structs.h"

const char* runAniList[6] = {
	"Assets/sprites/mc/run/run_1.png" ,
	"Assets/sprites/mc/run/run_2.png" ,
	"Assets/sprites/mc/run/run_3.png" ,
	"Assets/sprites/mc/run/run_4.png" ,
	"Assets/sprites/mc/run/run_5.png" ,
	"Assets/sprites/mc/run/run_6.png" };

const char* runAniLeftList[6] = {
	"Assets/sprites/mc/runLeft/run_1.png" ,
	"Assets/sprites/mc/runLeft/run_2.png" ,
	"Assets/sprites/mc/runLeft/run_3.png" ,
	"Assets/sprites/mc/runLeft/run_4.png" ,
	"Assets/sprites/mc/runLeft/run_5.png" ,
	"Assets/sprites/mc/runLeft/run_6.png" };

const char* standAniList[3] = {
	"Assets/sprites/mc/ready/ready_1.png",
	"Assets/sprites/mc/ready/ready_2.png",
	"Assets/sprites/mc/ready/ready_3.png"
};

const char* standAniLeftList[3] = {
	"Assets/sprites/mc/readyLeft/ready_1.png",
	"Assets/sprites/mc/readyLeft/ready_2.png",
	"Assets/sprites/mc/readyLeft/ready_3.png"
};

CP_Image animateRun(int interation, int facing, int state) {
	CP_Image aniInteration = NULL;
	BOOL isMoving = (state > 0);
	if (facing > 0) {
		if (isMoving) {
			aniInteration = CP_Image_Load(runAniList[interation - 1]);
		}
		else {
			if (interation > 3) {
				interation -= 3;
			}
			aniInteration = CP_Image_Load(standAniList[interation - 1]);
		}
	}
	else {
		if (isMoving) {
			aniInteration = CP_Image_Load(runAniLeftList[interation - 1]);
		}
		else {
			if (interation > 3) {
				interation -= 3;
			}
			aniInteration = CP_Image_Load(standAniLeftList[interation - 1]);
		}
	}
	return aniInteration;
}

int getFrameInteration(int interation) {
	if (CP_System_GetFrameCount() % 8 == 0) {
		if (interation < 6) {
			interation++;
		}
		else {
			interation = 1;
		}
	}
	return interation;
}

int frameToSprite(int interation, int noSprites) {
	if (CP_System_GetFrameCount() % 8 == 0) {
		if (interation < noSprites) {
			interation++;
		}
		else interation = 1;
	}

	return interation;
}

SpriteSheet getSpriteSheet(Character* character) {
	SpriteSheet sheet;
	switch (character->state) {
		case 1:
			character->sprite = CP_Image_Load("Assets/sprites/walk.png");
			sheet.frames = 13;
			sheet.stepWidth = CP_Image_GetWidth(character->sprite) / 13;
			sheet.interval = 4;
			break;
		case 2:
			character->sprite = CP_Image_Load("Assets/sprites/hit.png");
			sheet.frames = 8;
			sheet.stepWidth = CP_Image_GetWidth(character->sprite) / 8;
			sheet.interval = 3;
			break;
		default:
			character->sprite = CP_Image_Load("Assets/sprites/idle.png");
			sheet.frames = 11;
			sheet.stepWidth = CP_Image_GetWidth(character->sprite) / 11;
			sheet.interval = 5;
			break;
	}
	sheet.height = CP_Image_GetHeight(character->sprite);
	sheet.width = CP_Image_GetWidth(character->sprite);
	sheet.stepHeight = CP_Image_GetHeight(character->sprite);

	return sheet;
}