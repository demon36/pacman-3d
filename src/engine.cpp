#include "engine.h"
engine::engine(void)
{
}

void engine::init(){
	lives = 3;
	intscore = 0;
	score = "SCORE: " + std::to_string(intscore);
	foodR = 0.1f;//radii
	pacmanR = 0.2f;
	initNodes();
	startNode = &nodes.at(0);
	initGameChars();
	initFood();
	printf("engine :node 0 %f,%f,%f", startNode->pos.x, startNode->pos.y, startNode->pos.z);
}

//PACMAN FUNCTIONS
void engine::pacmanUp(){
		if (PacmanisOnNode(pacman->pos) != NULL){
	
			if ((pacman->currentNode->north != NULL))
			{
				pacman->goNorth();
				pacman->nextNode = pacman->currentNode->north;
			}
			else
				pacmanStop();
		}
		else if (PacmanisOnNode(pacman->pos) == NULL){
			if (pacman->nextNode->north != NULL)
			{
				pacman->predecision = GLFW_KEY_UP;
			}
			if (pacman->nextNode == pacman->currentNode->south){
				pacman->goNorth();
				pacman->nextNode = pacman->currentNode;
				pacman->currentNode =pacman->nextNode->south;
				pacman->predecision = 0;
			}
	
		}
}
void engine::pacmanDown(){
	if (PacmanisOnNode(pacman->pos) != NULL){
				
				if ((pacman->currentNode->south != NULL))
				{
					pacman->goSouth();
					pacman->nextNode = pacman->currentNode->south;
				}
				else
					pacmanStop();
			}
			else if (PacmanisOnNode(pacman->pos) == NULL){
				if ((pacman->nextNode->south != NULL))
				{
					pacman->predecision = GLFW_KEY_DOWN;
				}
				if (pacman->nextNode == pacman->currentNode->north){
					pacman->goSouth();
					pacman->nextNode = pacman->currentNode;
					pacman->currentNode = pacman->nextNode->north;
					pacman->predecision = 0;
				}
		
			}
	
}
void engine::pacmanRight(){
	if (PacmanisOnNode(pacman->pos) != NULL){

		if ((pacman->currentNode->east != NULL))
		{
			pacman->nextNode = pacman->currentNode->east;
			pacman->goEast();
		}
		else
			pacmanStop();
	}
	else if (PacmanisOnNode(pacman->pos) == NULL){
		if ((pacman->nextNode->east != NULL))
		{
			pacman->predecision = GLFW_KEY_RIGHT;
		}
		if (pacman->nextNode == pacman->currentNode->west){
			pacman->goEast();
			pacman->nextNode = pacman->currentNode;
			pacman->currentNode = pacman->nextNode->west;
			pacman->predecision = 0;
		}

	}
}
void engine::pacmanLeft(){
	if (PacmanisOnNode(pacman->pos) != NULL){

		if ((pacman->currentNode->west != NULL))
		{
			pacman->nextNode = pacman->currentNode->west;
			pacman->goWest();
		}
		else
			pacmanStop();
	}
	else if (PacmanisOnNode(pacman->pos) == NULL){
		if ((pacman->nextNode->west != NULL))
		{
			pacman->predecision = GLFW_KEY_LEFT;
		}
		if (pacman->nextNode == pacman->currentNode->east){
			pacman->goWest();
			pacman->nextNode = pacman->currentNode;
			pacman->currentNode = pacman->nextNode->east;
			pacman->predecision = 0;
		}

	}
}

void engine::pacmanStop(){
	pacman->nextNode = pacman->currentNode;
	pacman->state = MOVING_ON_NODE;
	pacman->stop();
}

void engine::pacmanJump(){
	if(pacman->jump == 274)
		pacman->jump = 90;
}

node* engine::PacmanisOnNode(glm::vec3 pos){


	for (int i = 0; i < nodes.size(); i++){
		if ((abs(nodes[i].pos.x - pos.x)<E) && (abs(nodes[i].pos.z - pos.z)<E)){
			//printf("pacman  on node %f, %f \n", pos.x, pos.z);
			pacman->currentNode = &nodes[i];
			pacman->currentNode->index = i;
			pacman->pos = pacman->currentNode->pos;
			pacman->state = MOVING_ON_NODE;
			//PlaySound(TEXT("intro.wav"), NULL, SND_ALIAS | SND_APPLICATION);
			return pacman->currentNode;

		}
		
	}
	pacman->state = MOVING_ON_EDGE;
	return NULL;

}

node* engine::arrivedNode(node* next, glm::vec3 pos){
	if ((abs(next->pos.x - pos.x) < E) && (abs(next->pos.z - pos.z) < E))
		return next;
}

float engine::getXZDistance(glm::vec3 p1, glm::vec3 p2){
	return sqrtf( powf( p1.x - p2.x, 2.0f) + powf( p1.z - p2.z, 2.0f) );
}

void engine::initFood(){
	foodPosVector = std::vector<std::pair<bool,glm::vec3>>();
	//food radius is 0.1f
	foodR = 0.1f;//radii
	foodMmx = glm::scale(glm::vec3(foodR, foodR, foodR));

	food = std::unique_ptr<gameChar>(new gameChar());
	food->LoadFromFile("data/models/sphere/food.obj", true);
	food->Initialize();
	
foodPosVector.push_back(std::make_pair(true,glm::vec3(0.463244, 0.1f,0.461516)));
foodPosVector.push_back(std::make_pair(true,glm::vec3(0.744866, 0.1f,0.461516)));
foodPosVector.push_back(std::make_pair(true,glm::vec3(1.02649, 0.1f,0.461516)));
foodPosVector.push_back(std::make_pair(true,glm::vec3(1.30811, 0.1f,0.461516)));
foodPosVector.push_back(std::make_pair(true,glm::vec3(1.58973, 0.1f,0.461516)));
foodPosVector.push_back(std::make_pair(true,glm::vec3(1.87135, 0.1f,0.461516)));
foodPosVector.push_back(std::make_pair(true,glm::vec3(2.15298, 0.1f,0.461516)));
foodPosVector.push_back(std::make_pair(true,glm::vec3(2.4346, 0.1f,0.461516)));
foodPosVector.push_back(std::make_pair(true,glm::vec3(2.71622, 0.1f,0.461516)));
foodPosVector.push_back(std::make_pair(true,glm::vec3(2.99784, 0.1f,0.461516)));
foodPosVector.push_back(std::make_pair(true,glm::vec3(3.27946, 0.1f,0.461516)));
foodPosVector.push_back(std::make_pair(true,glm::vec3(3.56109, 0.1f,0.461516)));
foodPosVector.push_back(std::make_pair(true,glm::vec3(3.84271, 0.1f,0.461516)));
foodPosVector.push_back(std::make_pair(true,glm::vec3(4.68757, 0.1f,0.461516)));
foodPosVector.push_back(std::make_pair(true,glm::vec3(4.96919, 0.1f,0.461516)));
foodPosVector.push_back(std::make_pair(true,glm::vec3(5.25082, 0.1f,0.461516)));
foodPosVector.push_back(std::make_pair(true,glm::vec3(5.53244, 0.1f,0.461516)));
foodPosVector.push_back(std::make_pair(true,glm::vec3(5.81406, 0.1f,0.461516)));
foodPosVector.push_back(std::make_pair(true,glm::vec3(6.09568, 0.1f,0.461516)));
foodPosVector.push_back(std::make_pair(true,glm::vec3(6.3773, 0.1f,0.461516)));
foodPosVector.push_back(std::make_pair(true,glm::vec3(6.65893, 0.1f,0.461516)));
foodPosVector.push_back(std::make_pair(true,glm::vec3(6.94055, 0.1f,0.461516)));
foodPosVector.push_back(std::make_pair(true,glm::vec3(7.22217, 0.1f,0.461516)));
foodPosVector.push_back(std::make_pair(true,glm::vec3(7.50379, 0.1f,0.461516)));
foodPosVector.push_back(std::make_pair(true,glm::vec3(7.78541, 0.1f,0.461516)));
foodPosVector.push_back(std::make_pair(true,glm::vec3(8.06704, 0.1f,0.461516)));
foodPosVector.push_back(std::make_pair(true,glm::vec3(0.463244, 0.1f,0.742274)));
foodPosVector.push_back(std::make_pair(true,glm::vec3(1.87135, 0.1f,0.742274)));
foodPosVector.push_back(std::make_pair(true,glm::vec3(3.84271, 0.1f,0.742274)));
foodPosVector.push_back(std::make_pair(true,glm::vec3(4.68757, 0.1f,0.742274)));
foodPosVector.push_back(std::make_pair(true,glm::vec3(6.65893, 0.1f,0.742274)));
foodPosVector.push_back(std::make_pair(true,glm::vec3(8.06704, 0.1f,0.742274)));
foodPosVector.push_back(std::make_pair(true,glm::vec3(0.463244, 0.1f,1.02303)));
foodPosVector.push_back(std::make_pair(true,glm::vec3(1.87135, 0.1f,1.02303)));
foodPosVector.push_back(std::make_pair(true,glm::vec3(3.84271, 0.1f,1.02303)));
foodPosVector.push_back(std::make_pair(true,glm::vec3(4.68757, 0.1f,1.02303)));
foodPosVector.push_back(std::make_pair(true,glm::vec3(6.65893, 0.1f,1.02303)));
foodPosVector.push_back(std::make_pair(true,glm::vec3(8.06704, 0.1f,1.02303)));
foodPosVector.push_back(std::make_pair(true,glm::vec3(0.463244, 0.1f,1.30379)));
foodPosVector.push_back(std::make_pair(true,glm::vec3(1.87135, 0.1f,1.30379)));
foodPosVector.push_back(std::make_pair(true,glm::vec3(3.84271, 0.1f,1.30379)));
foodPosVector.push_back(std::make_pair(true,glm::vec3(4.68757, 0.1f,1.30379)));
foodPosVector.push_back(std::make_pair(true,glm::vec3(6.65893, 0.1f,1.30379)));
foodPosVector.push_back(std::make_pair(true,glm::vec3(8.06704, 0.1f,1.30379)));
foodPosVector.push_back(std::make_pair(true,glm::vec3(0.463244, 0.1f,1.58455)));
foodPosVector.push_back(std::make_pair(true,glm::vec3(0.744866, 0.1f,1.58455)));
foodPosVector.push_back(std::make_pair(true,glm::vec3(1.02649, 0.1f,1.58455)));
foodPosVector.push_back(std::make_pair(true,glm::vec3(1.30811, 0.1f,1.58455)));
foodPosVector.push_back(std::make_pair(true,glm::vec3(1.58973, 0.1f,1.58455)));
foodPosVector.push_back(std::make_pair(true,glm::vec3(1.87135, 0.1f,1.58455)));
foodPosVector.push_back(std::make_pair(true,glm::vec3(2.15298, 0.1f,1.58455)));
foodPosVector.push_back(std::make_pair(true,glm::vec3(2.4346, 0.1f,1.58455)));
foodPosVector.push_back(std::make_pair(true,glm::vec3(2.71622, 0.1f,1.58455)));
foodPosVector.push_back(std::make_pair(true,glm::vec3(2.99784, 0.1f,1.58455)));
foodPosVector.push_back(std::make_pair(true,glm::vec3(3.27946, 0.1f,1.58455)));
foodPosVector.push_back(std::make_pair(true,glm::vec3(3.56109, 0.1f,1.58455)));
foodPosVector.push_back(std::make_pair(true,glm::vec3(3.84271, 0.1f,1.58455)));
foodPosVector.push_back(std::make_pair(true,glm::vec3(4.12433, 0.1f,1.58455)));
foodPosVector.push_back(std::make_pair(true,glm::vec3(4.40595, 0.1f,1.58455)));
foodPosVector.push_back(std::make_pair(true,glm::vec3(4.68757, 0.1f,1.58455)));
foodPosVector.push_back(std::make_pair(true,glm::vec3(4.96919, 0.1f,1.58455)));
foodPosVector.push_back(std::make_pair(true,glm::vec3(5.25082, 0.1f,1.58455)));
foodPosVector.push_back(std::make_pair(true,glm::vec3(5.53244, 0.1f,1.58455)));
foodPosVector.push_back(std::make_pair(true,glm::vec3(5.81406, 0.1f,1.58455)));
foodPosVector.push_back(std::make_pair(true,glm::vec3(6.09568, 0.1f,1.58455)));
foodPosVector.push_back(std::make_pair(true,glm::vec3(6.3773, 0.1f,1.58455)));
foodPosVector.push_back(std::make_pair(true,glm::vec3(6.65893, 0.1f,1.58455)));
foodPosVector.push_back(std::make_pair(true,glm::vec3(6.94055, 0.1f,1.58455)));
foodPosVector.push_back(std::make_pair(true,glm::vec3(7.22217, 0.1f,1.58455)));
foodPosVector.push_back(std::make_pair(true,glm::vec3(7.50379, 0.1f,1.58455)));
foodPosVector.push_back(std::make_pair(true,glm::vec3(7.78541, 0.1f,1.58455)));
foodPosVector.push_back(std::make_pair(true,glm::vec3(8.06704, 0.1f,1.58455)));
foodPosVector.push_back(std::make_pair(true,glm::vec3(0.463244, 0.1f,1.86531)));
foodPosVector.push_back(std::make_pair(true,glm::vec3(1.87135, 0.1f,1.86531)));
foodPosVector.push_back(std::make_pair(true,glm::vec3(2.71622, 0.1f,1.86531)));
foodPosVector.push_back(std::make_pair(true,glm::vec3(5.81406, 0.1f,1.86531)));
foodPosVector.push_back(std::make_pair(true,glm::vec3(6.65893, 0.1f,1.86531)));
foodPosVector.push_back(std::make_pair(true,glm::vec3(8.06704, 0.1f,1.86531)));
foodPosVector.push_back(std::make_pair(true,glm::vec3(0.463244, 0.1f,2.14606)));
foodPosVector.push_back(std::make_pair(true,glm::vec3(1.87135, 0.1f,2.14606)));
foodPosVector.push_back(std::make_pair(true,glm::vec3(2.71622, 0.1f,2.14606)));
foodPosVector.push_back(std::make_pair(true,glm::vec3(5.81406, 0.1f,2.14606)));
foodPosVector.push_back(std::make_pair(true,glm::vec3(6.65893, 0.1f,2.14606)));
foodPosVector.push_back(std::make_pair(true,glm::vec3(8.06704, 0.1f,2.14606)));
foodPosVector.push_back(std::make_pair(true,glm::vec3(0.463244, 0.1f,2.42682)));
foodPosVector.push_back(std::make_pair(true,glm::vec3(0.744866, 0.1f,2.42682)));
foodPosVector.push_back(std::make_pair(true,glm::vec3(1.02649, 0.1f,2.42682)));
foodPosVector.push_back(std::make_pair(true,glm::vec3(1.30811, 0.1f,2.42682)));
foodPosVector.push_back(std::make_pair(true,glm::vec3(1.58973, 0.1f,2.42682)));
foodPosVector.push_back(std::make_pair(true,glm::vec3(1.87135, 0.1f,2.42682)));
foodPosVector.push_back(std::make_pair(true,glm::vec3(2.71622, 0.1f,2.42682)));
foodPosVector.push_back(std::make_pair(true,glm::vec3(2.99784, 0.1f,2.42682)));
foodPosVector.push_back(std::make_pair(true,glm::vec3(3.27946, 0.1f,2.42682)));
foodPosVector.push_back(std::make_pair(true,glm::vec3(3.56109, 0.1f,2.42682)));
foodPosVector.push_back(std::make_pair(true,glm::vec3(3.84271, 0.1f,2.42682)));
foodPosVector.push_back(std::make_pair(true,glm::vec3(4.68757, 0.1f,2.42682)));
foodPosVector.push_back(std::make_pair(true,glm::vec3(4.96919, 0.1f,2.42682)));
foodPosVector.push_back(std::make_pair(true,glm::vec3(5.25082, 0.1f,2.42682)));
foodPosVector.push_back(std::make_pair(true,glm::vec3(5.53244, 0.1f,2.42682)));
foodPosVector.push_back(std::make_pair(true,glm::vec3(5.81406, 0.1f,2.42682)));
foodPosVector.push_back(std::make_pair(true,glm::vec3(6.65893, 0.1f,2.42682)));
foodPosVector.push_back(std::make_pair(true,glm::vec3(6.94055, 0.1f,2.42682)));
foodPosVector.push_back(std::make_pair(true,glm::vec3(7.22217, 0.1f,2.42682)));
foodPosVector.push_back(std::make_pair(true,glm::vec3(7.50379, 0.1f,2.42682)));
foodPosVector.push_back(std::make_pair(true,glm::vec3(7.78541, 0.1f,2.42682)));
foodPosVector.push_back(std::make_pair(true,glm::vec3(8.06704, 0.1f,2.42682)));
foodPosVector.push_back(std::make_pair(true,glm::vec3(1.87135, 0.1f,2.70758)));
foodPosVector.push_back(std::make_pair(true,glm::vec3(6.65893, 0.1f,2.70758)));
foodPosVector.push_back(std::make_pair(true,glm::vec3(1.87135, 0.1f,2.98834)));
foodPosVector.push_back(std::make_pair(true,glm::vec3(6.65893, 0.1f,2.98834)));
foodPosVector.push_back(std::make_pair(true,glm::vec3(1.87135, 0.1f,3.2691)));
foodPosVector.push_back(std::make_pair(true,glm::vec3(6.65893, 0.1f,3.2691)));
foodPosVector.push_back(std::make_pair(true,glm::vec3(1.87135, 0.1f,3.54985)));
foodPosVector.push_back(std::make_pair(true,glm::vec3(6.65893, 0.1f,3.54985)));
foodPosVector.push_back(std::make_pair(true,glm::vec3(1.87135, 0.1f,3.83061)));
foodPosVector.push_back(std::make_pair(true,glm::vec3(6.65893, 0.1f,3.83061)));
foodPosVector.push_back(std::make_pair(true,glm::vec3(1.87135, 0.1f,4.11137)));
foodPosVector.push_back(std::make_pair(true,glm::vec3(6.65893, 0.1f,4.11137)));
foodPosVector.push_back(std::make_pair(true,glm::vec3(1.87135, 0.1f,4.39213)));
foodPosVector.push_back(std::make_pair(true,glm::vec3(6.65893, 0.1f,4.39213)));
foodPosVector.push_back(std::make_pair(true,glm::vec3(1.87135, 0.1f,4.67289)));
foodPosVector.push_back(std::make_pair(true,glm::vec3(6.65893, 0.1f,4.67289)));
foodPosVector.push_back(std::make_pair(true,glm::vec3(1.87135, 0.1f,4.95365)));
foodPosVector.push_back(std::make_pair(true,glm::vec3(6.65893, 0.1f,4.95365)));
foodPosVector.push_back(std::make_pair(true,glm::vec3(0.463244, 0.1f,5.2344)));
foodPosVector.push_back(std::make_pair(true,glm::vec3(0.744866, 0.1f,5.2344)));
foodPosVector.push_back(std::make_pair(true,glm::vec3(1.02649, 0.1f,5.2344)));
foodPosVector.push_back(std::make_pair(true,glm::vec3(1.30811, 0.1f,5.2344)));
foodPosVector.push_back(std::make_pair(true,glm::vec3(1.58973, 0.1f,5.2344)));
foodPosVector.push_back(std::make_pair(true,glm::vec3(1.87135, 0.1f,5.2344)));
foodPosVector.push_back(std::make_pair(true,glm::vec3(6.65893, 0.1f,5.2344)));
foodPosVector.push_back(std::make_pair(true,glm::vec3(6.94055, 0.1f,5.2344)));
foodPosVector.push_back(std::make_pair(true,glm::vec3(7.22217, 0.1f,5.2344)));
foodPosVector.push_back(std::make_pair(true,glm::vec3(7.50379, 0.1f,5.2344)));
foodPosVector.push_back(std::make_pair(true,glm::vec3(7.78541, 0.1f,5.2344)));
foodPosVector.push_back(std::make_pair(true,glm::vec3(8.06704, 0.1f,5.2344)));
foodPosVector.push_back(std::make_pair(true,glm::vec3(0.463244, 0.1f,5.51516)));
foodPosVector.push_back(std::make_pair(true,glm::vec3(1.87135, 0.1f,5.51516)));
foodPosVector.push_back(std::make_pair(true,glm::vec3(6.65893, 0.1f,5.51516)));
foodPosVector.push_back(std::make_pair(true,glm::vec3(8.06704, 0.1f,5.51516)));
foodPosVector.push_back(std::make_pair(true,glm::vec3(0.463244, 0.1f,5.79592)));
foodPosVector.push_back(std::make_pair(true,glm::vec3(1.87135, 0.1f,5.79592)));
foodPosVector.push_back(std::make_pair(true,glm::vec3(6.65893, 0.1f,5.79592)));
foodPosVector.push_back(std::make_pair(true,glm::vec3(8.06704, 0.1f,5.79592)));
foodPosVector.push_back(std::make_pair(true,glm::vec3(0.463244, 0.1f,6.07668)));
foodPosVector.push_back(std::make_pair(true,glm::vec3(0.744866, 0.1f,6.07668)));
foodPosVector.push_back(std::make_pair(true,glm::vec3(1.02649, 0.1f,6.07668)));
foodPosVector.push_back(std::make_pair(true,glm::vec3(1.87135, 0.1f,6.07668)));
foodPosVector.push_back(std::make_pair(true,glm::vec3(2.71622, 0.1f,6.07668)));
foodPosVector.push_back(std::make_pair(true,glm::vec3(2.99784, 0.1f,6.07668)));
foodPosVector.push_back(std::make_pair(true,glm::vec3(3.27946, 0.1f,6.07668)));
foodPosVector.push_back(std::make_pair(true,glm::vec3(3.56109, 0.1f,6.07668)));
foodPosVector.push_back(std::make_pair(true,glm::vec3(3.84271, 0.1f,6.07668)));
foodPosVector.push_back(std::make_pair(true,glm::vec3(4.68757, 0.1f,6.07668)));
foodPosVector.push_back(std::make_pair(true,glm::vec3(4.96919, 0.1f,6.07668)));
foodPosVector.push_back(std::make_pair(true,glm::vec3(5.25082, 0.1f,6.07668)));
foodPosVector.push_back(std::make_pair(true,glm::vec3(5.53244, 0.1f,6.07668)));
foodPosVector.push_back(std::make_pair(true,glm::vec3(5.81406, 0.1f,6.07668)));
foodPosVector.push_back(std::make_pair(true,glm::vec3(6.65893, 0.1f,6.07668)));
foodPosVector.push_back(std::make_pair(true,glm::vec3(7.50379, 0.1f,6.07668)));
foodPosVector.push_back(std::make_pair(true,glm::vec3(7.78541, 0.1f,6.07668)));
foodPosVector.push_back(std::make_pair(true,glm::vec3(8.06704, 0.1f,6.07668)));
foodPosVector.push_back(std::make_pair(true,glm::vec3(1.02649, 0.1f,6.35744)));
foodPosVector.push_back(std::make_pair(true,glm::vec3(1.87135, 0.1f,6.35744)));
foodPosVector.push_back(std::make_pair(true,glm::vec3(2.71622, 0.1f,6.35744)));
foodPosVector.push_back(std::make_pair(true,glm::vec3(5.81406, 0.1f,6.35744)));
foodPosVector.push_back(std::make_pair(true,glm::vec3(6.65893, 0.1f,6.35744)));
foodPosVector.push_back(std::make_pair(true,glm::vec3(7.50379, 0.1f,6.35744)));
foodPosVector.push_back(std::make_pair(true,glm::vec3(1.02649, 0.1f,6.63819)));
foodPosVector.push_back(std::make_pair(true,glm::vec3(1.87135, 0.1f,6.63819)));
foodPosVector.push_back(std::make_pair(true,glm::vec3(2.71622, 0.1f,6.63819)));
foodPosVector.push_back(std::make_pair(true,glm::vec3(5.81406, 0.1f,6.63819)));
foodPosVector.push_back(std::make_pair(true,glm::vec3(6.65893, 0.1f,6.63819)));
foodPosVector.push_back(std::make_pair(true,glm::vec3(7.50379, 0.1f,6.63819)));
foodPosVector.push_back(std::make_pair(true,glm::vec3(0.463244, 0.1f,6.91895)));
foodPosVector.push_back(std::make_pair(true,glm::vec3(0.744866, 0.1f,6.91895)));
foodPosVector.push_back(std::make_pair(true,glm::vec3(1.02649, 0.1f,6.91895)));
foodPosVector.push_back(std::make_pair(true,glm::vec3(1.30811, 0.1f,6.91895)));
foodPosVector.push_back(std::make_pair(true,glm::vec3(1.58973, 0.1f,6.91895)));
foodPosVector.push_back(std::make_pair(true,glm::vec3(1.87135, 0.1f,6.91895)));
foodPosVector.push_back(std::make_pair(true,glm::vec3(2.15298, 0.1f,6.91895)));
foodPosVector.push_back(std::make_pair(true,glm::vec3(2.4346, 0.1f,6.91895)));
foodPosVector.push_back(std::make_pair(true,glm::vec3(2.71622, 0.1f,6.91895)));
foodPosVector.push_back(std::make_pair(true,glm::vec3(2.99784, 0.1f,6.91895)));
foodPosVector.push_back(std::make_pair(true,glm::vec3(3.27946, 0.1f,6.91895)));
foodPosVector.push_back(std::make_pair(true,glm::vec3(3.56109, 0.1f,6.91895)));
foodPosVector.push_back(std::make_pair(true,glm::vec3(3.84271, 0.1f,6.91895)));
foodPosVector.push_back(std::make_pair(true,glm::vec3(4.68757, 0.1f,6.91895)));
foodPosVector.push_back(std::make_pair(true,glm::vec3(4.96919, 0.1f,6.91895)));
foodPosVector.push_back(std::make_pair(true,glm::vec3(5.25082, 0.1f,6.91895)));
foodPosVector.push_back(std::make_pair(true,glm::vec3(5.53244, 0.1f,6.91895)));
foodPosVector.push_back(std::make_pair(true,glm::vec3(5.81406, 0.1f,6.91895)));
foodPosVector.push_back(std::make_pair(true,glm::vec3(6.09568, 0.1f,6.91895)));
foodPosVector.push_back(std::make_pair(true,glm::vec3(6.3773, 0.1f,6.91895)));
foodPosVector.push_back(std::make_pair(true,glm::vec3(6.65893, 0.1f,6.91895)));
foodPosVector.push_back(std::make_pair(true,glm::vec3(6.94055, 0.1f,6.91895)));
foodPosVector.push_back(std::make_pair(true,glm::vec3(7.22217, 0.1f,6.91895)));
foodPosVector.push_back(std::make_pair(true,glm::vec3(7.50379, 0.1f,6.91895)));
foodPosVector.push_back(std::make_pair(true,glm::vec3(7.78541, 0.1f,6.91895)));
foodPosVector.push_back(std::make_pair(true,glm::vec3(8.06704, 0.1f,6.91895)));
foodPosVector.push_back(std::make_pair(true,glm::vec3(0.463244, 0.1f,7.19971)));
foodPosVector.push_back(std::make_pair(true,glm::vec3(1.87135, 0.1f,7.19971)));
foodPosVector.push_back(std::make_pair(true,glm::vec3(3.84271, 0.1f,7.19971)));
foodPosVector.push_back(std::make_pair(true,glm::vec3(4.68757, 0.1f,7.19971)));
foodPosVector.push_back(std::make_pair(true,glm::vec3(6.65893, 0.1f,7.19971)));
foodPosVector.push_back(std::make_pair(true,glm::vec3(8.06704, 0.1f,7.19971)));
foodPosVector.push_back(std::make_pair(true,glm::vec3(0.463244, 0.1f,7.48047)));
foodPosVector.push_back(std::make_pair(true,glm::vec3(1.87135, 0.1f,7.48047)));
foodPosVector.push_back(std::make_pair(true,glm::vec3(3.84271, 0.1f,7.48047)));
foodPosVector.push_back(std::make_pair(true,glm::vec3(4.68757, 0.1f,7.48047)));
foodPosVector.push_back(std::make_pair(true,glm::vec3(6.65893, 0.1f,7.48047)));
foodPosVector.push_back(std::make_pair(true,glm::vec3(8.06704, 0.1f,7.48047)));
foodPosVector.push_back(std::make_pair(true,glm::vec3(0.463244, 0.1f,7.76123)));
foodPosVector.push_back(std::make_pair(true,glm::vec3(1.87135, 0.1f,7.76123)));
foodPosVector.push_back(std::make_pair(true,glm::vec3(3.84271, 0.1f,7.76123)));
foodPosVector.push_back(std::make_pair(true,glm::vec3(4.68757, 0.1f,7.76123)));
foodPosVector.push_back(std::make_pair(true,glm::vec3(6.65893, 0.1f,7.76123)));
foodPosVector.push_back(std::make_pair(true,glm::vec3(8.06704, 0.1f,7.76123)));
foodPosVector.push_back(std::make_pair(true,glm::vec3(0.463244, 0.1f,8.04198)));
foodPosVector.push_back(std::make_pair(true,glm::vec3(0.744866, 0.1f,8.04198)));
foodPosVector.push_back(std::make_pair(true,glm::vec3(1.02649, 0.1f,8.04198)));
foodPosVector.push_back(std::make_pair(true,glm::vec3(1.30811, 0.1f,8.04198)));
foodPosVector.push_back(std::make_pair(true,glm::vec3(1.58973, 0.1f,8.04198)));
foodPosVector.push_back(std::make_pair(true,glm::vec3(1.87135, 0.1f,8.04198)));
foodPosVector.push_back(std::make_pair(true,glm::vec3(2.15298, 0.1f,8.04198)));
foodPosVector.push_back(std::make_pair(true,glm::vec3(2.4346, 0.1f,8.04198)));
foodPosVector.push_back(std::make_pair(true,glm::vec3(2.71622, 0.1f,8.04198)));
foodPosVector.push_back(std::make_pair(true,glm::vec3(2.99784, 0.1f,8.04198)));
foodPosVector.push_back(std::make_pair(true,glm::vec3(3.27946, 0.1f,8.04198)));
foodPosVector.push_back(std::make_pair(true,glm::vec3(3.56109, 0.1f,8.04198)));
foodPosVector.push_back(std::make_pair(true,glm::vec3(3.84271, 0.1f,8.04198)));
foodPosVector.push_back(std::make_pair(true,glm::vec3(4.12433, 0.1f,8.04198)));
foodPosVector.push_back(std::make_pair(true,glm::vec3(4.40595, 0.1f,8.04198)));
foodPosVector.push_back(std::make_pair(true,glm::vec3(4.68757, 0.1f,8.04198)));
foodPosVector.push_back(std::make_pair(true,glm::vec3(4.96919, 0.1f,8.04198)));
foodPosVector.push_back(std::make_pair(true,glm::vec3(5.25082, 0.1f,8.04198)));
foodPosVector.push_back(std::make_pair(true,glm::vec3(5.53244, 0.1f,8.04198)));
foodPosVector.push_back(std::make_pair(true,glm::vec3(5.81406, 0.1f,8.04198)));
foodPosVector.push_back(std::make_pair(true,glm::vec3(6.09568, 0.1f,8.04198)));
foodPosVector.push_back(std::make_pair(true,glm::vec3(6.3773, 0.1f,8.04198)));
foodPosVector.push_back(std::make_pair(true,glm::vec3(6.65893, 0.1f,8.04198)));
foodPosVector.push_back(std::make_pair(true,glm::vec3(6.94055, 0.1f,8.04198)));
foodPosVector.push_back(std::make_pair(true,glm::vec3(7.22217, 0.1f,8.04198)));
foodPosVector.push_back(std::make_pair(true,glm::vec3(7.50379, 0.1f,8.04198)));
foodPosVector.push_back(std::make_pair(true,glm::vec3(7.78541, 0.1f,8.04198)));
foodPosVector.push_back(std::make_pair(true,glm::vec3(8.06704, 0.1f,8.04198)));
}

void engine::checkGhostCollision(){

	for (int i = 0; i < 4; i++){
		if (getXZDistance(pacman->pos, ghosts[i]->pos) <  (0.35f * 0.8f) + pacmanR / 2.0){
			lives--;
			restartGame();
			PlaySound(TEXT("death.wav"), NULL, SND_SYNC);
		}
	}
	
	
}

void engine::restartGame(){

	auto temp_scale_mat = glm::scale(glm::vec3(0.35f, 0.35f, 0.35f));
	//pacman->Initialize();
	pacman->init();
	pacman->pos = startNode->pos;
	pacman->currentNode = startNode;
	pacman->currentNode->index = 0;
	pacman->state = MOVING_ON_NODE;
	pacmanR = 0.2f;
	pacman->MMX = glm::translate(startNode->pos) * 
		glm::scale(glm::vec3(pacmanR, pacmanR, pacmanR))*
		glm::rotate(glm::radians(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	pacman->stop();
	
	ghosts[0]->init();
	ghosts[0]->pos = nodes[64].pos;
	ghosts[0]->currentNode = &nodes[64];
	ghosts[0]->currentNode->index = 64;
	ghosts[0]->MMX = glm::translate(nodes[64].pos) * temp_scale_mat*glm::rotate(glm::radians(-180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	

	ghosts[1]->init();
	ghosts[1]->pos = nodes[22].pos;
	ghosts[1]->currentNode = &nodes[22];
	ghosts[1]->currentNode->index = 22;
	ghosts[1]->MMX = glm::translate(nodes[22].pos) * temp_scale_mat*glm::rotate(glm::radians(-180.0f), glm::vec3(0.0f, 1.0f, 0.0f));

	ghosts[2]->init();
	ghosts[2]->pos = nodes[49].pos;
	ghosts[2]->currentNode = &nodes[49];
	ghosts[2]->currentNode->index = 49;
	ghosts[2]->MMX = glm::translate(nodes[49].pos) * temp_scale_mat*glm::rotate(glm::radians(-180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	
	ghosts[3]->init();
	ghosts[3]->pos = nodes[8].pos;
	ghosts[3]->currentNode = &nodes[8];
	ghosts[3]->currentNode->index = 8;
	ghosts[3]->MMX = glm::translate(nodes[8].pos) * temp_scale_mat*glm::rotate(glm::radians(-180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
}

void engine::updateFood(){
	for (int i = 0; i < foodPosVector.size(); i++){
		float temp = getXZDistance(pacman->pos, foodPosVector[i].second);
		if (temp < foodR + pacmanR)
		{
			foodPosVector.erase(foodPosVector.begin() + i);
			PlaySound(TEXT("eating.wav"), NULL, SND_ASYNC | SND_NOSTOP);
			intscore++;
			score = "SCORE: " + std::to_string(intscore);
		}
	}

	
}

void engine::initGameChars(){
	auto temp_scale_mat = glm::scale(glm::vec3(0.35f, 0.35f, 0.35f));

	pacman = std::unique_ptr<gameChar>(new gameChar());
	pacman->LoadFromFile("data/models/sphere/sphere.obj", true);
	pacman->Initialize();
	pacman->pos = startNode->pos;
	pacman->currentNode = startNode;
	pacman->currentNode->index = 0;
	pacman->state = MOVING_ON_NODE;
	pacmanR = 0.2f;
	pacman->MMX = glm::translate(startNode->pos) * glm::scale(glm::vec3(pacmanR, pacmanR, pacmanR));
	
	ghosts[0] = std::unique_ptr<gameChar>(new gameChar());
	ghosts[0]->LoadFromFile("data/models/blinky/Pacman-Blinky.obj", true);
	ghosts[0]->Initialize();
	ghosts[0]->pos = nodes[64].pos;
	ghosts[0]->currentNode = &nodes[64];
	ghosts[0]->currentNode->index = 64;
	ghosts[0]->MMX = glm::translate(nodes[64].pos) * temp_scale_mat*glm::rotate(glm::radians(-180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	
	ghosts[1] = std::unique_ptr<gameChar>(new gameChar());
	ghosts[1]->LoadFromFile("data/models/pinky/Pacman-Blinky.obj", true);
	ghosts[1]->Initialize();
	ghosts[1]->pos = nodes[22].pos;
	ghosts[1]->currentNode = &nodes[22];
	ghosts[1]->currentNode->index = 22;
	ghosts[1]->MMX = glm::translate(nodes[22].pos) * temp_scale_mat*glm::rotate(glm::radians(-180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	
	ghosts[2] = std::unique_ptr<gameChar>(new gameChar());
	ghosts[2]->LoadFromFile("data/models/inky/Pacman-Blinky.obj", true);
	ghosts[2]->Initialize();
	ghosts[2]->pos = nodes[49].pos;
	ghosts[2]->currentNode = &nodes[49];
	ghosts[2]->currentNode->index = 49;
	ghosts[2]->MMX = glm::translate(nodes[49].pos) * temp_scale_mat*glm::rotate(glm::radians(-180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	

	ghosts[3] = std::unique_ptr<gameChar>(new gameChar());
	ghosts[3]->LoadFromFile("data/models/clyde/Pacman-Blinky.obj", true);
	ghosts[3]->Initialize();
	ghosts[3]->pos = nodes[8].pos;
	ghosts[3]->currentNode = &nodes[8];
	ghosts[3]->currentNode->index = 8;
	ghosts[3]->MMX = glm::translate(nodes[8].pos) * temp_scale_mat*glm::rotate(glm::radians(-180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	

}
//Checks if pacman can continue in the same direction 
bool engine::sameDirection(node* current){
	if ((pacman->velocity.z == -pacman->step) && (current->south != NULL)){
		pacman->nextNode = pacman->currentNode->south;
		return true;
	}
	else if ((pacman->velocity.z == pacman->step) && (current->north != NULL)){
		pacman->nextNode = pacman->currentNode->north;
		return true;
	}
	else if ((pacman->velocity.x == -pacman->step) && (current->east != NULL)){
		pacman->nextNode = pacman->currentNode->east;
		return true;
	}
	else if ((pacman->velocity.x == pacman->step) && (current->west != NULL)){
		pacman->nextNode = pacman->currentNode->west;
		return true;
	}
	else
		return false;
}
void engine::update(){
	if (lives > 0){
		pacman->update();
		int index = pacman->currentNode->index;
		node* current = pacman->currentNode;
		if (pacman->velocity != glm::vec3(0.0f, 0.0f, 0.0f)){
			if (PacmanisOnNode(pacman->pos) != NULL){
				if (pacman->predecision == GLFW_KEY_UP)
				{
					pacman->predecision = 0;
					pacmanUp();
				}
				else if (pacman->predecision == GLFW_KEY_DOWN)
				{
					pacman->predecision = 0;
					pacmanDown();

				}
				else if (pacman->predecision == GLFW_KEY_RIGHT)
				{
					pacman->predecision = 0;
					pacmanRight();
				}
				else if (pacman->predecision == GLFW_KEY_LEFT)
				{
					pacman->predecision = 0;
					pacmanLeft();
				}
				else if ((pacman->predecision == 0) && (sameDirection(pacman->currentNode) == true))
				{
					pacman->update();
				}
				else
					pacmanStop();

			}


		}
	}

	UpdateGhosts();
	UpdateRandomGhosts();
	updateFood();
	checkGhostCollision();
}



//GHOST FUNCTIONS
//Updates ghosts nextnode
void engine::UpdateGhosts()
{
	int i = 1;
	if (lives > 0){
		if (GhostisOnNode(i, ghosts[i]->pos) == true && PacmanCaught(i) == false)
		{
			if ((pacman->state == MOVING_ON_NODE &&ghosts[i]->currentNode->index == pacman->currentNode->index) || (pacman->state == MOVING_ON_EDGE &&ghosts[i]->currentNode->index == pacman->nextNode->index))
			{
				ghosts[i]->stop();
				return;
			}

			NextGhostDirection(i);

			if (ghosts[i]->predecision == 0)
			{
				ghosts[i]->nextNode = ghosts[i]->currentNode->north;
				ghosts[i]->goNorth();
			}
			else if (ghosts[i]->predecision == 1)
			{
				ghosts[i]->nextNode = ghosts[i]->currentNode->east;
				ghosts[i]->goEast();
			}
			else if (ghosts[i]->predecision == 2)
			{
				ghosts[i]->nextNode = ghosts[i]->currentNode->south;
				ghosts[i]->goSouth();
			}
			else if (ghosts[i]->predecision == 3)
			{
				ghosts[i]->nextNode = ghosts[i]->currentNode->west;
				ghosts[i]->goWest();
			}

		}

		ghosts[i]->update();

	}
}

void engine::UpdateRandomGhosts(){
	if (lives > 0){

		for (int i = 0; i < 4; i++)
		{
			if (i == 1)
				continue;
			if (GhostisOnNode(i, ghosts[i]->pos) == true && PacmanCaught(i) == false)
			{
				srand(time(NULL));
				int random = rand() % 4;
				bool found = false;

				if (random == 0){
					if (ghosts[i]->currentNode->north != NULL)
					{
						ghosts[i]->nextNode = ghosts[i]->currentNode->north;
						ghosts[i]->goNorth();
						found = true;
					}
					else
						random++;
				}
				if (found == false && random == 1){
					if (ghosts[i]->currentNode->east != NULL)
					{
						ghosts[i]->nextNode = ghosts[i]->currentNode->east;
						ghosts[i]->goEast();
						found = true;
					}
					else
						random++;
				}
				if (found == false && random == 2){
					if (ghosts[i]->currentNode->south != NULL)
					{
						ghosts[i]->nextNode = ghosts[i]->currentNode->south;
						ghosts[i]->goSouth();
						found = true;

					}
					else
						random++;
				}
				if (found == false && random == 3){
					if (ghosts[i]->currentNode->west != NULL)
					{
						ghosts[i]->nextNode = ghosts[i]->currentNode->west;
						ghosts[i]->goWest();
						found = true;
					}
					else
					{
						if (ghosts[i]->currentNode->north != NULL)
						{
							ghosts[i]->nextNode = ghosts[i]->currentNode->north;
							ghosts[i]->goNorth();
						}
						else if (ghosts[i]->currentNode->south != NULL)
						{
							ghosts[i]->nextNode = ghosts[i]->currentNode->south;
							ghosts[i]->goSouth();
						}
						else if (ghosts[i]->currentNode->east != NULL)
						{
							ghosts[i]->nextNode = ghosts[i]->currentNode->east;
							ghosts[i]->goEast();
						}
					}
				}
			}

			ghosts[i]->update();

		}
	}

}
//checks if ghost arrived on a node or not
bool engine::GhostisOnNode(int index, glm::vec3 pos){


	for (int i = 0; i < nodes.size(); i++){
		if ((abs(nodes[i].pos.x - pos.x)<E) && (abs(nodes[i].pos.z - pos.z)<E)){
			//printf("\nghost  on noddde %f, %f \n", pos.x, pos.z);
			ghosts[index]->currentNode = &nodes[i];
			ghosts[index]->currentNode->index = i;
			return true;
		}
	}

	return false;

}
//checks if pacman one of the 4 ghosts are on the same node
bool engine::PacmanCaught(int index){
	if ((abs(ghosts[index]->pos.x - pacman->pos.x) < E) && (abs(ghosts[index]->pos.z - pacman->pos.z) < E)){
		for (int i = 0; i < 4; i++){
			ghosts[i]->stop();

		}
		return true;
	}
	return false;

}
// explores possible paths and updates predirection for a ghost

void engine::NextGhostDirection(int ghostnum)
{
	bool PathFound, goalfound = false;
	int gn = 0, index;
	float fn,
	hn = heuristic(ghosts[ghostnum]->currentNode->index);
	fn = hn + gn;
	std::queue<state> openNodes, closedNodes, unsorted;

	state start, child, current, finall;
	start.Cost = fn;
	start.path.push_back(ghosts[ghostnum]->currentNode->index);
	openNodes.push(start);

	while (!openNodes.empty())
	{
		
		current = openNodes.front();
		gn = current.path.size();//How many movement

		if (nodes[current.path.back()].north != NULL)
		{
			PathFound = false;
			index = nodes[current.path.back()].north->index;
			for (int x = 0; x < current.path.size(); x++)
				if (index == current.path[x])
				{PathFound = true;break;}
				
				if (PathFound == false){
					child.path = current.path;
					child.path.push_back(index);
					hn = heuristic(index);
					fn = gn + hn;
					child.Cost = fn;
					openNodes.push(child);
					if (hn == 0.0){
						goalfound = true;
						closedNodes.push(child);
					}
				}
		}
		if (goalfound==false&&nodes[current.path.back()].west != NULL)
		{
			PathFound = false;
			index = nodes[current.path.back()].west->index;
			for (int x = 0; x < current.path.size(); x++)
			if (index == current.path[x])
			{
				PathFound = true; break;
			}

			if (PathFound == false){
				child.path = current.path;
				child.path.push_back(index);
				hn = heuristic(index);
				fn = gn + hn;
				child.Cost = fn;
				openNodes.push(child);
				if (hn == 0.0){
					goalfound = true;
					closedNodes.push(child);
				}
			}
		}
		if (goalfound==false&&nodes[current.path.back()].east != NULL)
		{
			PathFound = false;
			index = nodes[current.path.back()].east->index;
			for (int x = 0; x < current.path.size(); x++)
			if (index == current.path[x])
			{
				PathFound = true; break;
			}

			if (PathFound == false){
				
				child.path = current.path;
				child.path.push_back(index);
				hn = heuristic(index);
				fn = gn + hn;
				child.Cost = fn;
				openNodes.push(child);
				if (hn == 0.0){
					goalfound = true;
					closedNodes.push(child);
				}
			}
		}
		if (goalfound==false&&nodes[current.path.back()].south != NULL)
		{
			PathFound = false;
			index = nodes[current.path.back()].south->index;
			for (int x = 0; x < current.path.size(); x++)
			if (index == current.path[x])
			{
				PathFound = true; break;
			}

			if (PathFound == false)
			{
				child.path = current.path;
				child.path.push_back(index);
				hn = heuristic(index);
				fn = gn + hn;
				child.Cost = fn;
				openNodes.push(child);
				if (hn == 0.0){
					goalfound = true;
					closedNodes.push(child);
				}
			}
		}
		if (goalfound == true)
			break;
		closedNodes.push(openNodes.front());
		openNodes.pop();
		

		unsorted = Sort(openNodes);
		unsorted.swap(openNodes);
		
	}

	finall = closedNodes.back();

	
	if (ghosts[ghostnum]->currentNode->north != NULL && (finall.path[1] == ghosts[ghostnum]->currentNode->north->index))
		ghosts[ghostnum]->predecision = NORTH;
	else if (ghosts[ghostnum]->currentNode->east != NULL && (finall.path[1] == ghosts[ghostnum]->currentNode->east->index ))
		ghosts[ghostnum]->predecision = EAST;
	else if (ghosts[ghostnum]->currentNode->west != NULL && (finall.path[1] == ghosts[ghostnum]->currentNode->west->index))
		ghosts[ghostnum]->predecision = WEST;
	else if (ghosts[ghostnum]->currentNode->south != NULL && (finall.path[1] == ghosts[ghostnum]->currentNode->south->index))
		ghosts[ghostnum]->predecision = SOUTH;
}

//Calculates Cost
float engine::heuristic(int index)
{//manhatan distance
	float hcost;
	if (pacman->state == MOVING_ON_EDGE)
		hcost = abs(nodes[index].pos.x - pacman->nextNode->pos.x) + abs(nodes[index].pos.z - pacman->nextNode->pos.z);
	else if (pacman->state== MOVING_ON_NODE)
		hcost = abs(nodes[index].pos.x - pacman->currentNode->pos.x) + abs(nodes[index].pos.z - pacman->currentNode->pos.z);
	return hcost;

}
//Sorts openNodes
std::queue<state> engine::Sort(std::queue<state> list)
{
	state x, y;
	int n, m;
	n = list.size();
	m = n - 1;
	for (int i = 0; i < n; i++)
	{
		x = list.front();
		list.pop();
		for (int j = 0; j < m; j++)
		{
			y = list.front();
			list.pop();
			if (x.Cost < y.Cost)
			{
				list.push(x);
				x = y;
			}
			else
				list.push(y);
		}
		list.push(x);
	}
	return list;
}


//NODES FUNCTIONS
void engine::initNodes(){
	nodes = std::vector<node>();

	/*nodegen ng;
	ng.init(&nodes);
	ng.fillVector();
	ng.assignRels();*/

	nodes.push_back(node(0,0.43,0.45));
	nodes.push_back(node(1,1.86,0.45));
	nodes.push_back(node(2,1.86,1.57));
	nodes.push_back(node(3,1.86,2.44));
	nodes.push_back(node(4,1.86,4.12));
	nodes.push_back(node(5,1.86,5.31));
	nodes.push_back(node(6,1.86,6.95));
	nodes.push_back(node(7,1.86,8.04));
	nodes.push_back(node(8,0.43,8.04));
	nodes.push_back(node(9,0.43,6.95));
	nodes.push_back(node(10,0.96,6.95));
	nodes.push_back(node(11,0.96,6.09));
	nodes.push_back(node(12,0.43,6.09));
	nodes.push_back(node(13,0.43,5.31));
	nodes.push_back(node(14,0.43,1.57));
	nodes.push_back(node(15,0.43,2.44));
	nodes.push_back(node(16,2.72,1.57));
	nodes.push_back(node(17,3.82,1.57));
	nodes.push_back(node(18,4.67,1.57));
	nodes.push_back(node(19,5.79,1.57));
	nodes.push_back(node(20,6.64,1.57));
	nodes.push_back(node(21,8.05,1.57));
	nodes.push_back(node(22,8.05,0.45));
	nodes.push_back(node(23,6.64,0.45));
	nodes.push_back(node(24,4.67,0.45));
	nodes.push_back(node(25,3.82,0.45));
	nodes.push_back(node(26,2.72,2.44));
	nodes.push_back(node(27,3.82,2.44));
	nodes.push_back(node(28,3.82,3.24));
	nodes.push_back(node(29,2.72,3.24));
	nodes.push_back(node(30,2.72,4.12));
	nodes.push_back(node(31,2.72,5.31));
	nodes.push_back(node(32,3.82,5.31));
	nodes.push_back(node(33,4.67,5.31));
	nodes.push_back(node(34,5.79,5.31));
	nodes.push_back(node(35,5.79,4.12));
	nodes.push_back(node(36,5.79,3.24));
	nodes.push_back(node(37,4.67,3.24));
	nodes.push_back(node(38,4.67,2.44));
	nodes.push_back(node(39,5.79,2.44));
	nodes.push_back(node(40,6.64,2.44));
	nodes.push_back(node(41,8.05,2.44));
	nodes.push_back(node(42,6.64,4.12));
	nodes.push_back(node(43,6.64,5.31));
	nodes.push_back(node(44,8.05,5.31));
	nodes.push_back(node(45,8.05,6.09));
	nodes.push_back(node(46,7.44,6.09));
	nodes.push_back(node(47,7.44,6.95));
	nodes.push_back(node(48,8.05,6.95));
	nodes.push_back(node(49,8.05,8.04));
	nodes.push_back(node(50,6.64,8.04));
	nodes.push_back(node(51,6.64,6.95));
	nodes.push_back(node(52,5.79,6.95));
	nodes.push_back(node(53,5.79,6.09));
	nodes.push_back(node(54,4.67,6.09));
	nodes.push_back(node(55,3.82,6.09));
	nodes.push_back(node(56,2.72,6.09));
	nodes.push_back(node(57,2.72,6.95));
	nodes.push_back(node(58,3.82,6.95));
	nodes.push_back(node(59,3.82,8.04));
	nodes.push_back(node(60,4.67,8.04));
	nodes.push_back(node(61,4.67,6.95));

	/*nodes.push_back(node(62,8.05,4.12));
	nodes.push_back(node(63,0.43,4.12));*/

	nodes.push_back(node(62,4.21,3.24));
	nodes.push_back(node(63,4.21,4.12));
	nodes.push_back(node(64,3.47,4.12));
	nodes.push_back(node(65,5.05,4.12));

	rels.push_back(std::make_pair(0,1));
	rels.push_back(std::make_pair(1,2));
	rels.push_back(std::make_pair(2,3));
	rels.push_back(std::make_pair(3,4));
	rels.push_back(std::make_pair(4,5));
	rels.push_back(std::make_pair(5,6));
	rels.push_back(std::make_pair(6,7));
	rels.push_back(std::make_pair(7,8));
	rels.push_back(std::make_pair(8,9));
	rels.push_back(std::make_pair(9,10));
	rels.push_back(std::make_pair(10,11));
	rels.push_back(std::make_pair(11,12));
	rels.push_back(std::make_pair(12,13));
	rels.push_back(std::make_pair(13,5));
	rels.push_back(std::make_pair(6,10));
	rels.push_back(std::make_pair(0,14));
	rels.push_back(std::make_pair(14,2));
	rels.push_back(std::make_pair(14,15));
	rels.push_back(std::make_pair(15,3));
	rels.push_back(std::make_pair(2,16));
	rels.push_back(std::make_pair(16,17));
	rels.push_back(std::make_pair(17,18));
	rels.push_back(std::make_pair(18,19));
	rels.push_back(std::make_pair(19,20));
	rels.push_back(std::make_pair(20,21));
	rels.push_back(std::make_pair(21,22));
	rels.push_back(std::make_pair(22,23));
	rels.push_back(std::make_pair(23,20));
	rels.push_back(std::make_pair(23,24));
	rels.push_back(std::make_pair(24,18));
	rels.push_back(std::make_pair(17,25));
	rels.push_back(std::make_pair(25,1));
	rels.push_back(std::make_pair(16,26));
	rels.push_back(std::make_pair(26,27));
	rels.push_back(std::make_pair(27,28));
	rels.push_back(std::make_pair(28,29));
	rels.push_back(std::make_pair(29,30));
	rels.push_back(std::make_pair(30,4));
	rels.push_back(std::make_pair(30,31));
	rels.push_back(std::make_pair(31,32));
	rels.push_back(std::make_pair(32,33));
	rels.push_back(std::make_pair(33,34));
	rels.push_back(std::make_pair(34,35));
	rels.push_back(std::make_pair(35,36));
	rels.push_back(std::make_pair(36,37));
	rels.push_back(std::make_pair(37,28));
	rels.push_back(std::make_pair(37,38));
	rels.push_back(std::make_pair(38,39));
	rels.push_back(std::make_pair(39,19));
	rels.push_back(std::make_pair(20,40));
	rels.push_back(std::make_pair(40,41));
	rels.push_back(std::make_pair(41,21));
	rels.push_back(std::make_pair(40,42));
	rels.push_back(std::make_pair(42,35));
	rels.push_back(std::make_pair(42,43));
	rels.push_back(std::make_pair(43,44));
	rels.push_back(std::make_pair(44,45));
	rels.push_back(std::make_pair(45,46));
	rels.push_back(std::make_pair(46,47));
	rels.push_back(std::make_pair(47,48));
	rels.push_back(std::make_pair(48,49));
	rels.push_back(std::make_pair(49,50));
	rels.push_back(std::make_pair(50,51));
	rels.push_back(std::make_pair(51,47));
	rels.push_back(std::make_pair(51,43));
	rels.push_back(std::make_pair(51,52));
	rels.push_back(std::make_pair(52,53));
	rels.push_back(std::make_pair(53,54));
	rels.push_back(std::make_pair(54,33));
	rels.push_back(std::make_pair(32,55));
	rels.push_back(std::make_pair(55,56));
	rels.push_back(std::make_pair(56,57));
	rels.push_back(std::make_pair(57,6));
	rels.push_back(std::make_pair(57,58));
	rels.push_back(std::make_pair(58,59));
	rels.push_back(std::make_pair(59,7));
	rels.push_back(std::make_pair(50,60));
	rels.push_back(std::make_pair(60,61));
	rels.push_back(std::make_pair(61,52));
	rels.push_back(std::make_pair(60,59));

	/*rels.push_back(std::make_pair(42,62));
	rels.push_back(std::make_pair(4,63));*/

	rels.push_back(std::make_pair(62,28));
	rels.push_back(std::make_pair(62,37));

	rels.push_back(std::make_pair(62,63));
	rels.push_back(std::make_pair(63,64));
	rels.push_back(std::make_pair(63,65));

	for(int j = 0; j < rels.size() ; j++){
		attachNodes(rels[j].first, rels[j].second);
	}

	displayNodes();


}

void engine::attachNodes(int first, int second){
	node* n =& nodes[first];
	node* m =& nodes[second];

	if(abs( n->pos.x - m->pos.x ) <= E){ //same x axis either - either north or south
		if(n->pos.z > m->pos.z){
			n->south = m;
			m->north = n;
		}else{
			m->south = n;
			n->north = m;
		}
	}else if(abs (n->pos.z - m->pos.z) <=E){ //same z axis - either east or west
		if(n->pos.x > m->pos.x){
			n->east = m;
			m->west = n;
		}else{
			m->east = n;
			n->west = m;
		}
	}
}
void engine::displayNodes(){
	for(int i = 0; i < nodes.size() ; i++){
		printf("node %i : \n",i);
		if(nodes[i].east != NULL)
			printf("\tEast is %i : \n",nodes[i].east->index);
		if(nodes[i].north != NULL)
			printf("\tnorth is %i : \n",nodes[i].north->index);
		if(nodes[i].west != NULL)
			printf("\twest is %i : \n",nodes[i].west->index);
		if(nodes[i].south != NULL)
			printf("\tsouth is %i : \n",nodes[i].south->index);
	
	}
}


engine::~engine(void)
{
}
