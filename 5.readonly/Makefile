CHARMC=../../../../bin/charmc $(OPTS)

OBJS = read_only.o

all: read_only

read_only: $(OBJS)
	$(CHARMC) -language charm++ -o read_only $(OBJS)

read_only.decl.h: read_only.ci
	$(CHARMC)  read_only.ci

clean:
	rm -f *.decl.h *.def.h conv-host *.o read_only charmrun

read_only.o: read_only.C read_only.decl.h
	$(CHARMC) -c read_only.C

#test: all
#	./charmrun hello +p4 10 $(TESTOPTS)

#bgtest: all
#	./charmrun hello +p4 10 +x2 +y2 +z1 $(TESTOPTS)
