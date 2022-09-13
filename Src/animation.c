#include "cprocessing.h"

const char* runAniList[6] = {
	"Assets/character/run/run_1.png" ,
	"Assets/character/run/run_2.png" ,
	"Assets/character/run/run_3.png" ,
	"Assets/character/run/run_4.png" ,
	"Assets/character/run/run_5.png" ,
	"Assets/character/run/run_6.png" };

const char* runAniLeftList[6] = {
	"Assets/character/runLeft/run_1.png" ,
	"Assets/character/runLeft/run_2.png" ,
	"Assets/character/runLeft/run_3.png" ,
	"Assets/character/runLeft/run_4.png" ,
	"Assets/character/runLeft/run_5.png" ,
	"Assets/character/runLeft/run_6.png" };

const char* standAniList[3] = {
	"Assets/character/ready/ready_1.png",
	"Assets/character/ready/ready_2.png",
	"Assets/character/ready/ready_3.png"
};

const char* standAniLeftList[3] = {
	"Assets/character/readyLeft/ready_1.png",
	"Assets/character/readyLeft/ready_2.png",
	"Assets/character/readyLeft/ready_3.png"
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