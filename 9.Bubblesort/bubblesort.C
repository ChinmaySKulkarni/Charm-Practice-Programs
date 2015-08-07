#include"bubblesort.decl.h"
#include<stdio.h>
#include<string.h>
#include<stdlib.h>

CProxy_main mainProxy;
int totalMembers;
	
class main: public CBase_main
{
	private:
		int phaseFlag;						//0 or 1 for even or odd indices respectively.
		int swapFlag;						//used to check whether or not a swap occurred for each index.
		int ConPhasesWithoutSwap;				//counts the number of consequent phases without swaps.
		int count;						//used to count the number of checkIns received.
		CProxy_bubble list;

		void nextPhase()					
		{
			count = 0;
			swapFlag = 0;
			list.startPhase(phaseFlag);			//broadcast to list with method startPhase with parameter as phaseFlag 	
		}


	public:
		main(CkMigrateMessage *msg)
		{};
		
		main(CkArgMsg *m)
		{
			if(m->argc >=2)
				totalMembers = atoi(m->argv[1]);
			else 
				totalMembers = 5;
			if(totalMembers <= 0)
			{
				CkPrintf("Total elements must be positive! \n");
				CkExit();
			}
			delete m;
			mainProxy = thisProxy;			
			phaseFlag = 0; 
			ConPhasesWithoutSwap = 0;
			CkPrintf("Bubblesort with %d elements on %d number of PEs\n",totalMembers,CkNumPes());
			list = CProxy_bubble::ckNew(totalMembers);		//Instantiate chare array.
			CkPrintf("Begin:\n");			
			list[0].display(1);					//Display the array before sorting operation.
		};

/***********************************************************************************************************************************************
Note: We have not bounded the number of iterations by the totalMembers variable. Rather we are checking the swapFlag and Consecutive phases without swap flag to check if the next iteration is required or not. If the latter flag becomes 2, we end the program after displaying its results.
****************************************************************************************************************************************************/

		void checkIn(int swap)
		{
			count++;		
			swapFlag += swap;
			if(count >= totalMembers)		//check that all chares have checked in for that phase (irrespective of parity)
			{
				if(swapFlag == 0)		//no swapping occurred for any index in that entire phase			
					ConPhasesWithoutSwap++;
				else 
					ConPhasesWithoutSwap = 0;

				if(ConPhasesWithoutSwap >= 2)
				{
					CkPrintf("Result: \n");				
					list[0].display(0);//and the program will end after display.
				}	
				else
				{
					phaseFlag = ((phaseFlag+1) % 2);//changes phase from 0 to 1 and 1 to 0
					nextPhase();
				}
			}
		};

		void finishedDisplay(int state)
		{
			if (state == 1)
				nextPhase();
			else if (state == 0)
				CkExit();
		};

};

class bubble: public CBase_bubble 
{
	private:
		int Myvalue;
	public:
		bubble(CkMigrateMessage *msg)
		{};
		
		bubble()
		{
			Myvalue = rand() % 100;
		};

		void acceptSwap(int recdVal)
		{
			Myvalue = recdVal;	
			mainProxy.checkIn(1);					//pass 1 because there is a swap
		};

		void denySwap()
		{
			mainProxy.checkIn(0);					//pass 0 because there is no swap
		};

		void requestSwap(int recdVal)
		{
			if(recdVal>Myvalue)
			{
				thisProxy[thisIndex - 1].acceptSwap(Myvalue);
				Myvalue = recdVal;
			}

			else
				thisProxy[thisIndex - 1].denySwap();
		};


		void startPhase(int phaseFlag)		
		{
			if(((thisIndex % 2) == phaseFlag) && ((thisIndex+1) < totalMembers))
				thisProxy[thisIndex+1].requestSwap(Myvalue);	//only those indices that are of the same parity as phaseFlag operate
			else
				mainProxy.checkIn(0);				//pass 0 because there is no swap.
		};

/***************************************************************************************************************************************************
Note: all indices eventually checkIn in each phase..even if they are not of the same parity as the phaseFlag, they will checkIn from this else statement. If they are of the same parity as the phaseFlag and are operating then according to the occurrence of a swap or not they will checkIn from either from acceptSwap() or denySwap()...so though in each phase only chares with even or odd indices operate, they all checkIn!
****************************************************************************************************************************************************/
		
		void display(int state)
		{
			CkPrintf("State(%d):\tbubble[%d] = %d on PE (%d) \n",state,thisIndex,Myvalue,CkMyPe());
			if(thisIndex < totalMembers-1 )
				thisProxy[thisIndex+1].display(state);	
			else
				mainProxy.finishedDisplay(state);
		};

};
	
#include"bubblesort.def.h"	


		
