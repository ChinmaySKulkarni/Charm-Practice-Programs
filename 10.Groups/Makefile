CHARMC=../../../../../bin/charmc $(OPTS)

OBJS = helloGroup.o

all: helloGroup

helloGroup: $(OBJS)
	$(CHARMC) -g -language charm++  -o helloGroup $(OBJS)

proj: $(OBJS)
	$(CHARMC) -language charm++  -tracemode projections -o helloGroup.prj $(OBJS)

helloGroup.decl.h: helloGroup.ci
	$(CHARMC)  helloGroup.ci

clean:
	rm -f *.decl.h *.def.h *.log *.prj.sts *.prj.projrc conv-host *.o helloGroup charmrun helloGroup.prj

helloGroup.o: helloGroup.C helloGroup.decl.h
	$(CHARMC) -g -c helloGroup.C


