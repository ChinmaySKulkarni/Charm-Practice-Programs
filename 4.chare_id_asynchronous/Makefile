CHARMC=../../../../bin/charmc $(OPTS)

OBJS = chare_id.o

all: chare_id

chare_id: $(OBJS)
	$(CHARMC) -language charm++ -o chare_id $(OBJS)

chare_id.decl.h: chare_id.ci
	$(CHARMC)  chare_id.ci

clean:
	rm -f *.decl.h *.def.h conv-host *.o chare_id charmrun

chare_id.o: chare_id.C chare_id.decl.h
	$(CHARMC) -c chare_id.C

#test: all
#	./charmrun hello +p4 10 $(TESTOPTS)

#bgtest: all
#	./charmrun hello +p4 10 +x2 +y2 +z1 $(TESTOPTS)
