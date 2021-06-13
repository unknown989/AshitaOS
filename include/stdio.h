#ifndef STDIO
#define STDIO

#include <stddef.h>
// Get length of a string (aka char*)
size_t strlen(char* str){
	size_t len = 0;
	while(str[len]){
		len++;
	}
	return len;
}

#endif
