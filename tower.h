#ifndef TOWER_H
#define TOWER_H
#include <iostream>
//tower class
#include "allegro.h"

//ring structure
struct ring{
	int size;
	int colour;
	ring *prev;
};

class tower{
	//protected attributes
	protected:
		ring *top;
		int quantity;
		int number;
		char name;
	//public methods
	public:
		tower();
		tower(int);
		void push(ring*);
		void setName(char);
		ring *pop();
		ring *getTop();
		int getQuant();
		void move(tower *b, int &inc);
		void print(int, int, BITMAP*, int c);
		void printTop();
		~tower();
};
#endif
