/******This program ensures total number of method invocations is satisfied, though correct order is still not ensuredsee page 14 of CharmTutorial2_3.pdf*****/
#include<stdio.h>
#include"chare_id.decl.h"

class main: public CBase_main
{
	private:
		int count;
	public:
		main(CkArgMsg *m)
		{	
			int i;			
			ckout<<"hello world!"<<endl;
			if(m->argc > 1)
				ckout<<"And hello to "<<m->argv[1]<<endl;
			double pi=3.14;
			CProxy_simple sim = CProxy_simple::ckNew(pi,thisProxy);
			for(i = 1;i<=10;i++)
				sim.findarea(i);
			count = 10;					//total 10 responses are wanted		
		};
		
		void printarea(int r, double area)
		{
			ckout<<"Radius is: "<<r<<" and area is: "<<area<<endl;
			count--;
			if(count == 0)
				CkExit();
		};
};

class simple: public CBase_simple
{
	private:
		float y;
		CProxy_main mainProxy;	
		
	public:
		simple(double pi, CProxy_main m)
		{
			mainProxy = m;
			ckout<<"I am a simple chare running from processor:"<<CkMyPe()<<endl;
			y = pi;
		};
		
		void findarea(int x)
		{
			
			mainProxy.printarea(x,y*x*x);
		};
};

#include"chare_id.def.h"
