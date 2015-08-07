#include<stdio.h>
#include<time.h>
#include"singleRing.decl.h"

class main: public CBase_main
{
	public:
		main(CkMigrateMessage *msg)
		{};
		main(CkArgMsg *m)
		{
			int ringSize = 10;
			int tripCount = 5;
			if(m->argc > 1)
				ringSize = atoi(m->argv[1]);
			if(m->argc >2)
				tripCount = atoi(m->argv[2]);
			if(ringSize <= 0 || tripCount <= 0)
			{
				CkPrintf("Invalid ringsize and number of trips! \n");
				CkExit();
			}
			
			CkPrintf("Single Ring of  %d  elements and with  %d  traversals using  %d  number of PEs \n",ringSize, tripCount,CkNumPes());
			
			CProxy_ring ring = CProxy_ring::ckNew(thisProxy, ringSize, ringSize); /*first ringSize is stored...second one need notbe specified 													in the constructor of ring because it is implicitly 													required*/ 
			srand(time(NULL));
			ring(rand() % ringSize).doSomething(ringSize, tripCount, -1 ,-1);
		};
		
		void finished()
		{
			CkExit();
		};
};

class ring: public CBase_ring
{
	private:
		CProxy_main mainProxy;
		int ringSize;
	public:
		ring(CkMigrateMessage *msg)
		{};
		ring(CProxy_main mp, int rs)
		{
			mainProxy = mp;
			ringSize = rs;
		};

		void doSomething(int elementsLeft, int tripsLeft, int fromIndex, int fromPE)
		{
			CkPrintf("Ring[%d] on PE (%d). Tripsleft = %d  message got from [%d] on PE (%d) \n", thisIndex, CkMyPe(), tripsLeft, fromIndex, 				fromPE);
			if(elementsLeft > 1)
				thisProxy[(thisIndex+1) % ringSize].doSomething(elementsLeft-1,tripsLeft,thisIndex,CkMyPe());
			else if(tripsLeft > 1)					//no more elements left in that trip so go to next trip 
				thisProxy[(thisIndex+1) % ringSize].doSomething(ringSize,tripsLeft-1,thisIndex,CkMyPe());
			else							//all traversals finished
				mainProxy.finished();
		};
};

#include"singleRing.def.h"


		









	
		
