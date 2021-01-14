#pragma once
#include "gameChar.h"
#include "node.h"
#include <vector>
#include <queue>
#include <utility>
#include <memory>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <time.h>
#ifdef WIN32

#include <Windows.h>
#include <MMSystem.h>
//# pragma comment(lib,"winmm.lib")

#endif

#define E 0.001
struct state{
	std::vector<int> path;
	float Cost;
};
class engine
{
private:
	
	std::vector<std::pair<int,int>> rels;	//relations table (contains indices)
	void attachNodes(int,int); // takes two nodes' indices as parameters and figures out relational position then attach nodes
	
public:
	std::unique_ptr<gameChar> pacman;
	std::unique_ptr<gameChar> ghosts[4];
	std::unique_ptr<Model3D> food;
	//pair first : visible, second position
	std::vector<std::pair<bool,glm::vec3>> foodPosVector;
	glm::mat4 foodMmx;
	float foodR;//radii
	float pacmanR;
	std::string score;
	int intscore;


	int lives;


	float getXZDistance(glm::vec3,glm::vec3);

	std::vector<node> nodes;
	node* startNode;
	void init(); // initialize ghosts with appropriate positions
	void initGameChars();
	void initNodes();
	void initFood();
	void restartGame();
	void update();
	void updateFood();
	void checkGhostCollision();
	void displayNodes();

	node* PacmanisOnNode(glm::vec3); 
	bool PacmanCaught(int);
	bool GhostisOnNode(int,glm::vec3);
	node* arrivedNode(node*, glm::vec3);

	void pacmanUp();
	void pacmanDown();
	void pacmanRight();
	void pacmanLeft();
	void pacmanStop();
	void pacmanJump();
	bool sameDirection(node*);

	//Astar Search Ghosts
	void UpdateGhosts();
	void UpdateRandomGhosts();
	std::queue<state> Sort(std::queue<state>);
	void NextGhostDirection(int);
	float heuristic(int);
	
	engine(void);
	~engine(void);
};

