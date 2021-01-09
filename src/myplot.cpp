#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<cfloat>
#include "myplot.h" 
#define abs(_x) ((_x)>0?(_x):-(_x))
#define sgn(_x) ((_x)>0?1:(_x)==0?0:-1)
#define rev(_a) ((_a)=!(_a))
#define m(_a,_b) if((_a)>(_b))(_a)=(_b)
#define M(_a,_b) if((_a)<(_b))(_a)=(_b)
#define Bound 1000000
using namespace std;
void MyPlot::initheader(int w,int h)
{
	header.width=w;
	header.height=h;
	header.remainsize=3*w*h;
	header.filesize=3*w*h+54;
	
	colors=new COL[3*w*h];
	memset(colors,-1,header.remainsize);
	Rval=Gval=Bval=0,Alpha=255;
}
void MyPlot::initfont()
{
	FILE* f=fopen("font.txt","r");
	if(!f)
	{
		printf("找不到font.txt，因此无法显示数字\n");
		return;
	}
	int n,t,i,j;
	char c[3];
	fscanf(f,"%d",&n);
	while(n--)
	{
		fscanf(f,"%s",c);
		for(i=0;i<5;i++)
			for(j=0;j<3;j++)
				fscanf(f,"%1d",&t),
				fontdata[*c][i][j]=t;
	}
	fclose(f);
}
void MyPlot::init3D()
{
	use3D=1;
	filldata=new bool[header.height*header.width];
}


MyPlot::MyPlot()
{
	initheader(0,0);
	initfont();
}
MyPlot::MyPlot(int w,int h)
{
	initheader(w,h);
	initfont();
}




void MyPlot::setcolor(COL r1,COL g1,COL b1,COL a1){
	Rval=r1,Gval=g1,Bval=b1,Alpha=a1;
}
COL& MyPlot::pixel(int x,int y,COL c){
	return (x>=0&&x<header.width && y>=0&&y<header.height && c>=0&&c<=2) ?
	        colors[(y*header.width+x)*3+c] : error;
}
bool& MyPlot::fillinfo(int x,int y){
	return (x>=0&&x<header.width && y>=0&&y<header.height) ?
	        filldata[y*header.width+x] : errorbool;
}
void MyPlot::drawpixel(int x,int y)
{
	if(x>=0&&x<header.width && y>=0&&y<header.height)
	{
		colors[(y*header.width+x)*3+2]=
		((int)colors[(y*header.width+x)*3+2]*(255-Alpha)+(int)Alpha*Rval)/255;
		colors[(y*header.width+x)*3+1]=
		((int)colors[(y*header.width+x)*3+1]*(255-Alpha)+(int)Alpha*Gval)/255;
		colors[(y*header.width+x)*3+0]=
		((int)colors[(y*header.width+x)*3+0]*(255-Alpha)+(int)Alpha*Bval)/255;
	}
}
void MyPlot::line(int x1,int y1,int x2,int y2)
{
	if(x1<-Bound||x1>Bound||x2<-Bound||x2>Bound
	|| y1<-Bound||y1>Bound||y2<-Bound||y2>Bound)
		return;
	if(x1!=x2||y1!=y2)
	{
		int dx=sgn(x2-x1),dy=sgn(y2-y1),deltax=abs(x2-x1),deltay=abs(y2-y1),
			x,y;
		if(deltax>=deltay)
		{
			for(x=x1;x!=x2;x+=dx)
			{
				y=((x2-x)*y1+(x-x1)*y2+(x2-x1)/2)/(x2-x1);
				drawpixel(x,y);
			}
		}
		else
		{
			for(y=y1;y!=y2;y+=dy)
			{
				x=((y2-y)*x1+(y-y1)*x2+(y2-y1)/2)/(y2-y1);
				drawpixel(x,y);
			}
		}
	}
	drawpixel(x2,y2);
}

bool MyPlot::fillline(int x1,int y1,int x2,int y2)
{
	if(x1<-Bound||x1>Bound||x2<-Bound||x2>Bound
	|| y1<-Bound||y1>Bound||y2<-Bound||y2>Bound
	|| !use3D)
		return 0;
	if(y1==y2)
		return 1;
	if(y1>y2)
		x1^=x2^=x1^=x2,y1^=y2^=y1^=y2;
	int x,y;
	for(y=y1;y!=y2;y++)
	{
		x=((y2-y)*x1+(y-y1)*x2+(y2-y1)/2)/(y2-y1);
		rev(fillinfo(x,y));
	}
	return 1;
}

void MyPlot::fillpolygon(int x1,int y1, int x2,int y2, 
                 int x3,int y3, int x4,int y4)
{
	if(!fillline(x1,y1,x2,y2))return;
	if(!fillline(x2,y2,x3,y3))return;
	if(!fillline(x3,y3,x4,y4))return;
	if(!fillline(x4,y4,x1,y1))return;
	//printf("ok\n");
	int xmin=header.width,xmax=0,
	    ymin=header.height,ymax=0;
	m(xmin,x1);m(xmin,x2);m(xmin,x3);m(xmin,x4);
	M(xmax,x1);M(xmax,x2);M(xmax,x3);M(xmax,x4);
	m(ymin,y1);m(ymin,y2);m(ymin,y3);m(ymin,y4);
	M(ymax,y1);M(ymax,y2);M(ymax,y3);M(ymax,y4);
	M(xmin,0);M(ymin,0);
	m(xmax,header.width); m(ymax,header.height);
	int x,y;
	bool fill=0;
	COL r1=Rval,g1=Gval,b1=Bval;
	setcolor(255,255,255,Alpha);
	for(y=ymin;y<=ymax;y++)
	{
		fill=0;
		for(x=xmin;x<=xmax;x++)
		{
			fill^=fillinfo(x,y);
			if(fill)
				drawpixel(x,y);
		}
	}
	//////////
	memset(filldata,0,header.width*header.height);
	setcolor(r1,g1,b1,Alpha);
	line(x1,y1,x2,y2);
	line(x2,y2,x3,y3);
	line(x3,y3,x4,y4);
	line(x4,y4,x1,y1);
}
void MyPlot::drawtext(const char* text,int x,int y)
{
	int dx,dy;
	for(;*text;text++,x+=4)
		for(dy=0;dy<5;dy++)
			for(dx=0;dx<3;dx++)
				if(fontdata[*text][dy][dx])
					drawpixel(x+dx,y-dy);
}
void MyPlot::drawaxis()
{
	line(0,origY, header.width,origY);
	line(origX,0, origX,header.height);
	line(header.width-1,origY, header.width-4,origY+3);
	line(header.width-1,origY, header.width-4,origY-3);
	line(origX,header.height-1, origX+3,header.height-4);
	line(origX,header.height-1, origX-3,header.height-4);
	
	char temp[10];
	int i;
	drawtext("0",origX-7,origY-3);
	for(i=1;i*ratio<header.width;i++)
	{
		line(origX+i*ratio,origY-1, origX+i*ratio,origY+1);
		sprintf(temp,"%d",i);
		drawtext(temp,origX+i*ratio-5,origY-4);
		line(origX-i*ratio,origY-1, origX-i*ratio,origY+1);
		sprintf(temp,"%d",-i);
		drawtext(temp,origX-i*ratio-5,origY-4);
	}
	for(i=1;i*ratio<header.height;i++)
	{
		line(origX-1,origY+i*ratio, origX+1,origY+i*ratio);
		sprintf(temp,"%d",i);
		drawtext(temp,origX+3,origY+i*ratio+2);
		line(origX-1,origY-i*ratio, origX+1,origY-i*ratio);
		sprintf(temp,"%d",-i);
		drawtext(temp,origX+3,origY-i*ratio+2);
	}
} 
void MyPlot::createCanvas(int width, int height, int origX, int origY, int ratio, bool axis)
{
	initheader(width,height);
	initfont();
	this->origX=origX;
	this->origY=origY;
	this->ratio=ratio;
	if(axis)
		drawaxis();
}
void MyPlot::createCanvas3D(
	int width, int height,
	int origX, int origY,
	double rxx, double rxy,
	double ryx, double ryy,
	double rzx, double rzy)
{
	initheader(width,height);
	init3D();
	this->origX=origX;
	this->origY=origY;
	this->rxx=rxx;
	this->rxy=rxy;
	this->ryx=ryx;
	this->ryy=ryy;
	this->rzx=rzx;
	this->rzy=rzy;
	int sgn1=sgn(rxx*ryy-rxy*ryx);
	int sgnx=-sgn(rxx*rzx+rxy*rzy);
	int sgny=-sgn(ryx*rzx+ryy*rzy);
	xdir=sgn1*sgnx,ydir=sgn1*sgny;
	if(xdir==0)xdir=1;
	if(ydir==0)ydir=1;
	//printf("%d,%d\n",xdir,ydir);
}



void MyPlot::plot2D(
	double (*func)(double),
	double minX, double maxX,
	int color)
{
	Bval=(color&0xff0000)>>16;
	Gval=(color&0x00ff00)>>8;
	Rval=(color&0x0000ff);
	Alpha=255;
	//先把minx、maxx换算成整数
	int xmin=round(minX*ratio+origX);
	int xmax=round(maxX*ratio+origX);
	
	//反过来
	int i,y1,y2=round(func(double(xmin-origX)/ratio)*ratio+origY);
	for(i=xmin;i<xmax;i++)
	{
		y1=y2;//func(double(i-origx)/ratio)*ratio+origY;
		y2=round(func(double(i+1-origX)/ratio)*ratio+origY);
		//printf("%d %d %d %d\n",i,y1,i+1,y2);
		line(i,y1,i+1,y2);
	} 
}

void MyPlot::plotPara(
	double (*funcX)(double), double (*funcY)(double),
	double minT, double maxT,
	int color)
{
	int steps=1000;
	double inc=(maxT-minT)/steps,t;
	int x1,x2=round(funcX(minT)*ratio+origX),
	    y1,y2=round(funcY(maxT)*ratio+origY);
	Bval=(color&0xff0000)>>16;
	Gval=(color&0x00ff00)>>8;
	Rval=(color&0x00ff00);
	
	for(t=minT;t<maxT;t+=inc)
	{
		x1=x2,y1=y2;
		x2=round(funcX(t+inc)*ratio+origX);
		y2=round(funcY(t+inc)*ratio+origY);
		line(x1,y1,x2,y2);
	}
}
	
void MyPlot::plot3D(
	double(*func)(double,double),
	double minX,double maxX,double minY,double maxY)
{
	int unit=50,i,j;//unit*unit grid
	double (*a)[105]=new double[unit+1][105];
	double maxz=-DBL_MAX,minz=DBL_MAX;
	int (*b)[105][2]=new int[unit+1][105][2];
	double tx=0,ty=0,tz=0,colindex;
	for(i=0;i<=unit;i++)
		for(j=0;j<=unit;j++)
		{
			tx=((unit-i)*minX+(i)*maxX)/unit;
			ty=((unit-j)*minY+(j)*maxY)/unit;
			a[i][j]=tz=func(tx,ty);
			M(maxz,tz); m(minz,tz);
			b[i][j][0]=origX+rxx*tx+ryx*ty+rzx*tz;
			b[i][j][1]=origY+rxy*tx+ryy*ty+rzy*tz;
		}
	int x1=(xdir>0?0:unit-1),x2=(xdir>0?unit:-1),
	    y1=(ydir>0?0:unit-1),y2=(ydir>0?unit:-1);
	if(maxz<=minz) maxz+=1,minz-=1;
	for(i=x1;i!=x2;i+=xdir)
		for(j=y1;j!=y2;j+=ydir)
		{
			colindex=(maxz-a[i][j])/(maxz-minz);
			setcolor( 
				colindex<0.4?255*(1-6.25*colindex*colindex):
				colindex>0.8?600*(colindex-0.8):0,//R
			 	colindex<0.8?255*(1-6.25*(0.4-colindex)*(0.4-colindex)):0,//G
				colindex>0.4?255*(1-6.25*(0.8-colindex)*(0.8-colindex)):0,//B
				Alpha);
			fillpolygon(
			b[i][j][0],b[i][j][1],
			b[i+1][j][0],b[i+1][j][1],
			b[i+1][j+1][0],b[i+1][j+1][1],
			b[i][j+1][0],b[i][j+1][1]);
		}
	delete[] a;
	delete[] b;
}
void MyPlot::saveCanvas(const char* const name)
{
	FILE* f = fopen(name,"wb");
	fwrite(&header,sizeof(header),1,f);
	fwrite(colors,header.remainsize,1,f);
	fclose(f);
}
