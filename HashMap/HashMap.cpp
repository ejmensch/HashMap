//Bryce Leslie Ethan Mensch

#include "hashMap.hpp"
#include "hashNode.hpp"
#include <iostream>
#include <math.h>
using namespace std;

// Nothing returns right now, but I think it's just because every function in here needs to be written

hashMap::hashMap(bool hash1, bool coll1) {
	map = new hashNode*[mapSize];
	first = "";
	mapSize = 500; // states 500 in code instructions
	numKeys = 0;
	for (int i=0;i<mapSize;i++) {
		map[i] = NULL; // values set to NULL in the map
	}
	collfn = coll1;
	hashfn = hash1;
	collisions = 0;
	hashcoll = 0;
	// all values in .hpp file are initialized
}
void hashMap::addKeyValue(string k, string v) {
	int ind = getIndex(k);
	if (map[ind]==NULL) { //adds a node at each null value
		map[ind]=new hashNode(k,v);
		numKeys++;
	}
	else if (map[ind]->keyword==k) {
		// add values if index's keyword matches the parameter k
		map[ind]->addValue(v);
	}
	else if (map[ind]->keyword!=k) { // calculate new hash index
		hashcoll++;
		if (hashfn==true) {
			ind = coll1(calcHash1(k),getIndex(k),k);
		}
		else {
			ind = coll2(calcHash2(k),getIndex(k),k);
		}
	}
	double load = (double)numKeys/double(mapSize);
	if (load>=0.7) { // call rehash if load is over 70%
		reHash();
	}
}
int hashMap::getIndex(string k) {
}

int hashMap::calcHash2(string k){
}
int hashMap::calcHash1(string k){
}
void hashMap::getClosestPrime() {
}
void hashMap::reHash() {
	int newsize=2*mapSize; // double array size
	mapSize=newsize;
	hashNode **prevmap=map;
	for (int i=0;i<mapSize/2;i++){ //update each node in the new map
		if (prevmap[i]!=NULL) {
			if (hashfn==true) {
				int ind=calcHash1(prevmap[i]->keyword);
				map[ind]=prevmap[i];
			}
			else {
				int ind=calcHash2(prevmap[i]->keyword);
				map[ind]=prevmap[i];
			}
		}
	}
	delete[] prevmap;
	return;
	// I think this should be done
}
int hashMap::coll1(int h, int i, string k) {
}
int hashMap::coll2(int h, int i, string k) {
}
int hashMap::findKey(string k) {
//NOTE: THIS METHOD CANNOT LOOP from index 0 to end of hash array looking for the key.  That destroys any efficiency in run-time.
}


void hashMap::printMap() {
	cout << "In printMap()" << endl;
	for (int i = 0; i < mapSize; i++) {
		//cout << "In loop" << endl;
		if (map[i] != NULL) {
			cout << map[i]->keyword << ": ";
			for (int j = 0; j < map[i]->currSize;j++) {
				cout << map[i]->values[j] << ", ";
			}
			cout << endl;
		}
	}
}


