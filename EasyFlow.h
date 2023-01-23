#ifndef EasyFlow
#define EasyFlow


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>



void bootFlow(void);
void drawInitBlock(void);
void menu(void);
void cls(int lines);

void drawInOut(void);
void drawProcess(void);
void drawConditional(void);
void drawEnd(void);

void undo(void);
void eraseAll(void);
 
typedef struct
{
	char title[50];
	int   position;
	int   block_num;
	int   block_cond;
    int last_block_dummy;
}globals;



#endif
