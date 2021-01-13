#pragma once
#include <glm/glm.hpp>
class node
{

public:
	node(int, float, float); //pos
	//void assignEdges(node*, node*, node*, node*); //indices of attached nodes in vector
	glm::vec3 pos;
	int index;
	node* north;
	node* east;
	node* south;
	node* west;
	~node(void);
};

