#include"helloGroup.decl.h"
#include<stdio.h>
#define ARRAY_ELEMENTS 100
CProxy_main mainProxy;
CProxy_countHi groupProxy;						//Readonly variables.
int totalChares;

class main: public  CBase_main							
{
  private: 
  CProxy_hello arrayProxy;
  int totalBranches;							//Equal to the number of processors.

  public:
  main(CkMigrateMessage *msg)
  {};
 
  main(CkArgMsg *m)
  {
    totalChares = ARRAY_ELEMENTS;					//Total number of chares in the chare array.
    if(m->argc >= 2)
      totalChares = atoi(m->argv[1]);
    delete m;
    totalBranches = 0;
    CkPrintf("Running helloGroup on %d processors with %d chares \n", CkNumPes(), totalChares);
    if(CkNumPes()<2) 
      CkAbort("This program should be run on at least 2 processors.\n");
    mainProxy = thisProxy;
    groupProxy = CProxy_countHi::ckNew();				//Create the group.
    arrayProxy = CProxy_hello::ckNew(totalChares);			//Create the chare array.
  };

  void startNow()
  {
    if(++totalBranches < CkNumPes())
      return;
    arrayProxy[0].sayHi();						//Start the sayHi method invocation only after all the branches 									have been created. One for each PE.
  };
  
  void done()
  {
    groupProxy[0].showCounts();
  };
};

class countHi: public CBase_countHi					//Group.
{
  private: 
  int localCheckIns;

  public:
  countHi()
  {
    CkPrintf("group branch countHi[%d] created \n",CkMyPe());
    localCheckIns = 0;
    mainProxy.startNow();
  };

  void chareCheckin()
  {
    localCheckIns++;
  };
 
  void showCounts()
  {
      CkPrintf("Total Checkins %d on processor %d \t %d\n",localCheckIns,CkMyPe(),thishandle);
      if(CkMyPe() == CkNumPes() - 1)
        CkExit();
      else
        thisProxy[CkMyPe()+ 1].showCounts();				//Single ring.
  };
};

class hello: public CBase_hello						//Chare array.
{
  public:
  hello(CkMigrateMessage *msg)
  {};
 
  hello()
  {
    //CkPrintf("hello[%d] created \n",thisIndex);
  };
 
  void sayHi()
  {
    CkPrintf("Hi\n");
    countHi *p;
    p = groupProxy.ckLocalBranch();					//Checkin with the local group branch.
    p->chareCheckin();
    if(thisIndex == totalChares - 1)
      mainProxy.done();
    else 
      thisProxy[thisIndex + 1].sayHi();					//Single ring method.
  };
};
#include"helloGroup.def.h"


















