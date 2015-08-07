#include<stdio.h>
#include"arrayhello.decl.h"

class main: public CBase_main
{
	private:
		int arraysize;
	
	public:		
		main(CkMigrateMessage *m)
		{};
		main(CkArgMsg *m)
		{
			//arraysize = DEFAULT_ARRAY_SIZE;
			if (m->argc >1)
				arraysize = atoi(m->argv[1]);
			else
				arraysize = 5;
			if (arraysize <=0)
			{
				CkPrintf(" [ERROR] !! There should be atleast one element in the array! Exiting now!");
				CkExit();
			}
			delete m;

			CProxy_hello hi = CProxy_hello::ckNew(thisProxy, arraysize);
		}

		void checkin()
		{
			static int check = 0;
			if((++check)>=arraysize)
				CkExit();
		};
};

class hello: public CBase_hello
{
	public:
		hello(CkMigrateMessage *m)
		{};				
		hello(CProxy_main master)
		{
			CkPrintf("Hello World! Index number: [%d] Processor number: [%d] \n", thisIndex,CkMyPe());
			master.checkin();		
		};
};

#include"arrayhello.def.h"
