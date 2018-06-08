//
//  graph.cpp
//  Project4
//
//  Created by Bein, Doina on 4/21/18.
//  Copyright © 2018 Bein, Doina. All rights reserved.
//

#include "graph.h"
#include <iostream>
#include <fstream>
#include <algorithm>
using namespace std;

Graph::Graph() // default constructor
{
	for (int i = 0; i<100; i++) {
		for (int j = 0; j<100; j++) {
			edges[i][j] = 0;
		}
		visitedNode[i] = 0;
	}
	numOfEdges = 0;
}

Graph::Graph(int rno, float rbudget) // constructor with two arguments representing the number of nodes, initial budget
{
	numOfNodes = rno;
	startBudget = currentBudget = rbudget;
	numOfEdges = 0;
}

void Graph::addEdge(int node1, int node2) // adds an edge between two nodes in the graph node1 and node2
{
	edges[node1][node2] = 1;
	edges[node2][node1] = 1;
	numOfEdges += 1;
}
void Graph::setValue(int node, float rval) // sets a value for a node
{
	valueOfNode[node] = rval;
}

void Graph::setBudget(float rbu) // sets the initial budget
{
	startBudget = currentBudget = rbu;
}

int Graph::getNSize() // return number of nodes
{
	return numOfNodes;
}

int Graph::getESize() // return number of edges
{
	return numOfEdges;
}

float Graph::getBudget() // return current budget
{
	return currentBudget;
}

float Graph::getValue(int node) // returns the value of the node
{
	return valueOfNode[node];
}

void Graph::readData(string fileName) // reads data from a specified file
{
	ifstream file(fileName);
	file >> numOfNodes;
	file >> startBudget;
	currentBudget = startBudget;

	for (int i = 0; i<numOfNodes; i++)
		file >> valueOfNode[i];

	int node1, node2;
	while (file >> node1 >> node2) {
		addEdge(node1, node2);
	}
}

int Graph::DFS(int startNode) //return the number of nodes visited using BFS starting at startNode and accumulating values at each node, as long as the budget remains positive
{
	DFSHelper(startNode);
	int count = 0;
	for (int i = 0; i<numOfNodes; i++) {
		if (visitedNode[i])
			count++;
	}
	return count;
}

void Graph::DFSHelper(int startNode)
{
	if (currentBudget + valueOfNode[startNode] >= 0) {
		visitedNode[startNode] = 1;
		currentBudget += valueOfNode[startNode];
		for (int i = 0; i<numOfNodes; i++) {

			if (edges[startNode][i] && !visitedNode[i]) {
				DFS(i);
			}

		}
	}
}
// return the starting node that gives a longest DFS run before running out of budget
// if there are multiple nodes with the same DFS run length, return the smallest node
int Graph::bestStartVertex()
{
	int maxcount = 0;
	for (int i = 0; i<numOfNodes; i++) {
		for (int j = 0; j<numOfNodes; j++)
			visitedNode[j] = 0;
		maxcount = max(maxcount, DFS(i));
	}
	return maxcount;
}

