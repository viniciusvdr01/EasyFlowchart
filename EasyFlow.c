
#include "EasyFlow.h"

static globals flowchart = { .block_num =1
};


void bootFlow(void)
{
  	
  printf(" ****************************************************************** \n"); 
  printf(" |                     EasyFlowchart                              | \n");  
  printf(" |                                                                | \n");
  printf(" |  Author: Vinicius Vasconcelos          Date: February 2023     | \n");
  printf(" |                                                                | \n");
  printf(" |  Based on FluxoC: WRKits                                       | \n");
  printf(" ****************************************************************** \n"); 
  printf(" Enter with the title of you flowchart: ");
  gets(flowchart.title);
  system("CLS");
    	
}


void menu(void)
{
    char opt = 0;
    
	drawInitBlock();
	
	do
	{
		
		printf("1 - Add a input/output block (parallelogram)\n");
		printf("2 - Add a process block (rectangle)\n");
		printf("3 - Add a conditional block (losangle) \n");
		printf("4 - Add a end block\n");
		printf("5 - Undo last block\n");
		printf("6 - Erase all flowchart\n");
		printf("0 - Exit (All will be lost)\n");
		printf("Select the block to be drawn: ");
		gets(&opt);
		
	switch(opt)
	{
		case '1' : drawInOut();
		break;
		case '2' : drawProcess();
		break;
		case '3' : drawConditional();
		break;
		case '4' : drawEnd();
		break;
		case '5' : undo();
		break;
		case '6' : eraseAll();
		break;
		default : printf("Invalid option!\n"); /// add a clear back
		break;
	}
	
	}while(opt != '0');

}


void drawInitBlock(void)
{
	
  printf("  ******************************************************* \n");   
  printf("              FLOWCHART %s          \n",flowchart.title);
  printf("                       -------------         \n");
  printf("                      (   Begin    )        \n");
  printf("                       -------------         \n");
	
}


void drawInOut(void)
{
  
  char s[20];
  
  printf("In/Out block text : ");
  gets(s);
  flowchart.position += 5;
  cls(flowchart.position);
  
  printf("                             |               \n");
  printf("                             v   blk%.2d     \n",flowchart.block_num);
  printf("                       /-------------/       \n");
  printf("                      / %s                   \n",s);
  printf("                     /-------------/         \n");
  
  flowchart.last_block_dummy = 0;
  flowchart.block_num ++;
  
}

void drawProcess(void)
{
	char s[20];
	register int i=0;
    printf("Process block text: ");
	gets(s);	
	
	flowchart.position += 5;
	cls(flowchart.position);
	
  printf("                             |               \n");
  printf("                             v   blk%.2d     \n",flowchart.block_num);
  printf("                       |------------|        \n");
  printf("                       | %s         ",s);
  for( i= 0; i <strlen(s); i++)
  {
  	printf("\b");
  }
  printf("|\n");
  printf("                       |------------|        \n");
  
  flowchart.last_block_dummy = 0;
  flowchart.block_num++;
  
	
}

void drawConditional(void)
{
	char s[20],branch_text[20],flux_text[20],flux,branch;
 
  register i;
  printf("Conditional block text: ");  
         
  gets(s);
  
  printf("Flux deviates at: ");                  
  gets(&branch);    
                               
  printf("Flux continues at:  ");                
  gets(&flux);                                    

  flowchart.position+=5;                                    
  cls(flowchart.position);                                  
     
  printf("                             |                    \n");
  printf("                             v   blk%.2d          \n",flowchart.block_num);
  printf("                             -                    \n");
  printf("                       / %s                       \n",s);
  printf("                      <            > - %c ------     \n",branch);
  printf("                       \\          /            | \n");
  printf("                             -                 |  \n");
  printf("                             %c                 | \n",flux);
  printf("\n\n");
  

  flowchart.block_num++;
  flowchart.block_cond  = flowchart.block_num+1;
  
  printf("Text at flux %c : ",flux);
  gets(flux_text);
  
  printf("Text at branch %c: ",branch);
  gets(branch_text);
  
  flowchart.position +=8;
  cls(flowchart.position);

  
  printf("                             |                 |            \n");
  printf("                             v   blk%.2d         v   blk%.2d          \n",flowchart.block_num,flowchart.block_cond);
  printf("                       |------------|    |------------|   \n");
  printf("                       |%s                 ",flux_text);
  
  for(i = 0; i < strlen(flux_text); i++)
  printf("\b");
  
  printf("|%s \n",branch_text); 
  
  printf("                       |------------|    |------------|   \n");
  printf("\n");
  
  flowchart.last_block_dummy = 1;
  flowchart.block_num++;
 
  
}


void drawEnd(void)
{
	flowchart.position+=5;
	cls(flowchart.position);
	
	
  printf("                             |               \n");
  printf("                             v               \n");
  printf("                       -------------         \n");
  printf("                      (     end    )        \n");
  printf("                       -------------         \n");
    
    flowchart.last_block_dummy = 0;
	flowchart.block_num++;
	
}


void undo(void)
{
    if(flowchart.last_block_dummy)
    {    
    	flowchart.position -= 8;
    	cls(flowchart.position);
    	flowchart.position=0;
    	flowchart.block_num--;
    	
	}
	else
	{
	     cls(flowchart.position);
	     flowchart.position=0;
	     flowchart.block_num--;

	}
	    	

}

void eraseAll(void)
{
  
  flowchart.position = 5;
  cls(flowchart.position);	
  flowchart.position=0;
  flowchart.block_num = 1;
}



void cls(int lines)
{
	COORD coordScreen = {0,lines}; // X and Y Colum 0, Y line
	DWORD cCharsWritten;           
	CONSOLE_SCREEN_BUFFER_INFO csbi;  // screen buffer information (size, color , format..)
	DWORD dwConSize;                   // window size to be writen
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE); // Console handle
	GetConsoleScreenBufferInfo(hConsole,&csbi);        // get console screen buffer information
	dwConSize = csbi.dwSize.X * csbi.dwSize.Y;         // calculate the window size 
	
	FillConsoleOutputCharacter(hConsole,TEXT(' '),dwConSize,coordScreen,&cCharsWritten);   // clear window where is specified
	 
	GetConsoleScreenBufferInfo(hConsole, &csbi);  // get the information of the screen buffer after the clean
	
	FillConsoleOutputAttribute(hConsole,csbi.wAttributes,dwConSize,coordScreen,&cCharsWritten); // fill the color attributes
	
    SetConsoleCursorPosition(hConsole,coordScreen); // set the cursor coordinates to the place where the new block will be drawn

	
}
