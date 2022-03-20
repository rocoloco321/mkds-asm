#include<nds.h>

#ifndef _MSG_H_
#define _MSG_H_

void MSG_Init(int x, int y, int palette, int color, uint32_t flags);
void MSG_SetText(char* text);
void MSG_ClearText();
void MSG_UpdateText();

#endif