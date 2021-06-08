#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include "types.h"

#define TABSIZE 4

const size_t VGA_WIDTH = 80;
const size_t VGA_HEIGHT = 45;

volatile int8_t* videoMemory = (volatile int8_t*)0xb8000;

unsigned int x = 0,y = 0;

// END
// stdio.h
// Get a char* length
size_t strlen(char* str){
	size_t len = 0;
	while(str[len]){
		len++;
	}
	return len;
}
//
// Print a character to the bios terminal
void puts(char c,unsigned int color){
	int index = 2*(y * VGA_WIDTH + x);
	volatile int8_t *vm =  videoMemory + index;
	*vm++ = c;
	*vm++ = color;
	x++;

}
// Clear the screen
void clear_screen(){
	volatile int8_t *vm =  videoMemory;
	for(unsigned int i = 0; i <= VGA_HEIGHT*VGA_WIDTH*2;i++){
		*vm++ =' ';
		*vm++ = BLACK;
	}
}
// Print to the screen with a specific foreground color
void dbg_printf(char* str,unsigned int color){
	for(size_t i = 0;i <= strlen(str);i++){
		if(str[i] == '\t')
			x += TABSIZE;
		else if(str[i] == '\n'){			
			x = -1;
			y++;
		}

		else
			puts(str[i],color);
	}
}
// Print to the screen a regular text with a regular color (WHITE)
void printf(char* str){
	dbg_printf(str,WHITE);
}

// Main kernel function where magic happens
extern "C" void kmain(void* multiboot_struct,uint32_t magic){
	clear_screen();
	dbg_printf((char*)"Ashita OS - Kernel Version : 0.1.0 Alpha\n\t",RED);
	printf((char*)"Hello From Kernel");
	while(1);
}
