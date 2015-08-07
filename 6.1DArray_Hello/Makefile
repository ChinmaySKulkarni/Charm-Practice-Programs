CHARMC=../../../../bin/charmc $(OPTS)

OBJS = arrayhello.o

all: arrayhello

arrayhello: $(OBJS)
	$(CHARMC) -language charm++ -o arrayhello $(OBJS)

arrayhello.decl.h: arrayhello.ci
	$(CHARMC)  arrayhello.ci

clean:
	rm -f *.decl.h *.def.h conv-host *.o arrayhello charmrun

arrayhello.o: arrayhello.C arrayhello.decl.h
	$(CHARMC) -c arrayhello.C

#test: all
#	./charmrun hello +p4 10 $(TESTOPTS)

#bgtest: all
#	./charmrun hello +p4 10 +x2 +y2 +z1 $(TESTOPTS)
