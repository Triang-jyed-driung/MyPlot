#ifndef _BMPHEADER_H
#define _BMPHEADER_H
#pragma pack(1)
typedef unsigned char COL; 
struct bitmapheader
{
	const char name[2]={'B','M'};
	int filesize=54;
	const int reserved1=0;
	const int headersize1=54;
	const int headersize2=40;
	int width=0;
	int height=0;
	const char reserved2[8]={0x01,0,0x18,0,0,0,0,0};
	int remainsize=0;
	const char reserved3[16]={0};
};
#endif
