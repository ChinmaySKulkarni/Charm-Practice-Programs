CHARMC=../../../../bin/charmc $(OPTS)

OBJS = simple.o

all: simple

simple: $(OBJS)
	$(CHARMC) -language charm++ -o simple $(OBJS)

simple.decl.h: simple.ci
	$(CHARMC)  simple.ci

clean:
	rm -f *.decl.h *.def.h conv-host *.o simple charmrun

simple.o: simple.C simple.decl.h
	$(CHARMC) -c simple.C

#test: all
#	./charmrun hello +p4 10 $(TESTOPTS)

#bgtest: all
#	./charmrun hello +p4 10 +x2 +y2 +z1 $(TESTOPTS)
