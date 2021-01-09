#ifndef _EXTEND_H
#define _EXTEND_H

class bds{
	public:
	double val;
	char sym;
	bool sg;
	bds *l,*r;
	bds();
	~bds(); 
};
bds* rrot(bds* p);
void simplify(bds*& p1);
class function
{
	char s[1005],*strt,op[1005],*sp;
	bds* bd;
	public:
	double t,x,y,z;
	bds* getsingleitem();
	bds* gentree();
	bds* make();
	double calc(bds*v);
	double calc();
	function(const char*);
};

#endif

