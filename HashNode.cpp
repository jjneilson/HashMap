#include "HashMap.hpp"
#include <iostream>
#include <cstdlib>
#include <time.h>
using namespace std;

hashNode::hashNode(string s) {
	keyword = s;
	values = new string[100];
	valuesSize = 100;
	currSize = 0;
}
hashNode::hashNode() {
	keyword = "";
	values = new string[100];
	valuesSize = 100;
	currSize = 0;
}
hashNode::hashNode(string s, string v) {
	keyword = s;
	values = new string[100];
	values[0] = v;
	valuesSize = 100;
	currSize = 1;
}
void hashNode::addValue(string v) {
	if (currSize + 1 >= valuesSize) {
		dblArray();
	}
	values[currSize] = v;
	currSize++;
	// adding a value to the end of the value array associated
	// with a key
}

void hashNode::dblArray() {
	valuesSize = valuesSize * 2;
	string *newValues = new string[valuesSize];
	for (int i = 0; i <= currSize; i++) {
		newValues[i] = values[i];
	}
	values = newValues;
	// when the value array gets full, you need to make a new
	// array twice the size of the old one (just double, no
	//going to next prime) and then copy over the old values
	//to the new values, then de-allocate the old array.
	//Again, just copying over, no hash function involved
	//here.
}

string hashNode::getRandValue() {
	return values[rand() % currSize];
	//Every key has a values array - an array of words that
	// follow that key in the text document.  You're going to
	//randomly select one of those words and return it.  That
	//will be the word that follows your key in your output
	//function, and it will also be the next key.
}
