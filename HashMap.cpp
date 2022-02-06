#include "HashMap.hpp"
#include "HashNode.hpp"
#include <iostream>
#include <math.h>
using namespace std;

hashMap::hashMap(bool hash1, bool coll1) {
	cout << "start of constructor" << endl;
	hashfn = hash1;
	collfn = coll1;
	numKeys = 0;
	hashcoll = 0;
	collisions = 0;
	mapSize = primes[0];
	cout << "before array make" << endl;
	//*map = new hashNode[mapSize];
	cout << "before loop" << endl;
	for (int i = 0; i < mapSize; i++) {
		map[i] = NULL;
	}
	cout << "end of constructor" << endl;
}

void hashMap::addKeyValue(string k, string v) {
	int hashIndex = 0;
	if (hashfn) {
		hashIndex = calcHash1(k);
	} else {
		hashIndex = calcHash2(k);
	}
	if (map[hashIndex] == NULL) {
		map[hashIndex] = new hashNode(k, v);
		numKeys++;
	} else if (map[hashIndex]->keyword == k) {
		map[hashIndex]->addValue(v);
	} else {
		hashcoll++;
		if (collfn) {
			hashIndex = coll1(hashIndex, hashcoll, k);
			if (map[hashIndex] == NULL) {
				map[hashIndex] = new hashNode(k, v);
				numKeys++;
			} else if (map[hashIndex]->keyword == k) {
				map[hashIndex]->addValue(v);
			}
		} else {
			hashIndex = coll2(hashIndex, hashcoll, k);
			if (map[hashIndex] == NULL) {
				map[hashIndex] = new hashNode(k, v);
				numKeys++;
			} else if (map[hashIndex]->keyword == k) {
				map[hashIndex]->addValue(v);
			}

		}
	}
	if ((numKeys / mapSize) >= .7) {
		reHash();
	}

}

int hashMap::getIndex(string k) {
	int hashIndex = 0;
	if (hashfn) {
		hashIndex = calcHash1(k);
	} else {
		hashIndex = calcHash2(k);
	}
	if (map[hashIndex]->keyword == k) {
		return hashIndex;
	} else {
		if (collfn) {
			return coll1(hashIndex, 0, k);
		} else {
			return coll2(hashIndex, 0, k);
		}
	}
}

int hashMap::calcHash1(string k) {
	unsigned long int hash = 0;
	for (int i = 0; i < k.length(); i++) {
		hash += k[i] * pow(2, i);
	}
	return hash % mapSize;
}

int hashMap::calcHash2(string k) {
	unsigned long int hash = 0;
	for (int i = 0; i < k.length(); i++) {
		hash += pow(k[i], i);
	}
	return hash % mapSize;
}

void hashMap::getClosestPrime() {
	int newSize = mapSize * 2;
	int end = 1204;
	int beg = 0;
	while (beg <= end) {
		int mid = beg + (end - beg) / 2;
		if (primes[mid] > newSize && primes[mid - 1] < newSize) {
			mapSize = primes[mid];
			break;
		}
		if (primes[mid] < newSize) {
			beg = mid + 1;
		} else {
			end = mid - 1;
		}
	}
}

void hashMap::reHash() {
	int oldSize = mapSize;
	getClosestPrime();
	hashNode temp[mapSize];
	for (int i = 0; i < oldSize; i++) {
		if (map[i] == NULL) {
			continue;
		}
		temp[i] = *map[i];
		map[i] = NULL;
	}
	unsigned int hash;
	for (int j = 0; j < oldSize; j++) {
		if (&temp[j] == NULL)
			continue;
		hash = 0;
		if (hashfn) {
			hash = calcHash1(temp[j].keyword);
			if (map[hash] != NULL) {
				if (collfn) {
					hash = coll1(hash, 0, temp[j].keyword);
				} else {
					hash = coll2(hash, 0, temp[j].keyword);
				}
			}
		} else {
			hash = calcHash2(temp[j].keyword);
			if (map[hash] != NULL) {
				if (collfn) {
					hash = coll1(hash, 0, temp[j].keyword);
				} else {
					hash = coll2(hash, 0, temp[j].keyword);
				}
			}
		}
		map[hash] = temp;
	}
}

int hashMap::coll1(int h, int i, string k) {
	/*
	 i = h;
	 h++;
	 while (h != i) {
	 if (h > mapSize) {
	 h = 0;
	 }
	 if (map[h] == NULL) {
	 return h;
	 } else if (map[h]->keyword == k) {
	 return h;
	 }
	 h++;
	 }
	 return -1;
	 */
	h++;
	if (h >= mapSize) {
		h = 0;
	}
	if (map[h] == NULL) {
		return h;
	} else if (map[h]->keyword == k) {
		return h;
	} else {
		i++;
		coll1(h, i, k);
	}
	return -1;

}

int hashMap::coll2(int h, int i, string k) {
	h = h + pow(i, 2);
	if (h > mapSize) {
		h = 0;
	}
	if (map[h] == NULL) {
		return h;
	} else if (map[h]->keyword == k) {
		return h;
	} else {
		i++;
		coll2(h, i, k);
	}
	return -1;
}

void hashMap::printMap() {
	cout << "In printMap()" << endl;
	for (int i = 0; i < mapSize; i++) {
		//cout << "In loop" << endl;
		if (map[i] != NULL) {
			cout << map[i]->keyword << ": ";
			for (int j = 0; j < map[i]->currSize; j++) {
				cout << map[i]->values[j] << ", ";
			}
			cout << endl;
		}
	}
}

