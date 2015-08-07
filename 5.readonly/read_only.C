#include<stdio.h>
#include"read_only.decl.h"

CProxy_main mainProxy;

class main: public CBase_main
{
	private:
		int count;
	public:
		main(CkArgMsg *m)
		{	
			int i;	
			mainProxy = thisProxy;					/*mainProxy is a readonly variable, so it can be set only in the 											constructor of the mainchare*/
			ckout<<"hello world!"<<endl;
			if(m->argc > 1)
				ckout<<"And hello to "<<m->argv[1]<<endl;
			double pi=3.14;
			for(i = 1;i<=10;i++)
				CProxy_worker::ckNew(i,pi);			//we don't need to store the proxy of the newly created worker chare
			count = 10;						//total 10 responses are wanted		
		};
		
		void printarea(int r, double area)
		{
			ckout<<"Radius is: "<<r<<" and area is: "<<area<<endl;
			count--;
			if(count == 0)
				CkExit();
		};
};

class worker: public CBase_worker
{
	private:
		float y;
				
	public:
		worker(int r, double pi)
		{
			ckout<<"I am a simple chare running from processor:"<<CkMyPe()<<endl;
			y = pi;
			mainProxy.printarea(r, y*r*r);
		};
};

#include"read_only.def.h"
