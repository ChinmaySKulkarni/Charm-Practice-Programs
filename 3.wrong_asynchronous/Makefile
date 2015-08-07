CHARMC=../../../../bin/charmc $(OPTS)

OBJS = async.o

all: async

async: $(OBJS)
	$(CHARMC) -language charm++ -o async $(OBJS)

async.decl.h: async.ci
	$(CHARMC)  async.ci

clean:
	rm -f *.decl.h *.def.h conv-host *.o async charmrun

async.o: async.C async.decl.h
	$(CHARMC) -c async.C

#test: all
#	./charmrun hello +p4 10 $(TESTOPTS)

#bgtest: all
#	./charmrun hello +p4 10 +x2 +y2 +z1 $(TESTOPTS)
