#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<cfloat> 
#include<cctype>
using namespace std;
#include "extend.h"
#include "myplot.h"
#include "func.h"

function* f1point;
function* f2point;
double f0(double x)
{
	f1point->x=x; 
	return f1point->calc();
}
double fx1(double t)
{
	f1point->t=t; 
	return f1point->calc();
}
double fy1(double t)
{
	f2point->t=t; 
	return f2point->calc();
}
double fxy1(double x,double y)
{
	f1point->x=x; 
	f1point->y=y; 
	return f1point->calc();
}
int main(int argc,char** argv)
{
	if(argc==1)
	{
		MyPlot bmp;
		bmp.createCanvas(800, 600, 400, 300, 50, true);
		bmp.plot2D(func1, -7, 7, 0x00FF00); 
		bmp.saveCanvas("func1.bmp");
		bmp.createCanvas(800, 600, 400, 80, 50, true);
		bmp.plot2D(func2, -3.5, 3.5, 0xFF7700); 
		bmp.saveCanvas("func2.bmp");
		bmp.createCanvas(800, 600, 400, 400, 90, false);
		bmp.plotPara(func32, func31, 0, 2*3.1416, 0xFF0000);
		bmp.saveCanvas("func3.bmp");
		bmp.createCanvas(800, 600, 400, 400, 90, true);
		bmp.plot2D(func41, -2, 2, 0x0000FF);
		bmp.plot2D(func42, -2, 2, 0x0077FF);
		bmp.saveCanvas("func4.bmp");
		bmp.createCanvas(800, 700, 400, 350, 46, true);
		bmp.plotPara(func51, func52, 0, 2*3.1416, 0x000000);
		bmp.plot2D(func41, -2, 2, 0x0000FF);
		bmp.plot2D(func42, -2, 2, 0x0077FF);
		bmp.saveCanvas("func5.bmp");
		bmp.createCanvas3D(
			800, 600, 400, 300,
			-16.175, -5.3, 24.8438, -5.375, 0, 145);
		bmp.plot3D(func6,-8,8,-8,8);
		bmp.saveCanvas("func6.bmp");
	}
	else if(argc==2)
	{	
		MyPlot bmp;
		char fun[1005]={},fun2[1005]={};
		double x1,x2,t1,t2;
		if(!strcmp(argv[1],"plot2D"))
		{
			scanf("%1000s%lf%lf",fun,&x1,&x2);
			function fx(fun);
			f1point=&fx;
			bmp.createCanvas(800, 600, 400, 300, 50, true);
			bmp.plot2D(f0, x1, x2, 0x000000); 
		}
		else if(!strcmp(argv[1],"plotPara"))
		{
			scanf("%1000s%1000s%lf%lf",fun,fun2,&t1,&t2);
			function fx(fun),fy(fun2);
			f1point=&fx;f2point=&fy;
			bmp.createCanvas(800, 600, 400, 300, 50, true);
			bmp.plotPara(fx1,fy1, t1, t2, 0x000000); 
		}
		else if(!strcmp(argv[1],"plot3D"))
		{
			scanf("%1000s%lf%lf%lf%lf",fun,&x1,&x2,&t1,&t2);
			function fxy(fun);
			f1point=&fxy;
			bmp.createCanvas3D(1600, 1200, 800, 600,120,-30,50,72,0,104);
			bmp.setcolor(0,0,0,192);
			bmp.plot3D(fxy1,x1,x2,t1,t2); 
		} 
		bmp.saveCanvas("custom.bmp");
	}
	return 0;
}

