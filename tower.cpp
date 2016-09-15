//tower class methods
#include "tower.h"

using namespace std;

//empty case constructor
tower::tower(){
	quantity = 0;
	top = NULL;
}

//constructor
tower::tower(int a){
	quantity = 0;
	top = NULL;
	number = a;	
}

//add ring to top of tower
void tower::push(ring *n){
	quantity += 1;
	n->prev = top;
	top = n;
}

//remove and return ring from top of tower
ring *tower::pop(){
	quantity -= 1;
	ring *temp = top;
	top = top->prev;
	return temp;
}

//returns top ring of tower
ring *tower::getTop(){
	return top;
}

//returns number of rings on tower
int tower::getQuant(){
	return quantity;
}

//moves ring from tower to tower b and increments number of moves made
void tower::move(tower *b, int &inc){
	if (quantity > 0){
		if (!b->getTop()){
			b->push(pop());
			inc += 1;
		}
		else if (top->size < b->top->size){
			b->push(pop());
			inc += 1;
		}
	}
}

//displays tower and associated rings through allegro
//doesn't display top ring if it is currently being moved by the mouse
void tower::print(int a, int b, BITMAP *n, int c){
	rectfill(n, a, b-300, a+20, b, makecol(150, 100, 50));
	int tempq = quantity;
	ring *tempr = top;
	if (c == number){
		if (top){
			top = top->prev;
			quantity -= 1;
		}
	}
	while (top){
		rectfill(n, a+10-(top->size*15), b-(quantity*25), a+10+(top->size*15), b-((quantity-1)*25), top->colour);
		quantity -= 1;
		top = top->prev;
	}
	top = tempr;
	quantity = tempq;
}

//test function, prints stats
void tower::printTop(){
	cout << top <<endl;
	cout <<quantity<<endl;
}

//deconstructor
tower::~tower(){
}
