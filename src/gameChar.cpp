#include "gameChar.h"
//dont forget to update position vector or map it to translation matrix 
gameChar::gameChar(void)
{
	init();
}

void gameChar::init(){
	velocity = glm::vec3(0.0f, 0.0f, 0.0f);
	state = STEADY;
	cur_angle = 270.0f; // looking north
	predecision = NULL;
	//pos = glm::vec3(3.0f, 0.0f, 0.0f);
	step = 0.01f;
	jump = 274;
}

void gameChar::goNorth(){
	rotate(NORTH);
	velocity.x = 0.0f;
	velocity.z = step;
}

void gameChar::goEast(){
	rotate(EAST);
	velocity.x = -step;
	velocity.z = 0.0f;
}

void gameChar::goSouth(){
	rotate(SOUTH);
	velocity.x = 0.0f;
	velocity.z = -step;
}

void gameChar::goWest(){
	rotate(WEST);
	velocity.x = step;
	velocity.z = 0.0f;
}

void gameChar::stop(){
	velocity.x = 0.0f;
	velocity.z = 0.0f;
}

void gameChar::update(){
	//if(velocity != glm::vec3(0.0f, 0.0f, 0.0f)){
		MMX = glm::translate(velocity) * MMX;
		//pos += velocity;
		pos.x += velocity.x;
		pos.z += velocity.z;
		//printf("jumped");
		//printf("pacman is at pos %f ,%f, %f\n",pos.x, pos.y, pos.z);
	//}
	if(jump <= 270){
		velocity.y = sinf((float) (jump) * (22.0f/7.0f) / 180.0f) * 0.04;
		jump+=4;
	}else{
		velocity.y = 0.0f;
	}
	

}

void gameChar::rotate(float target_angle){
	target_angle *= 90.0f;
	MMX = glm::translate(pos) * glm::rotate(glm::radians(cur_angle - target_angle) ,glm::vec3(0.0f,1.0f,0.0f)) * glm::translate(-pos) * MMX;
	cur_angle = target_angle;
}

gameChar::~gameChar(void)
{
}
