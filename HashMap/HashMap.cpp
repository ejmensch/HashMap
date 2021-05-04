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

}
void hashMap::addKeyValue(string k, string v) {
	//cout << "addKeyValue(): " << k << endl;
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

}

int hashMap::calcHash2(string k) {
	//rolling hash

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
			hash = ((int)k[i] + 11*hash) % mapSize;
		}
	}
	else {//odd
		for (int i = 0; i < len; i++) {
			hash = ((int)k[i] + 37 * hash) % mapSize;
		}
	}
	return hash;

}
void hashMap::getClosestPrime() {
	int primes [175]= {2,3,5,7,11,13,17,19,23,29,31,37,41,43,47,53,59,61,67,71,73,79,83,89,97,101,103,107,109,113,127,131,137,139,149,151,151,157,163,167,173,179,181,191,193,197,199,211,223,227,229,233,239,241,251,257,263,269,271,277,281,283,293,307,311,313,317,331,337,347,349,353,359,367,373,379,383,389,397,401,409,419,421,431,433,439,443,449,457,461,463,467,479,487,491,499,503,509,521,523,541,547,557,563,569,571,577,587,593,599,601,607,613,617,619,631,641,643,647,653,659,661,673,677,683,691,701,709,719,727,733,739,743,751,757,761,769,773,787,797,809,811,821,823,827,829,839,853,857,863,877,881,883,887,907,911,919,929,937,941,947,953,967,971,977,983,991,997,1001}; //add more primes later
	int len = sizeof(primes)/sizeof(primes[0]); //high
	int middle = (len)/2;
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
	// double hashing , adding half the aski value, do i have to use i for iterating through index? or can i not since it's already used?

	int len = k.length();
	//int h = 0;
	for (int j = 0; map[h%mapSize] != NULL && map[h%mapSize]->keyword != k; j++){
		for(i= 0; i<len;i++){
			h = h + int(k[i])/2;
		}
		//h = h %13;
		collisions++;
	}
	collisions--;
	return h%mapSize;
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
