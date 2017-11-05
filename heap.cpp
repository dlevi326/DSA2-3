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

heap::heap(int c){
	capacity = c-1;
	currsize = 0;
	data.resize(capacity+1);
	mapping = new hashTable(capacity*2);
	
}

heap::node::node(){
	id = "empty";
    key = 0;
    pv = NULL;
}

void heap::printHeap(){
	cout<<"PRINTING HEAP:"<<endl;
	/*for(int i=0;i<currsize;i++){
		cout<<"ID: "<<data[i].id<<" key: "<<data[i].key<<endl;
	}*/

	for(int i=0;i<currsize;i++){
		void* pntr = data[i].pv;
		node* pn1 = static_cast<node*>(pntr);
		cout<<"ID: "<<pn1->id<<" key: "<<pn1->key<<endl;
	}
}


void heap::percolateUp(int hole) { // Used for insert
	node n = data[hole]; // IS THIS NEEDED?
	for(;hole>=1 && n.key<data[hole/2].key;hole /= 2){ // Inserts item
		data[hole] = data[hole/2];
		mapping->setPointer(data[hole].id, &data[hole]); // Added data[hole] instead of data[0]
	}
	data[hole] = n;
	mapping->setPointer(data[hole].id, &data[hole]);
}

int heap::insert(string id, int key, void* pv){
	int hole = currsize; // My currsize is actually 1 greater than max position in array 
	if(hole>capacity){
		return 1; // Heap is already filled to capacity
	}
	else if(mapping->contains(id)){
		return 2; // Item already exists in Heap
	}
	else{
		currsize++;
		data[hole].id = id;
		data[hole].key = key;
		data[hole].pv = pv;
		mapping->insert(id, &data[hole]);
		percolateUp(hole);
		return 0; // Item inserted succesfully
	}
}

int heap::deleteMin(string *pId, int *pKey, void *ppData){
	if(currsize == 0){
		return 1;
	}
	else{
		if(pId){
			*pId = data[0].id;
		}
		if(pKey){
			*pKey = data[0].key;
		}
		if(ppData){
			*(static_cast<void **> (ppData)) = data[0].pv;
		}
		mapping->remove(data[0].id);
		data[0] = data[currsize-1];
		currsize--;
		percolateDown(0);
		return 0;
	}
}

int heap::setKey(const string &id, int key){
	bool b;
	node *pn = static_cast<node*>(mapping->getPointer(id, &b)); 
	int pos = getPos(pn);

    if(!b){
      return 1;
    }
    else{
      data[pos].key = key;
      if(pos == 0){ 
        percolateDown(0);
        return 0;
      }

      int parent = (pos)/2;
      int left = (pos)*2;
      int right = ((pos)*2)+1;

      if (left>currsize-1 || right>currsize-1 || key<data[parent].key){
        percolateUp(pos);
        return 0;
      }
      else{
        percolateDown(pos);
        return 0;
      }
    }
}

int heap::remove(const string &id, int *pKey, void *ppData){
	bool b;
	node* pn = static_cast<node *> (mapping->getPointer(id,&b));
	if(!b){
		return 1;
	}
	else{
		if(pKey){
			*pKey = data[getPos(pn)].key;
		}
		if(ppData){
			*(static_cast<void **> (ppData)) = data[getPos(pn)].pv;
		}
		mapping->remove(data[getPos(pn)].id);
		data[getPos(pn)] = data[currsize-1];
		currsize--;
		if(getPos(pn)==0){
			if(((data[0].key > data[1].key) && currsize > 1) || ((data[0].key > data[2].key) && currsize > 2)){
				percolateDown(getPos(pn));
				return 0;
			}
			else{
				data[0] = *pn;
				mapping->setPointer(data[0].id, &data[0]);
				return 0;
			}
		}
		else if(data[getPos(pn)].key < data[getPos(pn)*2].key || data[getPos(pn)].key < data[(getPos(pn)*2)+1].key){
			percolateDown(getPos(pn));
			return 0;
		}
		else{
			percolateUp(getPos(pn));
			return 0;
		}
	}
}

int heap::getPos(node *pn){
	int pos = pn-&data[0];
	return pos;
}

void heap::percolateDown(int hole){ // Used for deleteMin

	int left,right; 
  	node n = data[hole];

  	while ((currsize-1)/2 >= hole) { 
    	right = (hole*2)+1;
    	left = (hole*2);
    	if (n.key>data[left].key && data[right].key>=data[left].key){
      		data[hole] = data[left];
      		mapping->setPointer(data[hole].id, &data[hole]);
      		hole = hole*2;
    	}
    	else if (n.key>data[right].key && data[right].key<=data[left].key){
      		data[hole] = data[right];
      		mapping->setPointer(data[hole].id, &data[hole]);
      		hole = (hole*2)+1;
    	}
    	else{
      		break;
    	}
  	}

  	data[hole] = n;
  	mapping->setPointer(data[hole].id, &data[hole]); 

}



	







