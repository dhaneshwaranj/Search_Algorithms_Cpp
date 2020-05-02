#ifndef UTILITIES_CPP
#define UTILITIES_CPP

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
		FrontierNode(pi node,pi parent,char move):node(node), parent(parent), move(move){
		}
		
		// Formatted print
		void print(){
			std::cout<<"[("<<node.first<<","<<node.second<<"), "<<"("<<parent.first<<","<<parent.second<<"), "<<move<<"]"<<std::endl;
		}
		
		// Get methods to access Private members
		pi getNode(){
			return node;
		}
		
		pi getParent(){
			return parent;
		}
		
		char getMove(){
			return move;
		}
};


// Declaring Functions
void printMoves(std::unordered_map<char,pi>& moves);
void printMaze(std::vector<std::vector<char>>& maze);
std::unordered_map<char,pi> getChildren(pi& node,std::vector<std::vector<char>>& maze, std::unordered_map<char,pi>& moves);
bool insideBounds(pi& node, std::pair<char,pi> move, std::vector<std::vector<char>>& maze);
void printLegalMoves(std::vector<std::vector<char>>& maze, std::unordered_map<char,pi>& moves);
void printExplored(std::map<pi,std::pair<pi,char>>& explored);
void printPi(pi& pair_int);
void printPic(std::pair<pi,char>& pic);
void printFrontier(std::queue<FrontierNode>& frontier);
bool isGoal(pi& node, std::vector<std::vector<char>>& maze);
bool isStart(pi& node, std::vector<std::vector<char>>& maze);




// The first few functions named print are used to debug and view results
void printLegalMoves(std::vector<std::vector<char>>& maze, std::unordered_map<char,pi>& moves){
//	This function prints all the moves allowed at each node
	for(int i=0; i<maze.size(); i++){
		for(int j=0; j<maze[0].size(); j++){
			std::cout<<"Moves for "<<i<<" "<<j<<std::endl;
			pi node = std::make_pair(i,j);
			std::unordered_map<char,pi> children = getChildren(node,maze,moves);
			printMoves(children);
		}
	}
}

void printMaze(std::vector<std::vector<char>>& maze){
//	This function prints the maze
	std::string line = std::string(maze[0].size()*2+1,'-');
	for(auto row: maze){
		std::cout<<line<<std::endl;
		std::cout<<"|";
		for(auto col: row){
			std::cout<<col<<"|";
		}
		std::cout<<std::endl;
	}
}

void printMoves(std::unordered_map<char,pi>& moves){
//	This function prints out the moves passed in
	for(auto key_value: moves){
		std::cout<< key_value.first << " [" << key_value.second.first << "," << key_value.second.second << "]" <<std::endl;
	}
}

void printPi(pi& pair_int){
//	Print pair of ints
	std::cout<<"("<<pair_int.first<<","<<pair_int.second<<")";
}

void printPic(std::pair<pi,char>& pic){
//	Print pair of pair of ints and a char
	printPi(pic.first);
	std::cout<<", "<<pic.second;
}

void printExplored(std::map<pi,std::pair<pi,char>>& explored){
//	Print the Explored set
	for(auto x: explored){
		pi first = x.first;
		std::pair<pi,char> second = x.second;
		std::cout<<"{";
		printPi(first);
		std::cout<<" : ";
		printPic(second);
		std::cout<<"}"<<std::endl;
	}
}

void printFrontier(std::queue<FrontierNode>& frontier){
//	Print the Frontier 
	while(!frontier.empty()){
		frontier.front().print();
		frontier.pop();
	}
}

bool insideBounds(pi& node, std::pair<char,pi> move, std::vector<std::vector<char>>& maze){
//	Utility function to check if a node is within the boundary
//  after applying an action in a direction
	bool ret;
	int row = node.first+move.second.first;
	int col = node.second+move.second.second;
	ret = (row>=0&&row<maze.size() && col>=0&&col<maze[0].size());
	return ret;
}

std::unordered_map<char,pi> getChildren(pi& node, std::vector<std::vector<char>>& maze, std::unordered_map<char,pi>& moves){
//	Get the children of all the nodes from the 
//  current node
	std::unordered_map<char,pi> children;
	for(auto move: moves){
		if(insideBounds(node,move,maze)){
			int row = node.first + move.second.first;
			int col = node.second + move.second.second;
			if(maze[row][col]!='#'){
				children[move.first] = std::make_pair(row,col);
			}
		}
	}
	return children;
}

bool isGoal(pi& node, std::vector<std::vector<char>>& maze){
//	Check to see if the node is the goal node
	return maze[node.first][node.second]=='G';
}

bool isStart(pi& node, std::vector<std::vector<char>>& maze){
//	Check to see if the node is the start node
	return maze[node.first][node.second]=='S';
}


#endif // UTILITIES_CPP