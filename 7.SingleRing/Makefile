CHARMC=../../../../bin/charmc $(OPTS)

OBJS = singleRing.o

all: singleRing

singleRing: $(OBJS)
	$(CHARMC) -language charm++ -o singleRing $(OBJS)

singleRing.decl.h: singleRing.ci
	$(CHARMC)  singleRing.ci

clean:
	rm -f *.decl.h *.def.h conv-host *.o singleRing charmrun

singleRing.o: singleRing.C singleRing.decl.h
	$(CHARMC) -c singleRing.C

#test: all
#	./charmrun hello +p4 10 $(TESTOPTS)

#bgtest: all
#	./charmrun hello +p4 10 +x2 +y2 +z1 $(TESTOPTS)
