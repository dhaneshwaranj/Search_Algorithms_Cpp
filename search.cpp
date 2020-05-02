// This program is to find a path between a start and a
// goal in a maze with obstacles. This program currently
// just implements the BFS search, more to come.

#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <stack>
#include <map>
#include <unordered_map>

using namespace std;

typedef pair<int,int> pi;

// Global Variables

// Define the maze
vector<vector<char>> maze= {{'G', '#', ' '},
							{' ', ' ', ' '},
							{' ', '#', ' '},
							{'#', 'S', ' '}};
							
// Define the start and Stop nodes								
pi start = make_pair(3,1);
pi goal = make_pair(0,0);

// Define the moves allowed 
unordered_map<char,pi> moves = {{'L',{0,-1}},
								{'R',{0,1}},
								{'U',{-1,0}},
								{'D',{1,0}}};


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
			cout<<"[("<<node.first<<","<<node.second<<"), "<<"("<<parent.first<<","<<parent.second<<"), "<<move<<"]"<<endl;
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
void printMoves(unordered_map<char,pi>& moves);
void printMaze(vector<vector<char>>& maze);
unordered_map<char,pi> getChildren(pi& node);
bool insideBounds(pi node, pair<char,pi> direction);
void printLegalMoves();
void printExplored(map<pi,pair<pi,char>>& explored);
void printPi(pi& pair_int);
void printPic(pair<pi,char>& pic);
void printFrontier(queue<FrontierNode> frontier);
bool isGoal(pi node);
bool isStart(pi node);
string bfs_search(vector<vector<char>>& maze, pi start, pi goal);

int main(int argc, char** argv) {
	cout<<"Maze"<<endl;
	printMaze(maze);
//	printMoves(moves);
//	printLegalMoves();
	bfs_search(maze,start,goal);
	
	return 0;
}

// The first few functions named print are used to debug and view results
void printLegalMoves(){
//	This function prints all the moves allowed at each node
	for(int i=0; i<maze.size(); i++){
		for(int j=0; j<maze[0].size(); j++){
			cout<<"Moves for "<<i<<" "<<j<<endl;
			pi node = make_pair(i,j);
			unordered_map<char,pi> children = getChildren(node);
			printMoves(children);
		}
	}
}

void printMaze(vector<vector<char>>& maze){
//	This function prints the maze
	for(auto row: maze){
		for(auto col: row){
			cout<<col;
		}
		cout<<endl;
	}
}

void printMoves(unordered_map<char,pi>& moves){
//	This function prints out the moves passed in
	for(auto key_value: moves){
		cout<< key_value.first << " [" << key_value.second.first << "," << key_value.second.second << "]" <<endl;
	}
}

void printPi(pi& pair_int){
//	Print pair of ints
	cout<<"("<<pair_int.first<<","<<pair_int.second<<")";
}

void printPic(pair<pi,char>& pic){
//	Print pair of pair of ints and a char
	printPi(pic.first);
	cout<<", "<<pic.second;
}

void printExplored(map<pi,pair<pi,char>>& explored){
//	Print the Explored set
	for(auto x: explored){
		pi first = x.first;
		pair<pi,char> second = x.second;
		cout<<"{";
		printPi(first);
		cout<<" : ";
		printPic(second);
		cout<<"}"<<endl;
	}
}

void printFrontier(queue<FrontierNode> frontier){
//	Print the Frontier 
	while(!frontier.empty()){
		frontier.front().print();
		frontier.pop();
	}
}

bool insideBounds(pi node, pair<char,pi> direction){
//	Utility function to check if a node is within the boundary
//  after applying an action in a direction
	bool ret;
	int row = node.first+direction.second.first;
	int col = node.second+direction.second.second;
	ret = (row>=0&&row<maze.size() && col>=0&&col<maze[0].size());
	return ret;
}

unordered_map<char,pi> getChildren(pi& node){
//	Get the children of all the nodes from the 
//  current node
	unordered_map<char,pi> children;
	for(auto x: moves){
		if(insideBounds(node,x)){
			int row = node.first + x.second.first;
			int col = node.second + x.second.second;
			if(maze[row][col]!='#'){
				children[x.first] = make_pair(row,col);
			}
		}
	}
	return children;
}

bool isGoal(pi node){
//	Check to see if the node is the goal node
	return maze[node.first][node.second]=='G';
}

bool isStart(pi node){
//	Check to see if the node is the start node
	return maze[node.first][node.second]=='S';
}


string bfs_search(vector<vector<char>>& maze, pi start, pi goal){
//	Performs a Breadth-First Search on the maze and returns the 
//  actions to be taken to get to the goal

	string path;
	queue<FrontierNode> frontier;
	map<pi,pair<pi,char>> explored;
	FrontierNode frontier_node(start,start,'\0'); // start node
	frontier.push(frontier_node);
	
	while(!frontier.empty()){
		
//		cout<<"Frontier"<<endl;
//		printFrontier(frontier);
		
		// For BFS pop the frontier in a FIFO manner
		FrontierNode frontier_node = frontier.front();
		frontier.pop();
		
		// Current node in consideration
		pi node = frontier_node.getNode();
		
		// Check if this node is already expanded
		if(explored.find(node)==explored.end()){
			// Get the children of the current node		
			unordered_map<char,pi> children = getChildren(node);
			
			// Add the children to the back of the Frontier
			for(auto x: children){
				FrontierNode child(x.second,node,x.first);
				frontier.push(child);
			}
			
			// Mark the current node to be explored with its parent and the action
			explored[node] = make_pair(frontier_node.getParent(),frontier_node.getMove());
//			cout<<"Explored"<<endl;
//			printExplored(explored);
		}
		
		// If the current node is the Goal node, break the search, we are done!
		if(isGoal(node)){
			break;
		}
	}
	
//	cout<<"Explored"<<endl;
//	printExplored(explored);
	
	// Backtrack the path taken to get to the node
	pi node = goal;
	while(!isStart(node)){
		path = explored[node].second + path;
		node = explored[node].first;
	}
	
	cout<<path;
	return path;
}




