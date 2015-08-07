#include<stdio.h>
#include"simple.decl.h"

class main: public CBase_main
{
	public:
		main(CkArgMsg *m)
		{	
			ckout<<"hello world!"<<endl;
			if(m->argc > 1)
				ckout<<"And hello to "<<m->argv[1]<<endl;
			double pi=3.14;
			CProxy_simple::ckNew(12,pi);
		};
};

class simple: public CBase_simple
{
	public:
		simple(int x, double y)
		{
			ckout<<"I am a simple chare running from processor:"<<CkMyPe()<<endl;
			ckout<<"The radius is:"<<x<<endl;
			ckout<<"And the area is:"<<y*x*x<<endl;
			CkExit();
		};
};

#include"simple.def.h"
