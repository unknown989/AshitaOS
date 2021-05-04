#include "types.h"


void cprintf( int colour, const char *str )
{
    volatile int8_t *videoMemory = (volatile int8_t*)0xb8000;
    while( *str != 0){
        *videoMemory++ = *str++;
        *videoMemory++ = colour;
    }
}

void printf(char* str){
    uint16_t* videoMemory = (uint16_t *) 0xb8000;
    for(int i =0;str[i] !='\0';i++){
        videoMemory[i] = (videoMemory[i]& 0xFF00) | str[i];
    }
}


extern "C" void kmain(void* multiboot_struct,uint32_t magic){

    cprintf(LIGHT_BLUE,"Ashita OS - Kernel Version : 0.0 Alpha");

    while(1);
    
}
