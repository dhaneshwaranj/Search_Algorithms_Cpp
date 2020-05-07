#ifndef UTILITIES_HH
#define UTILITIES_HH

#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <stack>
#include <map>
#include <unordered_map>

typedef std::pair<int,int> pi;

// Custom Class to maintain the nodes in the Frontier (Open set)
class FrontierNode{
	private:
		// Variables for the node, its parent and what move led to this node
		pi node;
		pi parent;
		char move;
	public:
		FrontierNode(pi node,pi parent,char move);
		
		// Formatted print
		void print();
		
		// Get methods to access Private members
		pi getNode();
		pi getParent();
		char getMove();
};


// Declaring Functions
void printLegalMoves(std::vector<std::vector<char>>& maze, std::unordered_map<char,pi>& moves);
void printMaze(std::vector<std::vector<char>>& maze);
void printMoves(std::unordered_map<char,pi>& moves);
void printExplored(std::map<pi,std::pair<pi,char>>& explored);
void printPi(pi& pair_int);
void printPic(std::pair<pi,char>& pic);
void printFrontier(std::queue<FrontierNode>& frontier);
bool insideBounds(pi& node, std::pair<char,pi> move, std::vector<std::vector<char>>& maze);
std::unordered_map<char,pi> getChildren(pi& node,std::vector<std::vector<char>>& maze, std::unordered_map<char,pi>& moves);
bool isGoal(pi& node, std::vector<std::vector<char>>& maze);
bool isStart(pi& node, std::vector<std::vector<char>>& maze);

#endif // UTILITIES_HH