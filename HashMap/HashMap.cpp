//Bryce Leslie Ethan Mensch

#include "hashMap.hpp"
#include "hashNode.hpp"
#include <iostream>
#include <math.h>
using namespace std;

/* Functions:
 * hashMap - think good
 * addKeyValue - think good, but still unsure
 * getIndex - think good
 * calcHash1 - think good
 * calcHash2 - think good
 * getClosestPrime - think done
 * reHash - needs work
 * coll1 - think good
 * coll2 - think good
 * findKey - not sure
 * printMap - given
 */

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

	float load = numKeys/mapSize;
	if (load>=0.7) {
		reHash();
	}
}
int hashMap::getIndex(string k) {
	float load = numKeys/mapSize;
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
		if (newMapSize == primes[middle]){//never happens
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
}
void hashMap::reHash() {
	//make clone
	//give clone the updated mapsize by running get closest primes
	//iterate thru original map
	//take those strings, call hashes on the strings again
	//take outputs of the hashfunction and feed them to the new array , hash = calcHash1(string) , then make clone[hash] = string?





//	int prevsize=mapSize;
//	getClosestPrime();
//	//E's attempt
//	hashNode **clone;
//	clone = new hashNode*[mapSize];//how do i set a new map?
//	for(int i=0;i<mapSize;i++){ //fill clone with NULLS
//		clone[i]=NULL;
//	}
//	numKeys = 0;
//	for(int j=0;j<prevsize;j++){
//		if(map[j]!= NULL){
//			int index=j;//get index of that
//
//		if(clone[index]==NULL){ //if empty, fill it
//			clone[index]=map[j];
//			numKeys++;
//		}
//		else if(clone[index]!=NULL){ //colision
//			hashcoll++;
//			if(collfn==true){//coll1
//				if(hashfn==true){//hash1
//
//				}
//				else{//hash2
//
//				}
//
//
//				} else if (collfn == false) { //coll2
//					if (hashfn == true) { //hash1
//
//					}
//					else { //hash2
//
//					}
//				}
//				numKeys++;
//			}
//		}
//	}
//
//	return;

//	int newMapSize=2*mapSize; // double array size
//	mapSize=newMapSize;
//	hashNode **flipmap=map;
//	for (int i=0;i<mapSize/2;i++){
//		if (flipmap[i]!=NULL) {
//			if (hashfn==true) { //update each node in the new map
//				int ind=calcHash1(flipmap[i]->keyword);
//				map[ind]=flipmap[i];
//			}
//			else { //update each node in the new map
//				int ind=calcHash2(flipmap[i]->keyword);
//				map[ind]=flipmap[i];
//			}
//		}
//	}
//	delete[] flipmap; // deletes previous map once the new map is filled
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
//	if (map[i] != k){ //need help on with the test for collision line
//
//		h = calcHash1(k) + calcHash2(k);
//	}
//  this needs some work
}
int hashMap::findKey(string k) {
//NOTE: THIS METHOD CANNOT LOOP from index 0 to end of hash array looking for the key.  That destroys any efficiency in run-time.
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
	if (hashfn==false) {
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
	return -1;
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
