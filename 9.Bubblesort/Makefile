CHARMC=../../../../../bin/charmc $(OPTS)

OBJS = bubblesort.o

all: bubblesort

bubblesort: $(OBJS)
	$(CHARMC) -language charm++ -o bubblesort $(OBJS)

bubblesort.decl.h: bubblesort.ci
	$(CHARMC)  bubblesort.ci

clean:
	rm -f *.decl.h *.def.h conv-host *.o bubblesort charmrun

bubblesort.o: bubblesort.C bubblesort.decl.h
	$(CHARMC) -c bubblesort.C


