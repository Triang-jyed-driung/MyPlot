#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<cfloat> 
#include<cctype>
using namespace std; 
#include "extend.h" 
#define abs(_x) ((_x)>0?(_x):-(_x))
#define sgn(_x) ((_x)>0?1:(_x)==0?0:-1)



bds::bds(){l=r=NULL,sym=0,val=0,sg=0;}
bds::~bds()
{
	if(l!=NULL)delete l;
	if(r!=NULL)delete r;
}
bds* rrot(bds* p){bds*tmp=p->l;p->l=tmp->r;tmp->r=p;return tmp;}
void simplify(bds*& p1)
{
	if(p1->l->sg)return;
	if((p1->l->sym=='+'||p1->l->sym=='-')&&(p1->sym=='*'||p1->sym=='/'))p1=rrot(p1);
	if(p1->sym=='^'||p1->l->sym=='='){p1=rrot(p1);simplify(p1->r);}
}

bds* function::getsingleitem()
{
	bds* k;
    if(*strt=='+'||*strt=='-')
	{
		k=new bds;
		k->sym=*strt;
		strt++;
		if((k->r=getsingleitem())==NULL)return NULL;
		k->l=new bds;
		k->l->sg=1;
		k->sg=0;
		k->val=0;
		return k;
	}
	if((*strt>='0'&&*strt<='9')||*strt=='.')
	{
		k=new bds;
		sscanf(strt,"%lf",&(k->val));
		for(;(*strt>='0'&&*strt<='9')||*strt=='.';strt++);
	}
	else if(*strt=='(')	
    {
        strt++;
        if((k=gentree())==NULL)return NULL;
        strt++;
    }
	else if(islower(*strt))
	{
		k=new bds;
		for(sp=op;islower(*strt);*sp++=*strt++);
		*sp=0;
		if((!strcmp(op,"ln"))||(!strcmp(op,"log")))k->sym='l';
		else if(!strcmp(op,"exp"))k->sym='e';
		else if(!strcmp(op,"sin"))k->sym='s';
		else if(!strcmp(op,"cos"))k->sym='X';
		else if(!strcmp(op,"tan"))k->sym='t';
		else if((!strcmp(op,"asin"))||(!strcmp(op,"arcsin")))k->sym='S';
		else if((!strcmp(op,"acos"))||(!strcmp(op,"arccos")))k->sym='C';
		else if((!strcmp(op,"atan"))||(!strcmp(op,"arctan")))k->sym='T';
		else if(!strcmp(op,"sqrt"))k->sym='r';
		else if(!strcmp(op,"abs"))k->sym='A';
		if(!k->sym)
		{
			if(!strcmp(op,"e"))k->val=M_E,k->sg=1;
			else if(!strcmp(op,"pi"))k->val=M_PI,k->sg=1;
			else if(!strcmp(op,"t"))k->val=t,k->sym='\t',k->sg=1;
			else if(!strcmp(op,"x"))k->val=x,k->sym='x',k->sg=1;
			else if(!strcmp(op,"y"))k->val=y,k->sym='y',k->sg=1;
			else if(!strcmp(op,"z"))k->val=z,k->sym='z',k->sg=1;
			else return NULL;
		}
		else if((k->l=getsingleitem())==NULL)return NULL;
	}
	else
	{
        printf("非法字符：%c\n",*strt);
        return NULL;
    }
	k->sg=1;
	return k;
}


bds* function::gentree()
{
	bds*p1,*p2;
	p1=p2=NULL;
	if((p1=getsingleitem())==NULL)return NULL;
	while(*strt!=')'&&*strt!=0)
	{
		p2=new bds;
		p2->sym=*strt;
		if(*strt!='+'&&*strt!='-'&&*strt!='*'&&*strt!='/'&&*strt!='^'&&*strt!='=')
		{
            printf("非法字符：%c\n",*strt);
            return NULL;
        } 
		p2->l=p1;
		strt++;
		if((p2->r=getsingleitem())==NULL)return NULL;
		//p2->r=getsingleitem();
		p1=p2;
		simplify(p1);
	}
	return p1;
}
bds* function::make()
{return bd=gentree();}
double function::calc(bds* v)
{
	if(v==NULL)return NAN;
	else if(v->sym!=0)
	{
		double a1,b1;
		a1=calc(v->l);
		b1=calc(v->r);
		char c1=v->sym;
		switch(c1)
		{
			case'+':return a1+b1;
			case'-':return a1-b1;
			case'*':return a1*b1;
			case'/':return a1/b1;
			case'^':return pow(a1,b1);
			case'l':return log(a1);
			case'e':return exp(a1);
			case's':return sin(a1);
			case'X':return cos(a1);
			case't':return tan(a1);
			case'S':return asin(a1);
			case'C':return acos(a1);
			case'T':return atan(a1);
			case'A':return a1>0?a1:-a1;
			case'r':return sqrt(a1);
			case'E':return M_E;
			case'P':return M_PI;
			case'`':return -a1;
			case'\t':return t;
			case'x': return x;
			case'y': return y;
			case'z': return z;
			default:return a1;
		}	
	}else return v->val;
}
double function::calc()
{
	return calc(bd); 
}
function::function(const char * s1)
{
	x=y=z=t=0;
	memset(op,0,sizeof(op));
	memset(s,0,sizeof(s));
	bd=NULL;
	strcpy(s,s1);
	strt=s;
	make();
}
