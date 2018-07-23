#include "../Include/Monster.h"

Monster::Monster()
{
	HP = 30;
	ATK = 3;
	nearATK = 3;
	//¹¥»÷ÆµÂÊÒªµ÷
	atack_frame = seconds(1.f / 1.f);
	nearatack_frame = seconds(1.f / 1.f);
	timeSinceLastUpdate = tslu = Time::Zero;
	jump_speed = 500;
	speed = 40;
	drop_speed = 1000;
	foot_position = 454;

	isMovingLeft = false;
	isMovingRight = false;
	isJumping = false;
	face_to_right = true;
	standing = true;
	canAtack = true;

	atacking = false;
	nearatacking = false;
}