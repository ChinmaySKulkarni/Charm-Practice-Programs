CHARMC=../../../../../bin/charmc $(OPTS)

OBJS = parallel_prefix.o

all: parallel_prefix

parallel_prefix: $(OBJS)
	$(CHARMC) -language charm++ -o parallel_prefix $(OBJS)

proj: $(OBJS)
	$(CHARMC) -language charm++ -tracemode projections -o parallel_prefix.prj $(OBJS)

parallel_prefix.decl.h: parallel_prefix.ci
	$(CHARMC)  parallel_prefix.ci

clean:
	rm -f *.decl.h *.def.h conv-host *.o  *.log *.prj *.sts *.projrc parallel_prefix charmrun

parallel_prefix.o: parallel_prefix.C parallel_prefix.decl.h
	$(CHARMC) -c parallel_prefix.C

#test: all
#	./charmrun hello +p4 10 $(TESTOPTS)

#bgtest: all
#	./charmrun hello +p4 10 +x2 +y2 +z1 $(TESTOPTS)
