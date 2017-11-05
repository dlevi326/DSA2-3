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
#include <sstream>
#include "hash.h"
#include "heap.h"
#include "graph.h"


using namespace std;


int main(){

	cout<<"Enter name of graph file: ";
	string filename;
	cin>>filename;

	ifstream file;
	file.open(filename);
	if (!file.is_open()){
    	cout<<"ERROR"<<endl;
    } 

    string line;
    graph g;
    string a,b,w;
    int count = 0;
    while(getline(file,line)){
    	//count++;
    	istringstream iss(line);
    	iss>>a>>b>>w;
    	// cout<<a<<" --> "<<b<<" weight: "<<w<<endl; Used for debugging purposes

    	count+=g.insert(a,b,stoi(w));
    }
	
	int seconds = 0;
	string start;
	string outfile;

	cout<<"Enter a valid vertex id for the staring vertex: ";
	cin>>start;
	clock_t t1 = clock();
	while(!g.execute(start,count)){
		cout<<"Enter a valid vertex id for the staring vertex: ";
		cin>>start;
		clock_t t1 = clock();
	}
	clock_t t2 = clock();
	double timeDiff = ((double) (t2 - t1)) / CLOCKS_PER_SEC;
	cout<<"Total time (in seconds) to apply Dijkstra's algorithm: "<<timeDiff<<endl;
	cout<<"Specify outfile: ";
	cin>>outfile;
	g.printnodes(outfile);	

	return 0;
}















