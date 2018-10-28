#ifndef PORTS_H
#define PORTS_H

#include "../cpu/types.h"

u8 getPortByte(u16 port);
void setPortByte(u16 port, u8 data);
u16 getPortWord(u16 port);
void setPortWord(u16 port, u16 data);

#endif