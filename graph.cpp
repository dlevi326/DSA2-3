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
#include "graph.h"


using namespace std;

graph::graph(){
	//H = new heap; // Initialize heap pointer
}

graph::node::node(){
	// Initialize members
	id = "";
	distance = 1000000001;
	prev = NULL;
	adj.clear();
}

graph::edge::edge(int w,node* n){
	// Initialize edges
	dest = n;
	weight = w;
}



int graph::insert(string id1,string id2,int w){
	// Function returns a value based on how many unique nodes are encountered
	int result = 0;
	
	if(!verts.contains(id1)){
		// Creating a new node
		node* n1 = new graph::node();
		n1->id = id1;
		verts.insert(id1,n1);
		nodelist.push_back(n1);
		result++;
		
	}
	else{
		// Node already exists
		void* pntr1 = verts.getPointer(id1);
		node* pn1 = static_cast<node*>(pntr1);
		pn1->id = id1; 

	}
	if(!verts.contains(id2)){
		// Creating a new node
		node* n2 = new graph::node();
		n2->id = id2;
		verts.insert(id2,n2);
		nodelist.push_back(n2);
		result++;
		
	}
	else{
		// Node already exists
		void* pntr2 = verts.getPointer(id2);
		node* pn2 = static_cast<node*>(pntr2);
		pn2->id = id2;

	}

	void* pntr1 = verts.getPointer(id1);
	node* pn1 = static_cast<node*>(pntr1);
	void* pntr2 = verts.getPointer(id2);
	node* pn2 = static_cast<node*>(pntr2);

	// Adding a new edge
	edge e(w,pn2); 
	pn1->adj.push_back(e);
	return result;





}

void graph::printnodes(string outfile){

	// Opening output
	ofstream file;
	file.open(outfile);
	if (!file.is_open()){
    	cout<<"ERROR"<<endl;
    } 

    stringstream ss; // Setting up string stream

	list<node*>::iterator it;
	vector<string> path;
	for(it = nodelist.begin();it!=nodelist.end();it++){
		path.clear();
		node* pn = *it;
		if(pn->distance == 1000000001){
			// If distance is still at the max there is obviously no path

			ss<<pn->id<<": ";
			ss<<"NO PATH"<<endl;

			continue;
		}
		// Printing logistics

		ss<<pn->id<<": "<<pn->distance<<" [";

		

		path.push_back(pn->id);
		while(pn->prev!=NULL){
			path.push_back(pn->prev->id);
			pn = pn->prev;
		}
		for(int j=path.size()-1;j>=0;j--){
			ss<<path[j];
			if(j==0){
				continue;
			}
			else{
				ss<<", ";
			}
		}
		ss<<"]"<<endl;
		

	}
	file << ss.str();
    ss.str(string());

}

int graph::execute(string s, int count){
	heap* H = new heap(count);
	

	if(!verts.contains(s)){
		cout<<"This vertice does not exist"<<endl;
		return 0;
	}
	else{

		//H->capacity = count;
		list<node*>::iterator it;
		for(it = nodelist.begin();it!=nodelist.end();it++){
			node* pn1= *it;
			H->insert(pn1->id,pn1->distance,pn1);
		}

		void* pntr;

		H->remove(s,NULL,&pntr);
		node* pn = static_cast<node*>(pntr);
		pn->distance = 0;
		int flag = 0;


		while(!flag){
			for(int i=0;i<pn->adj.size();i++){
				if(pn->adj[i].weight+pn->distance < pn->adj[i].dest->distance){
					pn->adj[i].dest->distance = pn->adj[i].weight + pn->distance;
					pn->adj[i].dest->prev = pn;
					H->setKey(pn->adj[i].dest->id,pn->adj[i].dest->distance);
				}
			}
			void* pntr;
			flag = H->deleteMin(NULL,NULL,&pntr);
			pn = static_cast<node*>(pntr);

		}	
	}
	return 1;
}







