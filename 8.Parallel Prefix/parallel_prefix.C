#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>
#include"parallel_prefix.decl.h"

CProxy_main mainProxy;
int memberCount;

class main: public CBase_main
{
	private:
		int checkIncounter;
		CProxy_parallel parallelProxy;
	public:
	
		main(CkMigrateMessage *msg)
		{};

		main(CkArgMsg *m)
		{
			memberCount = 5;					//default value
			if(m->argc >1)
				memberCount = atoi(m->argv[1]);
			if(memberCount <=0)
				CkExit();
			checkIncounter = 0;					//initialize the checkin counter
			CkPrintf("Parallel Prefix code begins. \n");
			delete m;
			srand(time(NULL));					//used to seed the value for use by rand()
			CkPrintf("The original array is : \n");				
			parallelProxy = CProxy_parallel::ckNew(memberCount);
			parallelProxy.startStep();
		};

		void checkIn(int step)
		{
			checkIncounter++;
			if(checkIncounter == memberCount)			//to check that all chares have checked in
			{
				checkIncounter = 0;				//re-initialize the checkin counter
				step++;
				if (step <= ((log(memberCount)/log(2))+1))	//total steps should be log2(memberCount)+1
					parallelProxy.startStep();
				else
				{
					CkPrintf("End of Parallel Prefix Program. The Result is: \n");
					parallelProxy.display();		//display the final result
				}
			}
		};	
};


class parallel: public CBase_parallel
{
	private:
		int data;
		int step;
	
	public:
		parallel(CkMigrateMessage *msg)
		{};

		parallel()
		{
			step = 0;
			data = rand() % 100;
			display();
		};

		void startStep()
		{
			step++;
			int i = pow(2,(step - 1));					//to find the index of the receiver.
			if((thisIndex + i) <= (memberCount)-1)	
				thisProxy[thisIndex+i].doStep(data);	
			else
				mainProxy.checkIn(step);				/*if you are not sending your data to another chare, checkin 												with the mainchare anyways!*/
		};

	
		void doStep(int incoming)
		{
			data = data + incoming;						//Add the incoming data (previous sum) to your data.
			mainProxy.checkIn(step);					//checkin with the mainchare
		};

	
		void display()
		{
			CkPrintf("Data[%d] = %d on  PE(%d) .\n",thisIndex,data,CkMyPe());
			if((thisIndex == (memberCount - 1)) && (step!=0))
				CkExit();						//Exit condition.
		};

		
};

#include"parallel_prefix.def.h"





		













