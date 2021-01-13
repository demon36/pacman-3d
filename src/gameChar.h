#pragma once
#include "Scene\Model3D.h"
#include "node.h"
#include <glm\glm.hpp>
#define STEADY 0
#define MOVING_ON_EDGE 1
#define MOVING_ON_NODE 2
#define NORTH 0
#define EAST 1
#define SOUTH 2
#define WEST 3
class gameChar : public Model3D
{
public:
	gameChar(void);
	void init();
	glm::mat4 MMX;
	glm::vec3 velocity;
	glm::vec3 pos;
	node* currentNode;
	node* nextNode;
	int state;
	int jump;
	float cur_angle;
	float step;
	int predecision;
	void goNorth();
	void goEast();
	void goSouth();
	void goWest();
	void stop();
	void update();

	void rotate(float);
	~gameChar(void);

	
};

