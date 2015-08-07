#include<stdio.h>
#include"hello.decl.h"

class main : public CBase_main 
{
	public:
		main(CkArgMsg *m)
		{
			int a;
			ckout<<"Hello world!"<<endl;
			ckout<<" and hello to you: "<<m->argv[1]<<endl;
			CkScanf("%d",&a);
			ckout<<"Int a is : "<<a<<endl;
			CkExit();
		};
};

#include"hello.def.h"
