/******This program is WRONG as it doesn't guarantee proper order of execution as there is no provision for checking that messages (asynchronous method invocations) are delivered in the same order in Charm++ s.see page 11 of CharmTutorial2_3.pdf*****/
#include<stdio.h>
#include"async.decl.h"

class main: public CBase_main
{
	public:
		main(CkArgMsg *m)
		{	
			int i;			
			ckout<<"hello world!"<<endl;
			if(m->argc > 1)
				ckout<<"And hello to "<<m->argv[1]<<endl;
			double pi=3.14;
			CProxy_simple sim = CProxy_simple::ckNew(pi);
			for(i = 1;i<10;i++)
				sim.findarea(i,0);
			sim.findarea(10,1);		
		};
};

class simple: public CBase_simple
{
	private:
		float y;	
		
	public:
		simple(double pi)
		{
			ckout<<"I am a simple chare running from processor:"<<CkMyPe()<<endl;
			y = pi;
		};
		
		void findarea(int x, bool done)
		{
			
			ckout<<"Radius of circle is: "<<x<<"Area of the circle is: "<<y*x*x<<endl;
			if(done)
				CkExit();
		};
};

#include"async.def.h"
