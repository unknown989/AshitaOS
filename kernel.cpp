#include "types.h"

static int c = 0;

void printf(char* str){
    uint16_t* videoMemory = (uint16_t *) 0xb8000;
    for(int i =0;str[i] !='\0';i++){
        videoMemory[c] = (videoMemory[i]& 0xFF00) | str[i];
    	c++;
    }
}
void cprintf(char* str,int32_t color){
    uint16_t* videoMemory = (uint16_t *) 0xb8000;
    for(int i =0;str[i] !='\0';i++){
        videoMemory[c] = color | str[i];
        c++;
    }
}

extern "C" void kmain(void* multiboot_struct,uint32_t magic){

    printf((char*)"Ashita OS - Kernel Version : 0.0 Alpha");
    cprintf((char*)"Loading...",LIGHT_BLUE);

    while(1);
    
}
