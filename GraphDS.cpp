// GraphDS.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <list>
#include<queue>
using namespace std;



struct edge{

	double weight;
	pair<string, string> vertices;
	bool isdirected;
};

struct node{
string name;
};

class graph{
	vector<list<node>> adjlist;//adj list of nodes--with the first item in the list being 
	queue<node> BFSqueue;
	vector<string> BFS_order; //the BFS tree

	list<edge> edgelist; //list of edges in the graph
public:
	void addedge(const string&  , const string&   , double , bool);
	void deleteedge(const string&  , const string&  );
	void printgraph();
	void createAdjlist();
	void BFS_walk(string nodename);


};

void graph::BFS_walk(string nodename){

	BFS_order.push_back(nodename);
	//find the corresponding node in the list and enqueue it if it exists
	unsigned int bfs_source = atoi( nodename.c_str());
	//get the list of adj nodes 
	list<node> to_be_explored = adjlist[bfs_source];
	//explore all adj nodes
	for (std::list<node>::iterator it=to_be_explored.begin() ; it != to_be_explored.end(); ++it)
		BFSqueue.push(*it);

	while(!BFSqueue.empty()){
		node temp = BFSqueue.front();
		BFSqueue.pop();
		BFS_walk(temp.name);
	
	}

	//deque the next node and recursively call BFS_walk




}

void graph::addedge(const string& node1, const string& node2 , double cost, bool isdag){
	edge newedge;
	newedge.weight=cost;
	newedge.vertices=make_pair(node1, node2);
	newedge.isdirected=isdag;
	edgelist.push_back(newedge);
	

}

void graph::printgraph(){
cout<<"The graph saved in memory is"<<endl;
for (std::list<edge>::iterator it= this->edgelist.begin() ; it != this->edgelist.end(); ++it)
	std::cout << ' ' <<"Edge:"<< it->vertices.first<< it->vertices.second<<" "<<it->weight<<endl;


}

void graph::createAdjlist(){
	


	for (std::list<edge>::iterator it= this->edgelist.begin() ; it != this->edgelist.end(); ++it)
		currentVertex=  it->vertices.first;
		while(



}


int main(){

graph g1;
g1.addedge("a","b", 1.0, false);
g1.addedge("b", "c", 2.0, false);
g1.addedge("c", "a", 2.0, false);
g1.addedge("c", "d", 2.0, false);
g1.addedge("d", "e", 3.0, false);
g1.printgraph();

}


 