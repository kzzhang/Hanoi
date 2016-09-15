/**********************************
*          Kevin Zhang            *
*   Towers of Hanoi Visualization *
*            ICS4U                *
**********************************/
//This version allows for both manual and automatic completion. Note that 
//recursive automatic completion is only available when no moves have
//been made yet.

//declare includes
#include <iostream>
#include <allegro.h>
#include "tower.h"
#include <sstream>
#include "apstring.h"
#include "apstring.cpp"
#include <time.h>
#include "apvector.h"

//define colour variables
#define black makecol(0, 0, 0)
#define white makecol(255,255,255)
#define red makecol(255, 0, 0)
#define green makecol(0, 255, 0)
#define blue makecol(0, 0, 255)
#define yellow makecol(255, 255, 0)
#define orange makecol(255, 125, 0)
#define cyan makecol(0, 255, 255)
#define purple makecol(255, 0, 255)
#define pink makecol(255, 128, 128)
#define liblue makecol(128, 128, 255)
#define brown makecol(150, 100, 50)
#define grey makecol(192, 192, 192)


using namespace std;

//prototype functions
void printBackground(BITMAP *n, int m, int length);
void printVariables(int m, int n, BITMAP *q);
void printRing(ring *n, BITMAP *m, int x, int y);
void makeRing(ring *n, tower &test, apvector<int> &col);
void checkStatus(BITMAP *n, tower test, int status, int length);
void hanoi(int length, tower &a, tower &b, tower &c, int &time, BITMAP *n, int rings);
int mouseDown();

//declare globals
tower a(1), b(2), c(3);
int ringSize;
int completion = 1;

int main(int argc, char *argv[]){
	
	int rings = 3, moves = 0, clicked = 0, mouse = 1;
	//pointer wrappers for functions
	ring *sample = new ring;
	tower *container = new tower;
	
	//customize number of rings
	cout << "Enter number of rings (3-7): \n"; //limitation in size due to graphical area available on screen
	cin >> rings;
	if (rings > 7) rings = 7;
	if (rings < 3) rings = 3;
	ringSize = rings;
	
	//initialize allegro
	allegro_init(); 
    install_keyboard();
    install_mouse();
    set_color_depth(16);
	set_gfx_mode(GFX_AUTODETECT_WINDOWED, 640, 480, 0, 0);
    set_window_title("Towers of Hanoi");

	srand(time(NULL));
	
	BITMAP *buffer = create_bitmap(640, 480);
	
	//initialize possible colours
	apvector<int> colours(10);
	colours[0] = red;
	colours[1] = green;
	colours[2] = blue;
	colours[3] = yellow;
	colours[4] = orange;
	colours[5] = cyan;
	colours[6] = purple;
	colours[7] = pink;
	colours[8] = liblue;
	colours[9] = black;
	
	//create appropriate number of rings
	for (int i = 0; i < rings; i++){
		makeRing(sample, a, colours);
		sample = new ring;
	}
	
	while(!key[KEY_ESC]) {
		clear_bitmap(buffer);
		show_mouse(screen); //displays mouse
		
		//check where initial click is, return status if click is over tower or automatic button
		if (mouseDown() && mouse == 1 && completion == 1){
			if (mouse_x >= 30 && mouse_x <= 210){
				if(mouse_y >= 120 && mouse_y <= 420){
					clicked = 1;
				}
			}
			if (mouse_x >= 220 && mouse_x <= 400){
				if(mouse_y >= 120 && mouse_y <= 420){
					clicked = 2;
				}
			}
			if (mouse_x >= 400 && mouse_x <= 580){
				if(mouse_y >= 120 && mouse_y <= 420){
					clicked = 3;
				}
			}
			//automatic button
			if (mouse_x >= 440 && mouse_x <= 600){
				if(mouse_y >= 20 && mouse_y <= 60){
					clicked = 4;
				}
			}
			mouse = 0;
		}
		
		//print background, towers, and rings
		printBackground(buffer, clicked, moves);
		//print score and number rings
		printVariables(rings, moves, buffer);
		
		//check for mouse position if mouse click is held down and draw ring (if available) being moved to mouse
		if (mouseDown() && clicked != 0 && completion == 1){
			switch (clicked){
				case 1:
					if (a.getTop()) printRing(a.getTop(), buffer, mouse_x, mouse_y);
					else clicked = 0;
					break;
				case 2:
					if (b.getTop()) printRing(b.getTop(), buffer, mouse_x, mouse_y);
					else clicked = 0;
					break;
				case 3:
					if (c.getTop()) printRing(c.getTop(), buffer, mouse_x, mouse_y);
					else clicked = 0;
					break;
			} 
		}
		
		//check for release of mouse click and apply appropriate action (e.g. move rings, start Hanoi recursive function
		if (!mouseDown() && mouse == 0 && completion == 1) {
			//move ring from tower a 
			if (clicked == 1){
				if (mouse_x >= 220 && mouse_x <= 400){
					if(mouse_y >= 120 && mouse_y <= 420){
						container = &b;
						a.move(container, moves);
					}
				}
				else if (mouse_x >= 400 && mouse_x <= 580){
					if(mouse_y >= 120 && mouse_y <= 420){
						container = &c;
						a.move(container, moves);
					}
				}
			}
			//move ring from tower b
			else if (clicked == 2){
				if (mouse_x >= 30 && mouse_x <= 210){
					if(mouse_y >= 120 && mouse_y <= 420){
						container = &a;
						b.move(container, moves);
					}
				}
				else if (mouse_x >= 400 && mouse_x <= 580){
					if(mouse_y >= 120 && mouse_y <= 420){
						container = &c;
						b.move(container, moves);
					}
				}
			}
			//move ring from tower c
			else if (clicked == 3){
				if (mouse_x >= 30 && mouse_x <= 210){
					if(mouse_y >= 120 && mouse_y <= 420){
					 	container = &a;
						c.move(container, moves);
					}
				}
				if (mouse_x >= 220 && mouse_x <= 400){
					if(mouse_y >= 120 && mouse_y <= 420){
						container = &b;
						c.move(container, moves);
					}
				}
			}
			//begin Hanoi function
			else if (clicked == 4 && moves == 0){
				if (mouse_x >= 440 && mouse_x <= 600){
					if(mouse_y >= 20 && mouse_y <= 60){
						hanoi(rings, a, c, b, moves, buffer, rings);
					}
				}
			}
			clicked = 0;
			mouse = 1;
		}
		checkStatus(screen, c, rings, moves); //check for competion
    	blit(buffer, screen, 0,0,0,0,640,480); //blit updated bitmap to screen
    }
	show_mouse(NULL);
    destroy_bitmap(buffer);
    delete sample;
	return 0;
}

END_OF_MAIN();

//prints background, tower, rings, and solution button
void printBackground(BITMAP *n, int m, int length){
	rectfill(n, 0, 0, 640, 480, grey);
	rectfill(n, 50, 420, 590, 480, brown);
	a.print(120, 420, n, m);
	b.print(310, 420, n, m);
	c.print(490, 420, n, m);
	
	if (length == 0){
		rectfill(n, 440, 20, 600, 60, liblue);
		textprintf_ex(n, font, 450, 35, white, -1, "Automatic Solution");
	}
}

//prints dynamic text (# rings and moves)
void printVariables(int m, int n, BITMAP *q){
	textprintf_ex(q, font, 10, 10, white, -1, "Number of rings: %d", m);
	textprintf_ex(q, font, 10, 25, white, -1, "Number of moves: %d", n);
}

//prints ring to buffer based on mouse position
void printRing(ring *n, BITMAP *m, int x, int y){
	rectfill(m, x+10-(n->size*15), y-15, x+10+(n->size*15), y+10, n->colour);
}

//creates ring object and assigns it to tower
void makeRing(ring *n, tower &test, apvector<int> &col){
	int i = rand()%10;
	while (col[i] == -1){
		i = rand()%10;
	}
	n->colour=col[i];
	n->size = ringSize;
	ringSize -= 1;
	col[i] = -1;
	test.push(n);
}

//check for completion and prompt accordingly
void checkStatus(BITMAP *n, tower test, int status, int length){
	if (test.getQuant() == status){
		if (completion == 1){
			cout << "\n\n|~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~|\n";
			cout << "| The Towers of Hanoi have been solved! |\n";
			cout << "|                                       |\n";
			cout << " ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ \n\n";
			cout << "It took " << length << " moves.\n";
			cout << "Restart the program to try again!\n";
		}
		completion = 0;
	}
}

//Hanoi recursive function
void hanoi(int length, tower &a, tower &b, tower &c, int &time, BITMAP *n, int rings){
	tower *wrapper = new tower;
	//base case
	if (length>0){
		hanoi(length-1, a, c, b, time, n, rings); //move n-1 rings from a to c through b
		
		//move ring and update screen (includes delay)
		clear_bitmap(n);
		show_mouse(screen);
		
		wrapper = &b;
		a.move(wrapper, time);

		printBackground(n, 0, time);
		printVariables(rings, time, n);
		rest(500);
		blit(n, screen, 0,0,0,0,640,480);
		
		hanoi(length-1, c, b, a, time, n, rings); //move n-1 rings from c to b through a
	}
}

//check if mouse down
int mouseDown(){
	if (mouse_b & 0 || mouse_b & 1 || mouse_b & 2) return 1;
	else return 0;
}
