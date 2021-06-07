#ifndef IO_MANUP_HPP
#define IO_MANUP_HPP
inline unsigned char inb(unsigned int port){
	unsigned char ret;
	asm volatile ("inb %%dx,%%al":"=a" (ret):"d" (port));
	return ret;
}

inline void outb(unsigned int port,unsigned char value){
	asm volatile ("outb %%al,%%dx": :"d" (port), "a" (value));
}
#endif
