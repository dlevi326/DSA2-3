#ifndef _GRAPH_H
#define _GRAPH_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <list>
#include <vector>
#include <string>
#include <algorithm>
#include <ctime>
#include <cmath>
#include <cstring>
#include <cctype>
#include <cstdlib>
#include <iterator>
#include <ctime>
#include "hash.h"
#include "heap.h"


using namespace std;

class graph{

public:
	class edge;
	class node{
	public:
		node();
		
		string id;
		int distance;
		node* prev;

		vector<edge> adj;
	};

	class edge{
	public:
		edge(int w, node* n=NULL);
		node* dest;
		int weight;
	};
	list<node*> nodelist;

	graph();

	hashTable verts;

	//heap* H;





	int insert(string id1,string id2,int w);
	void printnodes(string outfile);
	int execute(string s, int count);
	



};









#endif