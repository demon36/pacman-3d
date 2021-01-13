#include "node.h"


node::node(int ind, float x, float z){
	pos = glm::vec3(x,0.2f,z);
	index = ind;
	east = NULL;
	north = NULL;
	west = NULL;
	south = NULL;
}

node::~node(void)
{
}
