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

#include "utilities.h"

using namespace std;

string bfs_search(std::vector<std::vector<char>>& maze, pi start, pi goal, unordered_map<char,pi>& moves);

int main(int argc, char** argv) {

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

	cout<<"Maze\n";
	printMaze(maze);
	// printMoves(moves);
	// printLegalMoves(maze);
	string path = bfs_search(maze,start,goal,moves);
	cout<<"\nPath: "<<path<<endl;

	return 0;
}


string bfs_search(vector<vector<char>>& maze, pi start, pi goal, unordered_map<char,pi>& moves){
// Performs a Breadth-First Search on the maze and returns the 
// actions to be taken to get to the goal

	string path;
	queue<FrontierNode> frontier;
	map<pi,pair<pi,char>> explored;
	FrontierNode frontier_node(start,start,'\0'); // start node
	frontier.push(frontier_node);
	
	while(!frontier.empty()){
		
		// cout<<"Frontier"<<endl;
		// printFrontier(frontier);
		
		// For BFS pop the frontier in a FIFO manner
		FrontierNode frontier_node = frontier.front();
		frontier.pop();
		
		// Current node in consideration
		pi node = frontier_node.getNode();
		
		// Check if this node is already expanded
		if(explored.find(node)==explored.end()){
			// Get the children of the current node		
			unordered_map<char,pi> children = getChildren(node,maze,moves);
			
			// Add the children to the back of the Frontier
			for(auto x: children){
				FrontierNode child(x.second,node,x.first);
				frontier.push(child);
			}
			
			// Mark the current node to be explored with its parent and the action
			explored[node] = make_pair(frontier_node.getParent(),frontier_node.getMove());
			// cout<<"Explored"<<endl;
			// printExplored(explored);
		}
		
		// If the current node is the Goal node, break the search, we are done!
		if(isGoal(node,maze)){
			break;
		}
	}
	
	// cout<<"Explored"<<endl;
	// printExplored(explored);
	
	// Backtrack the path taken to get to the node
	pi node = goal;
	while(!isStart(node,maze)){
		path = explored[node].second + path;
		node = explored[node].first;
	}
	
	// cout<<path;
	return path;
}




