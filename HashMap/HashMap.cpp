//Bryce Leslie Ethan Mensch

#include "hashMap.hpp"
#include "hashNode.hpp"
#include <iostream>
#include <math.h>
using namespace std;


hashMap::hashMap(bool hash1, bool coll1) {
	first = "";
	mapSize = 500; // states 500 in code instructions
	map = new hashNode*[mapSize];
	numKeys = 0;
	for (int i=0;i<mapSize;i++) {
		map[i] = NULL; // values set to NULL in the map
	}
	collfn = coll1;
	hashfn = hash1;
	collisions = 0;
	hashcoll = 0;
	// all values in .hpp file are initialized
	/*
	first = "";
	numKeys = 0;
	mapSize = 100;
	map = new hashNode*[mapSize];
	for(int i = 0; i < mapSize; i++){
		map[i] = NULL;
	}
	hashfn = hash1;
	collfn = coll1;
	collisions = 0;
	hashcoll = 0;
	//cout << "EXIT HASH" <<endl;
	return;
	*/
}
void hashMap::addKeyValue(string k, string v) {
	int ind = getIndex(k);
	cout << k << " ";
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
			if (hashfn==true) {
				ind = coll1(calcHash1(k),getIndex(k),k);
				if (map[ind]==NULL) {
					map[ind] = new hashNode(k,v);
					numKeys++;
				}
				else if (map[ind]->keyword==k) {
					map[ind]->addValue(v);
				}
			}
			else {
				ind = coll1(calcHash2(k),getIndex(k),k);
				if (map[ind]==NULL) {
					map[ind] = new hashNode(k,v);
					numKeys++;
				}
				else if (map[ind]->keyword==k) {
					map[ind]->addValue(v);
				}
			}
		}
		else {
			if (hashfn==true) {
				ind = coll2(calcHash1(k),getIndex(k),k);
				if (map[ind]==NULL) {
					map[ind] = new hashNode(k,v);
					numKeys++;
				}
				else if (map[ind]->keyword==k) {
					map[ind]->addValue(v);
				}
			}
			else {
				ind = coll2(calcHash2(k),getIndex(k),k);
				if (map[ind]==NULL) {
					map[ind] = new hashNode(k,v);
					numKeys++;
				}
				else if (map[ind]->keyword==k) {
					map[ind]->addValue(v);
				}
			}
		}
	}

	float load = (float)numKeys/(float)mapSize;
	if (load>=0.7) {
		reHash();
	}
	/*
	int index = getIndex(k);
	cout << k << " " ;
	if(map[index]==NULL){
		map[index]=new hashNode(k,v);
		numKeys++;
	}
	else if(map[index]->keyword==k){
		map[index]->addValue(v);
	}
	else if(map[index]->keyword!=k){
		hashcoll++;
		if(collfn==true){
			if(hashfn==true){
				index = coll1(calcHash1(k),getIndex(k),k);
			}
			else{
				index = coll1(calcHash2(k),getIndex(k),k);
			}
		}
		else{
			if(hashfn==true){
				index = coll2(calcHash1(k),getIndex(k),k);
			}
			else{
				index = coll2(calcHash2(k),getIndex(k),k);
			}
		}
		if(map[index]==NULL){
			map[index]=new hashNode(k,v);
			numKeys++;
		}
		else if(map[index]->keyword==k){
			map[index]->addValue(v);
		}
	}
	double load = (double)numKeys/double(mapSize);
	if(load>=0.7){
		reHash();}
	return;
	*/
}
int hashMap::getIndex(string k) {
	float load = (float)numKeys/(float)mapSize;
	if (load>=0.7) {
		reHash();
	}
	int ind;
	if (hashfn==true) {
		ind = calcHash1(k)%mapSize;
	}
	else if (hashfn==false) {
		ind = calcHash2(k)%mapSize;
	}
	else {
		ind = -1;
	}
	return ind;
	/*
	double load = (double)numKeys/double(mapSize);
	if(load>=0.7){
		reHash();
	}
	int index=-1;
	if(hashfn==true){
		index = (calcHash1(k))%mapSize;
	}
	else{
		index = calcHash2(k)%mapSize;
	}
	return index;
	*/
}

int hashMap::calcHash2(string k) {
	//rolling hash
	//https://cp-algorithms.com/string/string-hashing.html
	int len = k.length();
	unsigned long int hash = 0;
	int p = 53;
	int power = 1;
	for(int i = 0; i<len ; i++){
		hash = (hash + (k[i] - 'a' + 1) * power) % mapSize;
		power = (power * p) % mapSize;
	}
	return hash;
}
int hashMap::calcHash1(string k) {
	//odd even differentiation
	int len = k.length();
	unsigned long int hash = 0;
	if(len%2 == 0){   //even
		for(int i=0; i<len;i++){
			//hash = ((int)k[i] + 11*hash) % len; //instead of len here we need the array size of the data so mapSize? Bryce can you ask about this tomorrow?
			hash = ((int)k[i] + 11*hash) % mapSize;
		}
	}
	else {
		for (int i = 0; i < len; i++) {
			//hash = ((int)k[i] + 37 * hash) % len;
			hash = ((int)k[i] + 37 * hash) % mapSize;
		}
	}
	return hash;

//this was an attemp to do every other letter, might come back to it later
//	int len = k.length();
//	unsigned long int hsh = 0;
//	int i;
//	if (len<4){
//		for( i = 0; i< len ; i++){
//			hsh = ((int)k[i] + 7*hsh) % len;
//		}
//	}
//	else if(len%2 == 0){
//		for(i)
//	}
//	else {
//		for (i = 0; i < len - 1; i += 2) {
//			hsh = ((int) k[i] + hsh) % len;
//		}
//	}
//	return hsh;
	//maybe done?
	//probably add a check if the string is odd or even
}
void hashMap::getClosestPrime() {
	int primes [33]= {2,3,5,7,11,13,17,19,23,29,31,37,41,43,47,53,59,61,67,71,73,79,83,89,97,101,103,107,109,113,127,131,137}; //add more primes later
	int len = sizeof(primes)/sizeof(primes[0]); //high
	int middle = (len)/2; //if it doesnt work just hard code a variable for the length and change that
	int low = 0;
	int newMapSize = 2*mapSize;
	for(int i = 0 ; i< len; i++){
		if (newMapSize == primes[middle]){
			mapSize = primes[middle];
		}
		else if (newMapSize > primes[middle]){
			//set new middle using boundaries
			low = middle;
			middle = (len - middle)/2 + middle;

		}
		else if (newMapSize < primes[middle]){
			len = middle;
			middle = (low + middle)/2 +low;
		}
		//once you hit the same middle twice, break , check prime at value , if its less than mapSize - go up , if greater than, youre good - set new map size
	}
	// checck greater than or less than here- outside of loop
	if (newMapSize > primes[middle]){
		mapSize = primes[middle+1];
	}
	else{
		mapSize = primes[middle];
	}
	/*
	int ogsize = mapSize*2;
	if(ogsize == 0 || ogsize ==1 || ogsize==2){
		mapSize=3;
		return;
	}
	int up =ogsize-1;
	bool upPrime=false;
	while(upPrime==false){
		up = up+1;
		upPrime =true;
		for(int i=2;i<up;i++){
			if(up%i==0){
				upPrime=false;
				i = up;
			}
		}
	}
	int down =ogsize+1;
	bool downPrime=false;
	while(downPrime==false && down>2){
		down = down-1;
		downPrime =true;
		for(int i=2;i<down;i++){
			if(down%i==0){
				downPrime=false;
				i = down;
			}
		}

	}
	if(down==2){
		mapSize=up;
	}
	else if((ogsize-down)<(up-ogsize)){
		mapSize=down;
	}
	else{
		mapSize=up;
	}
	return;
	*/
}
void hashMap::reHash() {
	numKeys = 0;
	// make clone
	hashNode *clone[mapSize];
	for (int i = 0; i<mapSize;i++) {
		clone[i]=map[i];
	}
	int prevsize = mapSize;
	delete[]map;
	// give clone the updated mapsize by running get closest primes
	getClosestPrime();
	map = new hashNode*[mapSize];
	// iterate thru original map
	// here's how you spell through since you didn't know Friday
	for (int i = 0; i<mapSize; i++) {
		map[i] = NULL;
	}
	for (int j = 0; j<prevsize; j++) {
		if (clone[j] != NULL) {
			int ind = getIndex(clone[j]->keyword);
			// Process below follows a very similar process to addKeyValue
			// Just not adding any more values, just the rehash on the keys

			// take those strings, call hashes on the strings again
			if (map[ind]==NULL) {
				map[ind]=clone[j];
				numKeys++;
			}
			else if (map[ind]!=NULL) {
				hashcoll++;
				if (hashfn==true) {
					if (collfn==true) {
						ind = coll1(calcHash1(clone[j]->keyword),getIndex(clone[j]->keyword),clone[j]->keyword);
					}
					else {
						ind = coll1(calcHash1(clone[j]->keyword),getIndex(clone[j]->keyword),clone[j]->keyword);
					}
				}
				else {
					if (collfn==true) {
						ind = coll1(calcHash1(clone[j]->keyword),getIndex(clone[j]->keyword),clone[j]->keyword);
					}
					else {
						coll1(calcHash1(clone[j]->keyword),getIndex(clone[j]->keyword),clone[j]->keyword);
					}
				}
				// take outputs of the hash function and feed them to the new array
				map[ind]=clone[j];
				numKeys++;
			}
		}
	}
}

int hashMap::coll1(int h, int i, string k) {
	//quadratic probing
	for (int j = 0; map[h%mapSize] != NULL && map[h%mapSize]->keyword != k; j++) {
		h = (h+(j * j))%mapSize;
		collisions++;
	}
	collisions--;
	return h;
}
int hashMap::coll2(int h, int i, string k) {
	// double hashing , adding half the aski value % 13 , do i have to use i for iterating through index? or can i not since it's already used?

	int len = k.length();
	int hash = 0;
	for (int j = 0; map[h%mapSize] != NULL && map[h%mapSize]->keyword != k; j++){
		for(i= 0; i<len;i++){
			hash = hash + int(k[i])/2;
		}
		hash = hash %13;
		collisions++;
	}
	collisions--;
	return hash;
}
int hashMap::findKey(string k) {
	int ind = getIndex(k);
	if (hashfn==true) {
		ind = calcHash1(k);
		if (map[ind]->keyword==k) {
			return ind;
		}
		else if (collfn==true) {
			ind = coll1(calcHash1(k),getIndex(k),k);
			if (map[ind]->keyword==k){
				return ind;
			}
			else {
				return -1;
			}
		}
		else if(collfn==false) {
			ind = coll2(calcHash1(k),getIndex(k),k);
			if (map[ind]->keyword==k) {
				return ind;
			}
			else {
				return -1;
			}
		}
		else {
			return -1;
		}
	}
	else {
		ind = calcHash2(k);
		if (map[ind]->keyword==k) {
			return ind;
		}
		else if (collfn==true) {
			ind = coll1(calcHash2(k),getIndex(k),k);
			if(map[ind]->keyword==k){
				return ind;
			}
			else {
				return -1;
			}
		}
		else if(collfn==false) {
			ind = coll2(calcHash2(k),getIndex(k),k);
			if(map[ind]->keyword==k) {
				return ind;
			}
			else {
				return -1;
			}
		}
		else {
			return -1;
		}
	}
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
