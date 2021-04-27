//Bryce Leslie Ethan Mensch

#include "hashMap.hpp"
#include "hashNode.hpp"
#include <iostream>
#include <math.h>
using namespace std;


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
		if (collfn==true) {
			ind = coll1(calcHash1(k),getIndex(k),k);
		}
		else {
			ind = coll2(calcHash2(k),getIndex(k),k);
		}
	}
	int load = numKeys/mapSize; // did I do this right?   ~What if a fraction and not a whole nummber?-E
	if (load>=0.7) { // call rehash if load is over 70%
		reHash();
	}
	// done I think if load is correct
}
int hashMap::getIndex(string k) {
	// What does reHash need to be called for and where does it go?  ~Check if it needs to be rehashed?-E
	if (hashfn==true) {
		// think we call calcHash1 but want to get that function before we try this
	}
	else{
		// think we call calcHash2 but want to get that function before we try this
	}
}

int hashMap::calcHash2(string k) {
	//divide ascii by incremeenting number for each run through loop?

}
int hashMap::calcHash1(string k) {
	//take every other letter of a string
	int len = k.length();
	unsigned long int hsh = 0;
	for (int i =0 ; i <= len-1 ; i+=2){
		hsh = ((int)k[i] + hsh) % len;
	}
	return hsh;
	//maybe done?
	//probably add a check if the string is odd or even
}
void hashMap::getClosestPrime() {
	// confused how to start this one
	// Understand what is being asked but don't know how to approach it
}
void hashMap::reHash() {
	int newMapSize=2*mapSize; // double array size
	mapSize=newMapSize;
	hashNode **prevmap=map;
	for (int i=0;i<mapSize/2;i++){
		if (prevmap[i]!=NULL) {
			if (hashfn==true) { //update each node in the new map
				int ind=calcHash1(prevmap[i]->keyword);
				map[ind]=prevmap[i];
			}
			else { //update each node in the new map
				int ind=calcHash2(prevmap[i]->keyword);
				map[ind]=prevmap[i];
			}
		}
	}
	delete[] prevmap; // deletes previous map once the new map is filled
	return;
	// I think this should be done
}
int hashMap::coll1(int h, int i, string k) {
	// don't really know how to start this
}
int hashMap::coll2(int h, int i, string k) {
	// same as coll1
}
int hashMap::findKey(string k) {
//NOTE: THIS METHOD CANNOT LOOP from index 0 to end of hash array looking for the key.  That destroys any efficiency in run-time.
	if (hashfn==true) {
		int ind = calcHash1(k);
		if (k==map[ind]->keyword) {
			return ind;
			// return index if the keyword matches the string
		}
	}
	// Need to add collision functions 1 and 2 to search for key in array
	// Want to wait to try this until we get coll1 and coll2
	if (hashfn==false) {
		int ind = calcHash2(k);
		if (k==map[ind]->keyword) {
			return ind;
			// return index if the keyword matches the string
		}
	}
	// Need to add collision functions 1 and 2 to search for key in array
	// Want to wait to try this until we get coll1 and coll2
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



