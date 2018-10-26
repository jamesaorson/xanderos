#ifndef PORTS_H
#define PORTS_H

unsigned char getPortByte(unsigned short port);
void setPortByte(unsigned short port, unsigned char data);
unsigned short getPortWord(unsigned short port);
void setPortWord(unsigned short port, unsigned short data);

#endif