#include <nds.h>
#include "mkds.h"
#include "msg.h"

typedef struct
{
	uint8_t testdata[32 * 8 * 2 * 8];
	uint16_t scrdata[64];
	NNSG2dCharCanvas canvas;
	NNSG2dTextCanvas text_canvas;
	int text_x;
	int text_y;
	int text_flags;
	int text_color;
}info_t;

static info_t* info_p;

void MSG_Init(int x, int y, int palette, int color, uint32_t flags)
{
	info_p = MKDS_Alloc(GetNNSFndHeapHandle(sub_20364E8()), sizeof(info_t));;
	info_p->text_x = x;
	info_p->text_y = y;
	info_p->text_flags = flags;
	info_p->text_color = color;
	MSG_ClearText();
	NNS_G2dCharCanvasInitForBG(&info_p->canvas, &info_p->testdata[0], 32, 2, NNS_G2D_CHARA_COLORMODE_16);
	NNS_G2dTextCanvasInit(&info_p->text_canvas, &info_p->canvas, (NNSG2dFont*)((uint32_t*)0x217B390)[2], 1, 0);
	int i;
	for(i = 0; i < 63; i++)
	{
		info_p->scrdata[i] = /*0x1000*/((palette & 0xF) << 12) | (i + 1);
	}
	MSG_UpdateText();
}

void MSG_SetTextColor(int color)
{
	info_p->text_color = color;
}

void MSG_SetText(char* text)
{
	MSG_ClearText();
	NNSi_G2dTextCanvasDrawText(&info_p->text_canvas, /*0*/240, 9, /*14*/info_p->text_color, /*0x40A*//*NNS_G2D_HORIZONTALALIGN_CENTER | NNS_G2D_HORIZONTALORIGIN_LEFT | NNS_G2D_VERTICALORIGIN_MIDDLE*/info_p->text_flags, text);
}

void MSG_ClearText()
{
	MI_CpuClearFast(info_p->testdata, 32 * 8 * 2 * 8);
}

void MSG_UpdateText()
{
	DC_FlushRange(&info_p->testdata, 32 * 8 * 2 * 8);
	DC_FlushRange(&info_p->scrdata, 64 * 2);
	BG1CNT = 0x100;
	GX_LoadBG1Char(&info_p->testdata, 32, (32 * 8 * 2 * 8) - 32);
	GX_LoadBG1Scr(&info_p->scrdata, 0, 63 * 2);
	BG1HOFS = -info_p->text_x;//-8;
	BG1VOFS = -info_p->text_y;//-160;
	DISPCNT |= 0x200;
}