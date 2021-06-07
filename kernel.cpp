#include "types.h"
#include "IO/manipulator.hpp"
#include "FS/FAT.h"
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

// Variables START
const size_t VGA_WIDTH = 80;
const size_t VGA_HEIGHT = 45;
// END

void clear_screen(){

	volatile int8_t *videoMemory = (volatile int8_t*)0xb8000;
	for(unsigned int i = 0;i <= VGA_HEIGHT*VGA_WIDTH*2;i++){
		*videoMemory++ = ' ';
		*videoMemory++ = BLACK;
	}
}
void cprintf( int colour, const char *str )
{
    volatile int8_t *videoMemory = (volatile int8_t*)0xb8000;
    unsigned int i = 0;
    // while( *str != 0){
    	// if(str == "\n"){
    		// 
    	// }
        // *videoMemory++ = *str++;
        // *videoMemory++ = colour;
    // }
    while( *str != 0){
    	if(str[i] == '\n'){
    		i += VGA_WIDTH+VGA_HEIGHT;
    	}
        videoMemory[i] = *str++;
        i++;
        videoMemory[i] = colour;
        i++;
    }
}

void printf(char* str){
    uint16_t* videoMemory = (uint16_t *) 0xb8000;
    for(int i =0;str[i] !='\0';i++){
        videoMemory[i] = (videoMemory[i]& 0xFF00) | str[i];
    }
}
void enable_cursor(uint8_t cursor_start,uint8_t cursor_end){
	outb(0x3D4,0x0A);
	outb(0x3D5,(inb(0x3D5) & 0xC0) | cursor_start);

	outb(0x3D4,0x0B);
	outb(0x3D5,(inb(0x3D5) & 0xE0) | cursor_end);	
}
void disable_cursor(){
	outb(0x3D4,0x0A);
	outb(0x3D5,0x20);
}
void move_cursor(int x,int y){
	uint16_t pos = y * VGA_WIDTH + x;
	outb(0x3D4,0x0F);
	outb(0x3D5,(uint8_t) (pos & 0xFF));
	outb(0x3D4,0x0E);
	outb(0x3D5,(uint8_t)((pos >> 8) & 0xFF));
}
uint16_t get_cursor_position(void){
	uint16_t pos = 0;
	outb(0x3D4,0x0F);
	pos |= inb(0x3D5);
	outb(0x3D4,0x0E);
	pos |= ((uint16_t)inb(0x3D5)) << 8;
	return pos;
}

extern "C" void kmain(void* multiboot_struct,uint32_t magic){
	enable_cursor(0x0,0xF);
	clear_screen();
    cprintf(LIGHT_BLUE,"Ashita OS\n - Kernel Version : 0.1 Alpha");
    move_cursor(10,4);

    while(1);
    
}
