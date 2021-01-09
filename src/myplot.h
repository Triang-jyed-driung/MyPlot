#ifndef _MYPLOT_H
#define _MYPLOT_H


#include "bmpheader.h"
class MyPlot
{
	private:
		
	bitmapheader header;
	COL* colors=0;
	bool fontdata[128][5][3]={};
	COL Rval=0,Gval=0,Bval=0,Alpha=255,error=0;
	
	int origX=0,origY=0,ratio=1;
	bool use3D=0,errorbool=0;
	bool* filldata=0;
	double rxx,rxy,ryx,ryy,rzx,rzy;
	int xdir,ydir;
	
	public:
		
	MyPlot(void); 
	MyPlot(int,int); 
	void initheader(int w,int h);
	void initfont();
	void init3D();
	
	void setcolor(COL r1,COL g1,COL b1,COL a1);
	COL & pixel(int x,int y,COL c);
	bool & fillinfo(int x,int y);
	void drawpixel(int x,int y);
	
	void line(int x1,int y1,int x2,int y2);
	bool fillline(int x1,int y1,int x2,int y2);
	void fillpolygon(int x1,int y1, int x2,int y2, 
	                 int x3,int y3, int x4,int y4);
	void drawtext(const char* text,int x,int y);
	void drawaxis();

	void createCanvas(int width, int height, int origX, int origY, int ratio, bool axis);
	void createCanvas3D(
		int width, int height,
		int origX, int origY,
		double rxx, double rxy,
		double ryx, double ryy,
		double rzx, double rzy);

	void plot2D(
	double (*func)(double),
	double minX, double maxX,
	int color);
	void plotPara(
		double (*funcX)(double), double (*funcY)(double),
		double minT, double maxT,
		int color);
	void plot3D(
		double(*func)(double,double),
		double minX,double maxX,double minY,double maxY);
	void saveCanvas(const char* const);
};


#endif

